#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "scenes/scene.h"
#include <stdio.h>

class DebugWindow 
{
	void DrawElements();
public:
	DebugWindow();

	void Init(GLFWwindow* window);
	void PerFrame();
	void CleanUp();
};