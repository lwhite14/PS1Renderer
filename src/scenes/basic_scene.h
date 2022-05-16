#pragma once

#include "scene.h"

class Basic_Scene : public Scene
{
private:
	Shader shader;

public:
	Basic_Scene();
	void Start();
	void Update();
	void Render();
};