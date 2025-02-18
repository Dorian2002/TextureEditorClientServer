#include "Buffers.h"


void Buffers::storeData(void* data, size_t size)
{
	glNamedBufferStorage(buffer, size, data, 0);
}

void Buffers::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

unsigned int Buffers::GetBuffer()
{
	return buffer;
}

Buffers::Buffers()
{
	glCreateBuffers(1, &buffer);
}

Buffers::Buffers(int indices)
{
	glGenBuffers(1, &buffer);
}

Buffers::~Buffers()
{
	glDeleteBuffers(1, &buffer);
}
