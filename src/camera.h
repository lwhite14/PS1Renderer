#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "motion.h"

using glm::vec3;
using glm::mat4;

class Camera 
{
public:
	vec3 cameraPos;
	vec3 cameraFront;
	vec3 cameraUp;

	bool firstMouse;
	bool canFirstMouse;

	float yaw;
	float pitch;
	float lastX;
	float lastY;

	bool isActive;
	bool canChangeActive = true;

	Motion motion;

	Camera();
	Camera(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, vec3 startPos = vec3(0.0f));
	void SetFront(GLFWwindow* window);
	mat4 ChangeViewMatrix(mat4 view);
	void KeyCallback(GLFWwindow* window);
	void MouseCallback(GLFWwindow* window);
	void Movement(float deltaTime);
};