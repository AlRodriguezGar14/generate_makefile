#ifndef NEWMAKEFILE_HPP
#define NEWMAKEFILE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <filesystem>
#include <fstream>
#include <sstream>


int updateMakefile(std::vector<std::string> files, std::string path);
int buildMakefile(std::string path);

#endif
