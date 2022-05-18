#pragma once

#include "scene.h"
#include "../drawables/cube.h"
#include "../debug_window.h"

class Basic_Scene : public Scene
{
private:
	Shader shader;
	GLuint tex1, tex2;
	Cube cube;
	DebugWindow debugWindow;

public:
	Basic_Scene();
	void Start(GLFWwindow* window);
	void Update(GLFWwindow* window);
	void Render();
	void CleanUp();
};