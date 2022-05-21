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
	GLSLProgram prog;
	vec3 Ka, Kd, Ks;
	float shininess;
	Drawable* drawable;

	void SetMatrices(mat4& view, mat4& model, mat4& projection);
public:
	RenderObj();

	void SetMaterial(vec3 Ka, vec3 Kd, vec3 Ks, float shininess);
	void Init(Drawable* drawable, std::string vertexPath, std::string fragmentPath);
	void Render(PointLight pointLight, mat4& view, mat4& model, mat4& projection);
};