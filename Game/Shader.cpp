#include"Shader.h"

// Function to read the content of a file and return it as a string
std::string get_file_content(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string content;
		in.seekg(0, std::ios::end);
		content.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&content[0], content.size());
		in.close();
		return(content);
	}
	throw std::runtime_error(std::string("Failed to open file: ") + filename);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	GLint success;
	GLchar infoLog[1024];

	//reads the vertex and fragment shader files and stores contents in strings
	std::string vertexContents = get_file_content(vertexFile);
	std::string fragmentContents = get_file_content(fragmentFile);

	//converts strings into character arrays
	const char* vertexSource = vertexContents.c_str();
	const char* fragmentSource = fragmentContents.c_str();

	//create vertex and fragment shader objs
	GLuint vertexShader, fragmentShader;
	//gets refrence of vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//compile the vertex shader
	glCompileShader(vertexShader);
	//check if compilation was successful
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << "ERROR VERTEX SHADER COMPILATION FAILED\n" << infoLog << std::endl;
	}

	//gets reference of fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//compile the fragment shader
	glCompileShader(fragmentShader);
	//check if compilation was successful
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		std::cout << "ERROR FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
	}

	//create the shader program
	shadRef = glCreateProgram(); 
	//links the vertex and fragment shaders to the shader program
	glLinkProgram(shadRef);
	
	//delete the vertex and fragment shaders they are not needed anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	//activates the shader program
	glUseProgram(shadRef);
}

void Shader::Delete()
{
	//deletes the shader program
	glDeleteProgram(shadRef);
}


