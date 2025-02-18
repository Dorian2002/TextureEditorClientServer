#pragma once
#include <string>
#include <vector>

class Texture
{
public:
	Texture();
	~Texture();

	void LoadTextureFromFile(const char* texturePath);
	bool LoadTextureFromMemory(const void* data, size_t data_size, int* out_width, int* out_height);
	void GeneratePerlinTexture(int width, int height);

	unsigned int textureId;
	std::string path;
};
