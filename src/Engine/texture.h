
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include "shader.h"

/*
	Basic 2D Texture
*/
class Texture
{
public:
	//which texture sample in shader 0-3
	enum Sample 
	{
		SAMPLE_0=0,
		SAMPLE_1,SAMPLE_2, 
		SAMPLE_3
	};
	Texture(Shader* shader, const GLchar* data, GLuint imgWidth, GLuint imgHeight, Sample sample);
	virtual ~Texture();
	//load from PNG file
	//static Texture *loadPNG(std::string filename);
	
	//Bind for shader to use 
	virtual void bind();


private:
	//Teture to bind
	GLuint m_texture;
	//uniform location
	Sample m_sample;
	//Shader to bind to
	Shader * m_shader;
};

#endif