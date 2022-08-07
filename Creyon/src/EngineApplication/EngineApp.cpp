#include "EngineApp.h"

namespace Creyon {

	EngineApp::EngineApp()
	{
		CreyonWindow::CreyonWindowInit();
		
		windowInstance = CreyonWindow(800,600, "Learnopengl");

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			cout << "Failed to initialize GLAD\n";
		}

		glViewport(0, 0, 800, 600);

		windowInstance.register_Callback();
	}

	void EngineApp::Run() {

		Shaderprogram programrect;
		
		programrect.addShader(
		"Render\\VertexShader.glsl", GL_VERTEX_SHADER);
		programrect.addShader(
		"Render\\FragmentShader.glsl",  GL_FRAGMENT_SHADER);
		
		programrect.link();

		//Set the data for rendering------------------------------------------------
		float vertices[]{ //position            //color
						  0.5f,  0.5f , 0.0f,	1.0f, 0.0f, 0.0f,
						  0.5f, -0.5f , 0.0f,	0.0f, 1.0f, 0.0f,
						 -0.5f, -0.5f , 0.0f,   0.0f, 0.0f, 1.0f,
						 -0.5f,  0.5f , 0.0f,	0.5f, 0.5f, 0.5f };

		unsigned int  indices[]{ 0, 1, 3,   //triangle 1
								 1, 2, 3 }; //triangle 2

		float texturecoords[]{
			0.0f, 0.0f,  //bottom-left
			1.0f, 0.0f,  //bottom-right
			0.0f, 1.0f,  //top-left
			1.0f, 1.0f  //top-right
		};

		//sampling texture colors
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//unbind vao
		glBindVertexArray(0);
		//---------------------------------------------------------------------------

		//Render loop
		while (!windowInstance.isWindowClosed()) {

			//Processes all Input
			windowInstance.processInput();

			//Render commands here------------------------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			programrect.useProgram();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			//---------------------------------------
			windowInstance.swapBuffers();
			windowInstance.pollWindowEvents();
			//---------------------------------------
		}
		CreyonWindow::CreyonWindowTerminate(windowInstance);
	}
}