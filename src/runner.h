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
#include "gui.h"

class Runner 
{
private:
	GUI gui;
	GLFWwindow* window;
	int fbw, fbh;

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

		gui = GUI();
		gui.Init(window);
	}

	int Run(Scene& scene)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		scene.SetDimensions(fbw, fbh);
		scene.Start();
		scene.Resize(fbw, fbh);

		MainLoop(scene);

		gui.CleanUp();

		glfwTerminate();

		return EXIT_SUCCESS;
	}

private:
	void MainLoop(Scene& scene) 
	{        
		while( ! glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) ) 
        {
            glfwSwapBuffers(window);
            glfwPollEvents();

			scene.Update(window);
			scene.Render();

			gui.PerFrame();
        }	
	}
};
