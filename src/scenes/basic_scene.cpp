#include "basic_scene.h" 
#include <GLFW/glfw3.h>
#include "../texture.h"
#include <glm/gtc/type_ptr.hpp>

Basic_Scene::Basic_Scene() : cube(1.0f) { }

void Basic_Scene::Start()
{
	glEnable(GL_DEPTH_TEST);
	shader = Shader("shaders/basic.vert", "shaders/basic.frag");

    tex1 = Texture::LoadTexture("media/images/container.jpg");
    tex2 = Texture::LoadTexture("media/images/awesomeface.png");

    shader.Use();
    shader.SetVec3("Colour", vec3(1.0f, 0.0f, 0.0f));
}

void Basic_Scene::Update()
{

}

void Basic_Scene::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2);

    shader.Use();

    glm::mat4 model = glm::mat4(1.0f); 
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    shader.SetMat4("projection", projection);

    cube.Render();
}
