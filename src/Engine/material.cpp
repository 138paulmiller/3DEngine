#include "material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse,glm::vec3 specular, GLfloat shininess ) 
:	m_diffuse(diffuse), 
	m_ambient(ambient),
	m_specular(specular),
	m_shininess(shininess)
{
m_baseTexture= 0;
m_normalTexture= 0;
}

Material::~Material()
{}
void Material::setBaseTexture(Texture *baseTexture)
{
	m_baseTexture = baseTexture;
}
void Material::setNormalTexture(Texture *normalTexture)
{
	m_normalTexture = normalTexture;
}
//static Material* Material::loadMtl(std::string fileName);

void Material::bind(Shader* shader)
{
	if(m_baseTexture)
		m_baseTexture->bind(shader);
	if(m_normalTexture)
		m_normalTexture->bind(shader);
	shader->setUniformVec3("mtl.ambient", m_ambient);
	shader->setUniformVec3("mtl.diffuse", m_diffuse);
	shader->setUniformVec3("mtl.specular",m_specular);
	shader->setUniformFloat("mtl.shininess",m_shininess);
}
void Material::unbind(Shader* shader)
{
	if(m_baseTexture)
		m_baseTexture->unbind(shader);
	if(m_normalTexture)
		m_normalTexture->unbind(shader);
}
