#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

//height and width of the window
int width = 1500;
int height = 800;

//triangle vertices
float vertices1[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
};

float vertices2[] = {
     0.5f, -0.5f, 0.0f,
     1.0f, -0.5f, 0.0f,
     0.75f, 0.5f, 0.0f,
};

GLuint indices[] =
{
	0, 1, 2,
    1, 3, 4
};

int main()
{
	// Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//initialize the window
    GLFWwindow* window = glfwCreateWindow(width, height, "test", NULL, NULL);
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

	GLint success;
	GLchar infoLog[1024];

	//shaders
    GLuint vertexShader, fragmentShader1, fragmentShader2;

	//create the vertex shader and compile
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

	//check for compilation errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::cout << " ERROR IN VERTEX SHADER COMPILATION" << infoLog << std::endl;
    }

	//create the fragment shader and compile
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader1);

	//check for compilation errors
    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::cout << " ERROR IN FRAGMENT SHADER 1 COMPILATION" << infoLog << std::endl;
    }
    
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::cout << " ERROR IN FRAGMENT SHADER 2 COMPILATION" << infoLog << std::endl;
    }



	//create the shader program and attach the shaders
	GLuint shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
	//link the shader program
	glLinkProgram(shaderProgram1);

	//check for linking errors
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if(success == GL_FALSE)
    {
        std::cout << " ERROR IN SHADER PROGRAM 1 LINKING" << infoLog << std::endl;
	}

	GLuint shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2,vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::cout << " ERROR IN SHADER PROGRAM 2 LINKING" << infoLog << std::endl;
    }

    GLuint VBOs[2], VAOs[2], EBO;

	//bind the VBO and generate the buffer
	glGenBuffers(2, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);


    //generate and bind the VAO
    glGenVertexArrays(2, VAOs);
    glBindVertexArray(VAOs[0]);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //passes data(vectices) to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//tell openGL how to interpret the vertex data (attribute, layout, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//while loop to keep the window open
    while (!glfwWindowShouldClose(window))
    {
		//set the background color and clear the buffers
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//swap back buffer with front buffer and poll for events
		glfwSwapBuffers(window);
        glfwPollEvents();
    }
	//clean up and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}