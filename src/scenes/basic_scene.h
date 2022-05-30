#pragma once

#include "scene.h"
#include "../debug_window.h"
#include "../render_obj.h"

class Basic_Scene : public Scene
{
private:
	DebugWindow debugWindow;
	GLSLProgram prog;
	RenderObj car, road, buildings, crate;
	PointLight light;

	float cameraSpeed, timer, angleMultiplier, startAngle;

	void CompileShaders();
public:
	Basic_Scene();
	void Start(GLFWwindow* window);
	void Update(GLFWwindow* window, float deltaTime);
	void Render();
	void CleanUp();
};