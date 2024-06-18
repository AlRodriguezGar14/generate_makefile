#include "newMakefile.hpp"


int main(int argc, char **argv) {

	bool makefileFound = false;

	std::string path = argc >= 2 ? argv[1] : ".";

	std::vector<std::string> files;
	for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(path)) {
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
	std::cout << "Writing to the makefile..." << std::endl;
	if (updateMakefile(files, path + "/Makefile"))
		return (1);
	std::cout << "Makefile updated successfully" << std::endl;
	return 0;
}
