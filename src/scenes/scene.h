#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader.h"
#include "../camera.h"
#include "../glslprogram.h"
using glm::mat4;
using glm::vec3;

class Scene 
{
public:
	Camera camera;
	int width, height;
	mat4 view, model, projection;

	virtual void Start(GLFWwindow* window) = 0;
	virtual void Update(GLFWwindow* window, float deltaTime) = 0;
	virtual void Render() = 0;
	void Resize(float w, float h)
	{
		glViewport(0, 0, w, h);
		width = w;
		height = h;
		projection = glm::perspective(glm::radians(80.0f), (float)w / h, 0.3f, 1000.0f);
	}
	void SetDimensions(int w, int h) 
	{
		width = w;
		height = h;
	}
	virtual void CleanUp() = 0;
};