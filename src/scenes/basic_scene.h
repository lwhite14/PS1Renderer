#pragma once

#include "scene.h"

class Basic_Scene : public Scene
{
private:
	Shader shader;
	GLuint tex1, tex2;
	unsigned int VBO, VAO;

public:
	Basic_Scene();
	void Start();
	void Update();
	void Render();
};