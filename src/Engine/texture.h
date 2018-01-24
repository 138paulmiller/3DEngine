
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm/glm.hpp>

#include "shader.h"
class Texture
{
public:
	Texture(Shader* shader, const char* data);
	virtual ~Texture();
	//load from Mtl file
	//static Texture *loadTexture(std::string filename);
	
	//Bind for shader to use 
	virtual void bind();


private:
	//Teture to bind
	GLuint m_texture;
	//reference to shader to be used
	Shader* shader; 
};

#endif