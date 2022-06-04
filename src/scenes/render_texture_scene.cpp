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
    //unsigned int quadVAO, quadVBO;
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
    quadProg.SetUniform("ScreenTexture", 0);

    // framebuffer configuration
    // -------------------------
    //unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    //unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Wireframe Mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RenderTexture_Scene::CompileShaders()
{
    try
    {
        prog.CompileShader("shaders/basic_lit.vert");
        prog.CompileShader("shaders/basic_lit.frag");
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

void RenderTexture_Scene::Update(GLFWwindow* window, float deltaTime)
{
	// Per Frame Calculations
}

void RenderTexture_Scene::Render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);
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

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

    quadProg.Use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderTexture_Scene::CleanUp()
{
	// After Scene Closes
}
