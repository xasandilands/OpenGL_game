#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	//ref to the VBO
	GLuint VBORef;
	//constructor that takes vertices and size to create the VBO
	VBO(GLfloat* vertices, GLsizeiptr size);

	//binding and delete functions for the VBO
	void Bind();
	void Unbind();
	void Delete();
};

#endif
