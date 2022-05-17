#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "motion.h"

using glm::vec3;
using glm::mat4;

class Camera 
{
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float deltaTime;
	float lastFrame;

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
	Camera(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, vec3 startPos = vec3(0.0f, 0.0f, 0.0f));
	void UpdateDeltaTime();
	void KeyCallback(GLFWwindow* window);
	void MouseCallback(GLFWwindow* window);
	void Movement();
	mat4 ChangeViewMatrix(mat4 view);
};