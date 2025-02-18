// TextureEditorClient.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "Buffers.h"
#include "Vao.h"
#include "Texture.h"
#include "Shader.h"
#include "File.h"
#include "../TextureEditorBusiness/FastNoiseLite.h"
#include "queue"
#include "list"
#include "../TextureEditorBusiness/Operator.h"
#include "../TextureEditorBusiness/PerlinOperatorClient.h"
#include "../TextureEditorBusiness/DraftClient.h"

struct DataShape
{

	DataShape(Vao* vertices, Shader* shader, GLsizei size, std::vector<Buffers*>* buffers)//, Texture* newTexture)
	{
		shapeVertices = vertices;
		count = size;
		buf = buffers;
		//texture = newTexture;
		shaders = shader;
	}
	~DataShape()
	{
		delete shapeVertices;
		delete shaders;
		if (!buf->empty())
		{
			for (auto i : *buf)
			{
				delete i;
			}
		}
		delete buf;
		//delete texture;
	}

	Vao* shapeVertices;
	//Texture* texture;
	Shader* shaders;
	GLsizei count;

	std::vector<Buffers*>* buf;
};

/*
 /Brief : function that load data into opengl to prepare a rectangle draw
  vsSrc : vertex shader
  fsSrc : fragment shader
  x, y  : position where render the shape
*/
DataShape* buildRectangle(File* vsSrc, File* fsSrc, float x, float y)
{
	float vertices[28] = {
	 0.5f + x,  0.5f + y, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 0.5f + x,  -0.5f + y, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f + x, -0.5f + y, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 -0.5f + x,  0.5f + y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[6] = { 0, 1, 3, 1, 2, 3 };

	/* Allocate brut memory on GPU */
	Buffers* buf = new Buffers();
	buf->storeData(vertices, 28 * sizeof(float));
	Buffers* buf2 = new Buffers();
	buf2->storeData(indices, 6 * sizeof(unsigned int));

	/* Create the Vao */
	Vao* vao = new Vao(0, buf->GetBuffer(), 0, 7 * sizeof(float));

	vao->MakeVao(0, 0, 2, GL_FLOAT, GL_FALSE, 0);
	vao->MakeVao(1, 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	vao->MakeVao(2, 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

	glVertexArrayElementBuffer(vao->GetVaoId(), buf2->GetBuffer());

	/* Create Program */
	Shader* shader = new Shader(vsSrc, fsSrc);

	std::vector<Buffers*>* buffers = new std::vector<Buffers*>;
	buffers->push_back(buf);
	buffers->push_back(buf2);

	DataShape* s = new DataShape(vao, shader, 6, buffers);
	return s;

	//m_drawList.push_back(new DataShape(vao, shader, 6, buffers));
}

/*
 /Brief : function that load data into opengl to draw a rectangle
  shapeToRender : data of the shape
*/
void drawTriangle(DataShape* shapeToRender)
{
	//glBindTexture(GL_TEXTURE_2D, shapeToRender->texture->textureId);
	glBindVertexArray(shapeToRender->shapeVertices->GetVaoId());
	glUseProgram(shapeToRender->shaders->programId);
	glDrawElements(GL_TRIANGLES, shapeToRender->count, GL_UNSIGNED_INT, nullptr);
	glUseProgram(0);
	glBindVertexArray(0);

}

/*
 /Brief : Function that load an open gl texture into imgui frame 
*/
void DrawImgui(Texture* TextureToRender)
{

	ImGui::Begin("My Scene");

	// we access the ImGui window size
	const float window_width = ImGui::GetContentRegionAvail().x;
	const float window_height = ImGui::GetContentRegionAvail().y;

	// we rescale the framebuffer to the actual window size here and reset the glViewport 
	glViewport(0, 0, window_width, window_height);

	// we get the screen position of the window
	ImVec2 pos = ImGui::GetCursorScreenPos();

	// and here we can add our created texture as image to ImGui
	// unfortunately we need to use the cast to void* or I didn't find another way tbh
	ImGui::GetWindowDrawList()->AddImage(
		TextureToRender->textureId,
		ImVec2(pos.x, pos.y),
		ImVec2(pos.x + window_width, pos.y + window_height),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);
	ImGui::End();
}

int main()
{
	glfwInit();
	IMGUI_CHECKVERSION();

	// Set context as OpenGL 4.6 Core, forward compat, with debug depending on build config
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#else /* !NDEBUG */
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
#endif /* !NDEBUG */
	glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	int width = 550;
	int height = 800;
	GLFWwindow* window = glfwCreateWindow(width, height, "Client", nullptr, nullptr);
	if (!window)
		throw std::runtime_error("Unable to initialize GLFW");

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
	ImGui_ImplOpenGL3_Init("#version 460");

	/* Create clientDraft to get client method */
	//DraftClient* clientDraft = new DraftClient();
	//PerlinOperatorClient* perlinOp = new PerlinOperatorClient();
	//clientDraft->AddOperator(perlinOp);
	//perlinOp->Activate(clientDraft);

	/* Create Texture */
	Texture* T = new Texture();
	T->GeneratePerlinTexture(128,128);

	do
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//drawTriangle(shape);
		DrawImgui(T);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	delete T;
	//delete perlinOp;
	//delete clientDraft;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}