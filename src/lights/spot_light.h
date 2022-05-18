#pragma once

#include "light.h"

using glm::vec3;
using glm::vec4;

class SpotLight : public Light 
{
public:
	vec3 direction;
	float exponent;
	float cutoff;

	SpotLight() {}

	SpotLight(vec4 position, vec3 ambientIntensity, vec3 diffuseIntensity, vec3 specularIntensity, vec3 direction, float exponent, float cutoff)
	{
		this->position = position;
		this->ambientIntensity = ambientIntensity;
		this->diffuseIntensity = diffuseIntensity;
		this->specularIntensity = specularIntensity;
		this->direction = direction;
		this->exponent = exponent;
		this->cutoff = cutoff;
	}
};