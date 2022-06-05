#pragma once

#include <glm/glm.hpp>

class Light 
{
public:
	glm::vec4 position;
	glm::vec3 ambientIntensity;
	glm::vec3 diffuseIntensity;
	glm::vec3 specularIntensity;
};