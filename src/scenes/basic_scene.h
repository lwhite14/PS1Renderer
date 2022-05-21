#pragma once

#include "scene.h"
#include "../debug_window.h"
#include "../lights/point_light.h"
#include "../glslprogram.h"
#include "../render_obj.h"

class Basic_Scene : public Scene
{
private:
	DebugWindow debugWindow;
	GLSLProgram prog;
	RenderObj cube;

	PointLight light;

public:
	Basic_Scene();
	void Start(GLFWwindow* window);
	void Update(GLFWwindow* window, float deltaTime);
	void Render();
	void CleanUp();
};