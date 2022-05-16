#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader.h"
using glm::mat4;
using glm::vec3;

class Scene 
{
public:
	int width, height;
	mat4 view, model, projection;

	virtual void Start() {};
	virtual void Update() {};
	virtual void Render() {};
	void SetMatrices(Shader& shader)
	{
		mat4 mv = view * model;
		shader.SetMat4("MVP", projection * mv);
		shader.SetMat4("ModelViewMatrix", mv);
		shader.SetMat4("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	}
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
};