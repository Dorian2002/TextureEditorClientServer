#include "File.h"

/* File constructor */
File::File(std::filesystem::path filePath)
{
	if (!std::filesystem::exists(filePath))
	{
		std::cout << "File instantiation Error : path do not  exits" << std::endl;
		exit(151);
	}
	Path = filePath;
	File::readFile();
}

/* File Destructor */
File::~File()
{
	if (file.is_open())
		file.close();
}

/* function that open and keep data in memory */
void File::readFile()
{
	file.open(Path);
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	fileContent = content;
	file.close();
	Timestamp = std::filesystem::last_write_time(Path);
}
