#include "basic_scene.h" 
#include <GLFW/glfw3.h>
#include "../texture.h"
#include <glm/gtc/type_ptr.hpp>
#include "../drawables/cube.h"
#include "../drawables/obj_mesh.h"
#include "../drawables/quad.h"

Basic_Scene::Basic_Scene()
{ 
    this->light = PointLight
    (
        vec4(-5.0f, 5.0f, 5.0f, 1.0f),
        vec3(0.25f),
        vec3(0.45f, 0.45f, 0.6f),
        vec3(0.0f)
    );
    this->cameraSpeed = 1.0f;
    this->timer = 0.0f;
    this->startAngle = -90.0f;
    this->angleMultiplier = 15.0f;
    this->renderTexWidth = 320;
    this->renderTexHeight = 240;
    this->cratePositions = vector<vec3>
    {
        vec3(-4.0f, 0.5f, -1.0f),
        vec3(-1.0f, 0.5f, -2.0f),
        vec3(3.0f, 0.5f, -1.0f)
    };
    this->crateRotations = vector<float>
    {
        -33.0f, -80.0f, 10.0f
    };
    this->barrelPositions = vector<vec3>
    {
        vec3(-3.5f, 0.0f, 2.25f),
        vec3(-6.75f, 0.0f, -2.25f),
        vec3(6.75f, 0.0f, -2.25f),
        vec3(1.0f, 0.0f, -3.5f),
        vec3(6.0f, 0.0f, 1.0f)
    };
    this->barrelRotations = vector<float>
    {
        -21.0f, 
        45.0f, 
        45.0f,
        70.0f,
        0.0f
    };
    this->objectPosition = vec3(0.0f, 0.0f, 0.0f);
    this->objectRotation = 0.0f;
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
    camera = Camera(width, height, vec3(0.0f, 3.0f, 5.0f));
    camera.pitch = -25.0f;

	glEnable(GL_DEPTH_TEST);

    car.Init(ObjMesh::Load("media/models/car.obj"), vec3(0.25f), vec3(0.25f), vec3(0.25f), 256.0f, Texture::LoadTexturePtr("media/images/car.png"));
    road.Init(ObjMesh::Load("media/models/floor.obj"), vec3(0.25f), vec3(0.25f), vec3(0.25f), 256.0f, Texture::LoadTexturePtr("media/images/road.png"));
    buildings.Init(ObjMesh::Load("media/models/buildings.obj"), vec3(0.25f), vec3(0.25f), vec3(0.25f), 256.0f, Texture::LoadTexturePtr("media/images/buildingface.jpg"));
    crate.Init(new Cube(1.0f), vec3(0.25f), vec3(0.25f), vec3(0.25f), 256.0f, Texture::LoadTexturePtr("media/images/crate.jpg"));
    barrel.Init(ObjMesh::Load("media/models/barrel.obj"), vec3(0.25f), vec3(0.25f), vec3(0.25f), 256.0f, Texture::LoadTexturePtr("media/images/barrel.png"));

    CompileShaders();

    view = mat4(1.0f);  
    projection = mat4(1.0f);

    float quadVertices[] =
    {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    // Screen Quad VAO
    // unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Shader Calls
    quadProg.Use();
    quadProg.SetUniform("Texture", 0);

    // framebuffer configuration
    // -------------------------
    // unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    // unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderTexWidth, renderTexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, renderTexWidth, renderTexHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Wireframe Mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Basic_Scene::CompileShaders()
{
    try
    {
        prog.CompileShader("shaders/psx.vert");
        prog.CompileShader("shaders/psx.frag");
        prog.Link();   

        quadProg.CompileShader("shaders/quad.vert");
        quadProg.CompileShader("shaders/quad.frag");
        quadProg.Link();
    }
    catch (GLSLProgramException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Basic_Scene::Update(GLFWwindow* window, float deltaTime)
{

    camera.SetYaw((glm::sin(timer) * angleMultiplier) + startAngle);
    timer = timer + (deltaTime * cameraSpeed);

    camera.SetFront(window);
    view = camera.ChangeViewMatrix(view);

    light.position = vec4(debugWindow.lightPos[0], debugWindow.lightPos[1], debugWindow.lightPos[2], 1.0f);
    light.ambientIntensity = vec3(debugWindow.lightAmbient[0], debugWindow.lightAmbient[1], debugWindow.lightAmbient[2]);
    light.diffuseIntensity = vec3(debugWindow.lightDiffuse[0], debugWindow.lightDiffuse[1], debugWindow.lightDiffuse[2]);
    light.specularIntensity = vec3(debugWindow.lightSpecular[0], debugWindow.lightSpecular[1], debugWindow.lightSpecular[2]);

    objectPosition = vec3(debugWindow.objectPos[0], debugWindow.objectPos[1], debugWindow.objectPos[2]);
    objectRotation = debugWindow.objectRot[0];

    debugWindow.PerFrame();
}

void Basic_Scene::Render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.25f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, renderTexWidth, renderTexHeight);

    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    car.Render(prog, light, view, model, projection);
    road.Render(prog, light, view, model, projection);
    buildings.Render(prog, light, view, model, projection);

    for (unsigned int i = 0; i < cratePositions.size(); i++)
    {
        model = mat4(1.0f);
        model = glm::translate(model, cratePositions[i]);
        model = glm::rotate(model, glm::radians(crateRotations[i]), glm::vec3(0.0f, 1.0f, 0.0f));
        crate.Render(prog, light, view, model, projection);
    }

    for (unsigned int i = 0; i < barrelPositions.size(); i++)
    {
        model = mat4(1.0f);
        model = glm::translate(model, barrelPositions[i]);
        model = glm::rotate(model, glm::radians(barrelRotations[i]), glm::vec3(0.0f, 1.0f, 0.0f));
        barrel.Render(prog, light, view, model, projection);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);

    quadProg.Use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Basic_Scene::CleanUp() 
{
    debugWindow.CleanUp();
}