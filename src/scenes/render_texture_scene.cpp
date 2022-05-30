#include "render_texture_scene.h"
#include "../texture.h"

RenderTexture_Scene::RenderTexture_Scene() 
{
    suzanne = ObjMesh::Load("media/models/suzanne.obj");
}

void RenderTexture_Scene::Start(GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);
    CompileShaders();

    view = mat4(1.0f);
    projection = mat4(1.0f);
   
}

void RenderTexture_Scene::CompileShaders()
{
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

void RenderTexture_Scene::Update(GLFWwindow* window, float deltaTime)
{
	// Per Frame Calculations
}

void RenderTexture_Scene::Render()
{
    glClearColor(0.0f, 0.25f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, 0.0f, -5.0f));
    prog.Use();
    prog.SetUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
    prog.SetUniform("Light.La", vec3(1.0f));
    prog.SetUniform("Light.Ld", vec3(1.0f));
    prog.SetUniform("Light.Ls", vec3(1.0f));
    prog.SetUniform("Material.Ka", vec3(0.6f, 0.25f, 0.25f));
    prog.SetUniform("Material.Kd", vec3(0.5f));
    prog.SetUniform("Material.Ks", vec3(0.5f));
    prog.SetUniform("Material.Shininess", 64.0f);
    mat4 mv = view * model;
    prog.SetUniform("MVP", projection * mv);
    prog.SetUniform("ModelViewMatrix", mv);
    prog.SetUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    suzanne->Render();
}

void RenderTexture_Scene::CleanUp()
{
	// After Scene Closes
}
