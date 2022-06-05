#pragma once

#include "light.h"

using glm::vec3;
using glm::vec4;

class PointLight : public Light
{
public:

	PointLight() {}

	PointLight(vec4 position, vec3 ambientIntensity, vec3 diffuseIntensity, vec3 specularIntensity) 
	{
		this->position = position;
		this->ambientIntensity = ambientIntensity;
		this->diffuseIntensity = diffuseIntensity;
		this->specularIntensity = specularIntensity;
	}
};