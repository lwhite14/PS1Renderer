#pragma once

#include <glm/glm.hpp>
using glm::mat4;

class Scene 
{
public:
	mat4 view, model, projection;

	virtual void Start() {};
	virtual void Update() {};
	virtual void Render() {};
};