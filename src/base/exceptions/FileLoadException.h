#pragma once

#include <stdexcept>
#include <string>

class FileLoadException : public std::exception
{
public:
	FileLoadException(std::string filename) throw() : std::exception(std::string("File '" + filename + "' does not exist or is corrupted").c_str()) {}
};
