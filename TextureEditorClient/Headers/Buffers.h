#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#pragma once
class Buffers
{
public:

	// Methodes
	Buffers();
	Buffers(int indices);
	~Buffers();
	void storeData(void* data, size_t size);
	void bind();
	unsigned int GetBuffer();

private:
	unsigned int buffer = 0;
};

