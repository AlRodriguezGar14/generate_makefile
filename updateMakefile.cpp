#include "newMakefile.hpp"

std::string readMakefile(const std::string& path) {
	std::ifstream makefileIn(path);
	if (!makefileIn.is_open()) {
		std::cerr << "Failed to open Makefile" << std::endl;
		return "";
	}

	// Iterate from the first to the last char of the ifstream
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
		if (line.find("SRCS") == 0) {
			std::string newLine = "SRCS =";
			for (size_t i = 0; i < files.size(); ++i) {
				newLine += (i == 0) ? "\t" + files[i] : "\t\t" + files[i];
				if (i != files.size() - 1) {
					newLine += " \\";
				}
				newLine += "\n";
			}
			if (files.size() == 0) {
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
