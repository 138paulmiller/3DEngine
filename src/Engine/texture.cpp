#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const unsigned char* data, GLuint imgWidth, GLuint imgHeight, Sample sample)
{
	m_texture;
	m_sample = sample;
	glGenTextures(1, &m_texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//unbind
	glBindTexture(GL_TEXTURE_2D, 0);

}
Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);

}
//load from PNG file
Texture *Texture::load(std::string filename, Sample sample)
{
	int w,h,n;
	unsigned char *data = stbi_load(filename.c_str(), &w, &h, &n, 0);
	Texture * texture = new Texture(data, w, h, sample);
    stbi_image_free(data);
    return texture;
}
void Texture::bind(Shader* shader)
{
	//Activate Texture number <sample>
	glActiveTexture(GL_TEXTURE0 + m_sample); //
	if(shader)
		//set the uniform for sampler[0-GL_MAX_TEXTURE]
		shader->setUniformInt("sampler"+std::to_string(m_sample), m_sample);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}


