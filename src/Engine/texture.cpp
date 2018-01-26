#include "texture.h"


Texture::Texture(Shader* shader, const GLchar* data, GLuint imgWidth, GLuint imgHeight, Sample sample)
:m_shader(shader)
{
	if(!m_shader)
		Log::error() << "Texture: Null shader!";
	m_texture;
	m_sample = sample;
	glGenTextures(1, &m_texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgWidth, imgHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

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
//static Texture *loadPNG(std::string filename);

void Texture::bind()
{
	//Activate Texture number <sample>
	glActiveTexture(GL_TEXTURE0 + m_sample); //
	if(m_shader)
		//set the uniform for sampler[0-GL_MAX_TEXTURE]
		m_shader->setUniformInt("sampler"+std::to_string(m_sample), m_sample);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}


