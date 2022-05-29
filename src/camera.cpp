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

void Camera::SetFront(GLFWwindow* window)
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void Camera::SetYaw(float yaw) 
{
	this->yaw = yaw;
}

mat4 Camera::ChangeViewMatrix(mat4 view) 
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
