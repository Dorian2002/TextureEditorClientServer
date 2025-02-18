#pragma once
#include <string>

class Texture
{
public:
	Texture(const char* texturePath);
	~Texture();

	unsigned int textureId;
	std::string path;
};

