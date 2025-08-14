#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_content(const char* filename);

class Shader
{
	public:
		//reference of shader program
		GLuint shadRef;
		//constructor that takes vertex and fragment shader file names to build the shader program
		Shader(const char* vertexFile, const char* fragmentFile);

		//activate the shader program
		void Activate();
		//delete the shader program
		void Delete();
		void compileErrors(unsigned int shader, const char* type);
};

#endif