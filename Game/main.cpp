#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//height and width of the window
int width = 1000;
int height = 800;

int main()
{
	// Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//initialize the window
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	//check if the window was created successfully
    if (window == NULL)
    {
        std::cout << "failed to initialize window" << std::endl;
        glfwTerminate();
        return -1;
    }
	// Set the current context to the window
    glfwMakeContextCurrent(window);

	//load OpenGL function pointers using GLAD and set the viewport
    gladLoadGL();
    glViewport(0, 0, width, height);

	//while loop to keep the window open
    while (!glfwWindowShouldClose(window))
    {
		//set the background color and clear the buffers
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//swap back buffer with front buffer and poll for events
		glfwSwapBuffers(window);
        glfwPollEvents();
    }
	//clean up and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;
}