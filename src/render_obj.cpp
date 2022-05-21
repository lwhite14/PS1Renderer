#include "render_obj.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

RenderObj::RenderObj() 
{ 
	this->drawable = nullptr;
	this->Ka = vec3(0.0f);
	this->Kd = vec3(0.0f);
	this->Ks = vec3(0.0f);
	this->shininess = 0.0f;
}

void RenderObj::SetMaterial(vec3 Ka, vec3 Kd, vec3 Ks, float shininess)
{
	this->Ka = Ka;
	this->Kd = Kd;
	this->Ks = Ks;
	this->shininess = shininess;
}

void RenderObj::Init(Drawable* drawable, std::string vertexPath, std::string fragmentPath)
{
	this->drawable = drawable;
	try 
	{
		prog.CompileShader("shaders/basic_lit.vert");
		prog.CompileShader("shaders/basic_lit.frag");
		prog.Link();
	}
	catch (GLSLProgramException& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void RenderObj::Render(PointLight pointLight, mat4& view, mat4& model, mat4& projection)
{
	prog.Use();
	prog.SetUniform("Material.Ka", Ka);
	prog.SetUniform("Material.Kd", Kd);
	prog.SetUniform("Material.Ks", Ks);
	prog.SetUniform("Material.Shininess", shininess);
	prog.SetUniform("Light.Position", view * pointLight.position);
	prog.SetUniform("Light.La", pointLight.ambientIntensity);
	prog.SetUniform("Light.Ld", pointLight.diffuseIntensity);
	prog.SetUniform("Light.Ls", pointLight.specularIntensity);
	model = mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	SetMatrices(view, model, projection);
	drawable->Render();
}

void RenderObj::SetMatrices(mat4& view, mat4& model, mat4& projection)
{
	mat4 mv = view * model;
	prog.SetUniform("MVP", projection * mv);
	prog.SetUniform("ModelViewMatrix", mv);
	prog.SetUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));	
}
