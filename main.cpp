#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <filesystem>
#include <fstream>
#include <sstream>
namespace fs = std::filesystem;

int buildMakefile(std::string path) {

	std::string makefileContent = R"(CXX = g++ -g3 -O2

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -I ./

SRCS =	main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = genericTarget

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking the object files to create the executable..."
	@$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	@echo "Compiling the source file $< into the object file $@..."
	@$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	@echo "Removing the object files..."
	@rm -f $(OBJS) *.gch

fclean: clean
	@echo "Removing the executable..."
	@rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
	)";

	std::ofstream makefile(path);
	if (!makefile.is_open()) {
		std::cerr << "Failed to create Makefile" << std::endl;
		return 1;
	}
	makefile << makefileContent;
	makefile.close();
	return (0);
}

std::string readMakefile(const std::string& path) {
    std::ifstream makefileIn(path);
    if (!makefileIn.is_open()) {
        std::cerr << "Failed to open Makefile" << std::endl;
        return "";
    }

	// Iterate from the first to the lasst char of the ifstream
    std::string makefileContent((std::istreambuf_iterator<char>(makefileIn)),
                                 std::istreambuf_iterator<char>());
    makefileIn.close();
    return makefileContent;
}

std::string updateSRCSLine(const std::string& makefileContent, const std::vector<std::string>& files) {
    std::istringstream iss(makefileContent);
    std::ostringstream oss;
    bool replacing = false;
    for (std::string line; std::getline(iss, line);) {
        if (line.find("SRCS") != std::string::npos) {
            std::string newLine = "SRCS =";
            for (size_t i = 0; i < files.size(); ++i) {
                newLine += (i == 0) ? "\t" + files[i] : "\t\t" + files[i];
                if (i != files.size() - 1) {
                    newLine += " \\";
                }
                newLine += "\n";
            }
            oss << newLine << "\n";
            replacing = true;
        } else if (replacing && (line.find("=") != std::string::npos || line.find(":") != std::string::npos)) {
            replacing = false;
        }
        if (!replacing) {
            oss << line << "\n";
        }
    }
    return oss.str();
}

bool writeMakefile(const std::string& path, const std::string& makefileContent) {
    std::ofstream makefileOut(path);
    if (!makefileOut.is_open()) {
        std::cerr << "Failed to open Makefile for writing" << std::endl;
        return false;
    }
    makefileOut << makefileContent;
    makefileOut.close();
    return (true);
}

int updateMakefile(std::vector<std::string> files, std::string path) {
    std::string makefileContent = readMakefile(path);
    if (makefileContent.empty()) {
        return (1);
    }

    makefileContent = updateSRCSLine(makefileContent, files);

    if (!writeMakefile(path, makefileContent)) {
        return (1);
    }

    return (0);
}

int main(int argc, char **argv) {

	bool makefileFound = false;

	std::string path = argc >= 2 ? argv[1] : ".";

	std::vector<std::string> files;
	for (const fs::directory_entry &entry : fs::directory_iterator(path)) {
		std::string filename = entry.path().filename().string();
		if (!filename.compare("Makefile"))
			makefileFound = true;
		if (filename.find(".cpp") != std::string::npos)
			files.push_back(filename);
	}

	if (makefileFound)
		std::cout << "Makefile already exists in the directory" << std::endl;
	else
		if (buildMakefile(path + "/Makefile"))
			return (1);

	if (updateMakefile(files, path + "/Makefile"))
		return (1);
	return 0;
}
