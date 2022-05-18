#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "scenes/scene.h"
#include <stdio.h>

class DebugWindow 
{
private:
	void DrawElements();
public:
	float lightPos[3] = { 0.0f, 0.0f, 0.0f };
	float lightDiffuse[3] = { 0.0f, 0.0f, 0.0f };
	float lightAmbient[3] = { 0.0f, 0.0f, 0.0f };
	float lightSpecular[3] = { 0.0f, 0.0f, 0.0f };

	DebugWindow();
	void Init(GLFWwindow* window);
	void PerFrame();
	void CleanUp();
};