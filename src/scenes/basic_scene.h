#pragma once

#include "scene.h"
#include "../drawables/cube.h"
#include "../debug_window.h"
#include "../lights/point_light.h"
#include "../glslprogram.h"

class Basic_Scene : public Scene
{
private:
	DebugWindow debugWindow;
	GLSLProgram prog;
	GLuint tex1, tex2;
	Cube cube;

	PointLight light;

public:
	Basic_Scene();
	void Start(GLFWwindow* window);
	void Update(GLFWwindow* window, float deltaTime);
	void Render();
	void CleanUp();
};