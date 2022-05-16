#include "basic_scene.h" 
#include <GLFW/glfw3.h>

Basic_Scene::Basic_Scene()
{

}

void Basic_Scene::Start()
{
	glEnable(GL_DEPTH_TEST);
	shader = Shader("shaders/basic.vert", "shaders/basic.frag");
}

void Basic_Scene::Update()
{

}

void Basic_Scene::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Use();
	shader.SetVec3("Colour", vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	SetMatrices(shader);
}
