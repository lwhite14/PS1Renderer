#pragma once

#include "scene.h"
#include "../debug_window.h"
#include "../lights/point_light.h"
#include "../glslprogram.h"
#include "../render_obj.h"
#include "../drawables/obj_mesh.h"

class Basic_Scene : public Scene
{
private:
	DebugWindow debugWindow;
	GLSLProgram prog;
	RenderObj car, road;
	PointLight light;

public:
	Basic_Scene();
	void Start(GLFWwindow* window);
	void CompileShaders();
	void Update(GLFWwindow* window, float deltaTime);
	void Render();
	void CleanUp();
};