#include "basic_scene.h" 
#include <GLFW/glfw3.h>
#include "../texture.h"
#include <glm/gtc/type_ptr.hpp>
#include "../drawables/cube.h"

Basic_Scene::Basic_Scene()
{ 
    this->light = PointLight
    (
        vec4(0.0f, 10.0f, 0.0f, 1.0f),
        vec3(0.8f),
        vec3(0.25f),
        vec3(0.0f)
    );
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

    cube.Init(new Cube(1.0f), vec3(0.25f, 0.25f, 0.25f), vec3(0.25f, 0.25f, 0.25f), vec3(0.25f, 0.25f, 0.25f), 64.0f);
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

    cube.Render(prog, light, view, model, projection);
}

void Basic_Scene::CleanUp() 
{
    debugWindow.CleanUp();
}