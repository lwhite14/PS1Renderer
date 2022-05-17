#pragma once

#include "scene.h"
#include "../drawables/cube.h"

class Basic_Scene : public Scene
{
private:
	Shader shader;
	GLuint tex1, tex2;
	Cube cube;

public:
	Basic_Scene();
	void Start();
	void Update();
	void Render();
};