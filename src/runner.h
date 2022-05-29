#pragma once

#include <iostream>
using std::string;
using std::cerr;
using std::endl;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "systeminformation.h"
#include "scenes/scene.h"
#include "scenes/basic_scene.h"

class Runner 
{
private:
	GLFWwindow* window;
	int fbw, fbh;
	float deltaTime;

public:
	Runner(string name, int width, int height) 
	{
		if (!glfwInit()) 
		{
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		if (!window)
		{
			cerr << "UNABLE TO CREATE OPENGL CONTEXT" << endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);

		glfwGetFramebufferSize(window, &fbw, &fbh);

		if (!gladLoadGL())
		{
			exit(-1);
		}

		SystemInformation::OutputInformation();

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	int Run(Scene& scene)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		scene.SetDimensions(fbw, fbh);
		scene.Start(window);
		scene.Resize(fbw, fbh);

		MainLoop(scene);

		scene.CleanUp();

		glfwTerminate();

		return EXIT_SUCCESS;
	}

private:
	float lastFrame;

	void MainLoop(Scene& scene) 
	{        
		while( ! glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) ) 
        {
            glfwSwapBuffers(window);
            glfwPollEvents();

			UpdateDeltaTime();
			scene.Render();
			scene.Update(window, deltaTime);
        }	
	}

	void UpdateDeltaTime() 
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
};
