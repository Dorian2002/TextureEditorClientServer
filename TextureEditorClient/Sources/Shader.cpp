#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "File.h"


Shader::Shader(File* vertexShaderFile, File* fragmentShaderFile)
{
	/* Compile Vextex Shader */
	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	auto* ptr = vertexShaderFile->fileContent.c_str();
	glShaderSource(vertexShaderId, 1, &ptr, nullptr);
	glCompileShader(vertexShaderId);

	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	/* Check Vertex Shader */
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertexShaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile fragment shader
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	auto* ptr2 = fragmentShaderFile->fileContent.c_str();
	glShaderSource(fragmentShaderId, 1, &ptr2, nullptr);
	glCompileShader(fragmentShaderId);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link program
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glDeleteShader(fragmentShaderId);
	glDeleteShader(vertexShaderId);

	// Check program
	glGetProgramiv(programId, GL_LINK_STATUS, &Result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(programId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	positionLocation = glGetUniformLocation(programId, "uPosition");
	rotationLocation = glGetUniformLocation(programId, "uRotation");
	scaleLocation = glGetUniformLocation(programId, "uScale");
	aspectRatioLocation = glGetUniformLocation(programId, "uAspectRatio");
	sizeLocation = glGetUniformLocation(programId, "uSize");
	pivotLocation = glGetUniformLocation(programId, "uPivot");
}

Shader::~Shader()
{
	glDeleteProgram(programId);
}
