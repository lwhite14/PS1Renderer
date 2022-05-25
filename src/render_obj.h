#pragma once

#include <glm/glm.hpp>
#include "drawables/drawable.h"
#include "glslprogram.h"
#include "lights/point_light.h"
using glm::vec3;
using glm::mat4;

class RenderObj 
{
private:
	vec3 Ka, Kd, Ks;
	float shininess;
	Drawable* drawable;

	void SetMatrices(GLSLProgram& prog, mat4& view, mat4& model, mat4& projection);
public:
	RenderObj();

	void Init(Drawable* drawable, vec3 Ka, vec3 Kd, vec3 Ks, float shininess);
	void Render(GLSLProgram& prog, PointLight pointLight, mat4& view, mat4& model, mat4& projection);
};