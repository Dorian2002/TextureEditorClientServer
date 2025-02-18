#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
class File
{
public:
	std::string fileContent;

	File() = default;
	File(std::filesystem::path filePath);
	~File();

	void readFile();

private:
	std::filesystem::path Path;
	std::ifstream file;
	std::filesystem::file_time_type Timestamp;
};

