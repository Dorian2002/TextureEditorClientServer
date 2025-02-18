#include "Vao.h"

Vao::Vao()
{
	glCreateVertexArrays(1, &vaoId);
}

Vao::Vao(unsigned int bindingIndex, unsigned int buffer, unsigned int offset, unsigned int size)
{
	glCreateVertexArrays(1, &vaoId);
	glVertexArrayVertexBuffer(vaoId, bindingIndex, buffer, offset, size);
}

Vao::~Vao()
{
	glDeleteVertexArrays(1, &vaoId);
}

void Vao::MakeVao(unsigned int attribIndex, unsigned int bindingindex, int size, GLenum type, GLboolean normalize, unsigned int relativeOffset)
{
	glEnableVertexArrayAttrib(vaoId, attribIndex);
	glVertexArrayAttribBinding(vaoId, attribIndex, bindingindex);
	glVertexArrayAttribFormat(vaoId, attribIndex, size, type, normalize, relativeOffset);
}

unsigned int Vao::GetVaoId()
{
	return vaoId;
}
