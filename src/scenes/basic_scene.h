#pragma once

#include "scene.h"
#include "../debug_window.h"
#include "../render_obj.h"
#include <vector>

using namespace std;
using namespace glm;

class Basic_Scene : public Scene
{
private:
	DebugWindow debugWindow;
	GLSLProgram prog;
	GLSLProgram quadProg;
	RenderObj car, road, buildings, crate;
	PointLight light;

	vector<vec3> crateLocations;
	vector<float> crateRotations;

	float cameraSpeed;
	float timer;
	float angleMultiplier;
	float startAngle;

	unsigned int renderTexWidth;
	unsigned int renderTexHeight;
	unsigned int framebuffer;
	unsigned int quadVAO, quadVBO;
	unsigned int textureColorbuffer;

	void CompileShaders();
public:
	Basic_Scene();
	void Start(GLFWwindow* window);
	void Update(GLFWwindow* window, float deltaTime);
	void Render();
	void CleanUp();
};