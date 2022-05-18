#include "basic_scene.h" 
#include <GLFW/glfw3.h>
#include "../texture.h"
#include <glm/gtc/type_ptr.hpp>

Basic_Scene::Basic_Scene() :    cube(1.0f),
                                light
                                (
                                    vec4(5.0f, 5.0f, 5.0f, 1.0f),
                                    vec3(0.8f),
                                    vec3(0.25f),
                                    vec3(0.0f)
                                )
{ 

}

void Basic_Scene::Start(GLFWwindow* window)
{
    debugWindow = DebugWindow();
    debugWindow.Init(window);
    debugWindow.lightPos[0] = light.position.x;
    debugWindow.lightPos[1] = light.position.y;
    debugWindow.lightPos[2] = light.position.z;
    debugWindow.lightAmbient[0] = light.ambientIntensity.x;
    debugWindow.lightAmbient[1] = light.ambientIntensity.y;
    debugWindow.lightAmbient[2] = light.ambientIntensity.z;
    debugWindow.lightDiffuse[0] = light.diffuseIntensity.x;
    debugWindow.lightDiffuse[1] = light.diffuseIntensity.y;
    debugWindow.lightDiffuse[2] = light.diffuseIntensity.z;
    debugWindow.lightSpecular[0] = light.specularIntensity.x;
    debugWindow.lightSpecular[1] = light.specularIntensity.y;
    debugWindow.lightSpecular[2] = light.specularIntensity.z;
    camera = Camera(width, height, vec3(0.0f, 0.0f, 3.0f));

	glEnable(GL_DEPTH_TEST);
	//shader = Shader("shaders/basic_lit.vert", "shaders/basic_lit.frag");
    prog.CompileShader("shaders/basic_lit.vert");
    prog.CompileShader("shaders/basic_lit.frag");
    prog.Link();

    view = mat4(1.0f);
    projection = mat4(1.0f);
}

void Basic_Scene::Update(GLFWwindow* window, float deltaTime)
{
    camera.Movement(deltaTime);
    camera.KeyCallback(window);
    camera.MouseCallback(window);

    light.position = vec4(debugWindow.lightPos[0], debugWindow.lightPos[1], debugWindow.lightPos[2], 1.0f);
    light.ambientIntensity = vec3(debugWindow.lightAmbient[0], debugWindow.lightAmbient[1], debugWindow.lightAmbient[2]);
    light.diffuseIntensity = vec3(debugWindow.lightDiffuse[0], debugWindow.lightDiffuse[1], debugWindow.lightDiffuse[2]);
    light.specularIntensity = vec3(debugWindow.lightSpecular[0], debugWindow.lightSpecular[1], debugWindow.lightSpecular[2]);

    debugWindow.PerFrame();
}

void Basic_Scene::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = camera.ChangeViewMatrix(view);

    prog.Use();
    prog.SetUniform("Material.Ka", vec3(0.5f, 0.5f, 0.5f));
    prog.SetUniform("Material.Kd", vec3(0.85f, 0.85f, 0.85f));
    prog.SetUniform("Material.Ks", vec3(1.0f, 1.0f, 1.0f));
    prog.SetUniform("Material.Shininess", 64.0f);
    prog.SetUniform("Light.Position", light.position);
    prog.SetUniform("Light.La", light.ambientIntensity);
    prog.SetUniform("Light.Ld", light.diffuseIntensity);
    prog.SetUniform("Light.Ls", light.specularIntensity);
    model = mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    SetMatrices(prog);
    cube.Render();
}

void Basic_Scene::CleanUp() 
{
    debugWindow.CleanUp();
}