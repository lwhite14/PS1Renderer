#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() { }

Camera::Camera(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, vec3 startPos)
{
	isActive = true;

	firstMouse = true;
	canFirstMouse = true;
	yaw = -90.0f;
	pitch = 0.0f;
	lastX = SCR_WIDTH / 2.0;
	lastY = SCR_HEIGHT / 2.0;

	motion = { false,false,false,false };

	cameraPos = startPos;
	cameraFront = vec3(0.0f, 0.0f, -1.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);
}

void Camera::KeyCallback(GLFWwindow* window)
{
	int wState = glfwGetKey(window, GLFW_KEY_W);
	int sState = glfwGetKey(window, GLFW_KEY_S);
	int aState = glfwGetKey(window, GLFW_KEY_A);
	int dState = glfwGetKey(window, GLFW_KEY_D);
	int shiftState = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
	if (shiftState == GLFW_PRESS)
	{
		if (canChangeActive)
		{
			canChangeActive = false;
			canFirstMouse = true;
			if (isActive)
			{
				isActive = false;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else if (!isActive)
			{
				isActive = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
		}
	}
	if (shiftState == GLFW_RELEASE)
	{
		if (canFirstMouse)
		{
			canChangeActive = true;
			firstMouse = true;
		}
		canFirstMouse = false;
	}
	if (isActive)
	{
		if (wState == GLFW_PRESS)
		{
			motion.Forward = true;
		}
		if (sState == GLFW_PRESS)
		{
			motion.Backward = true;
		}
		if (aState == GLFW_PRESS)
		{
			motion.Left = true;
		}
		if (dState == GLFW_PRESS)
		{
			motion.Right = true;
		}
		if (wState == GLFW_RELEASE)
		{
			motion.Forward = false;
		}
		if (sState == GLFW_RELEASE)
		{
			motion.Backward = false;
		}
		if (aState == GLFW_RELEASE)
		{
			motion.Left = false;
		}
		if (dState == GLFW_RELEASE)
		{
			motion.Right = false;
		}
	}
	else
	{
		motion.Forward = false;
		motion.Backward = false;
		motion.Left = false;
		motion.Right = false;
	}
}

void Camera::MouseCallback(GLFWwindow* window)
{
	if (isActive)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}
}

void Camera::Movement(float deltaTime)
{
	float cameraSpeed = 20.0f * deltaTime;
	if (motion.Forward)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (motion.Backward)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (motion.Left)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (motion.Right)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

mat4 Camera::ChangeViewMatrix(mat4 view) 
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
