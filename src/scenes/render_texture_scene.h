#pragma once

#include "scene.h"
#include "../drawables/obj_mesh.h"

class RenderTexture_Scene : public Scene
{
private:
	GLSLProgram prog;
	GLSLProgram quadProg;
	ObjMesh* suzanne;

	unsigned int framebuffer;
	unsigned int quadVAO, quadVBO;
	unsigned int textureColorbuffer;

	void CompileShaders();
public:
	RenderTexture_Scene();
	void Start(GLFWwindow* window);
	void Update(GLFWwindow* window, float deltaTime);
	void Render();
	void CleanUp();
};