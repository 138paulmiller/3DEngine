#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "texture.h"


class Material 
{
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess );
	
	virtual ~Material();

	//static Material* loadMtl(std::string fileName);

	//Material handles textures so they will be destroyed when material is destroyed
	void setBaseTexture(Texture *baseTexture);
	void setNormalTexture(Texture *normalTexture);
	//Set the uniforms in the shader
	void bind(Shader * shader);
	void unbind(Shader* shader);
private:
	//Phong coeeficients
	glm::vec3 m_diffuse;
	glm::vec3 m_ambient;
	glm::vec3 m_specular;
	GLfloat m_shininess;
	Texture *m_baseTexture; 
	Texture *m_normalTexture;
};

#endif //MATERIAL_H
