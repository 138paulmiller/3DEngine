#include "material.h"

Material::Material(Shader* shader, glm::vec3 ambient, glm::vec3 diffuse,glm::vec3 specular, GLfloat shininess )
:	m_shader(shader), 
	m_diffuse(diffuse), 
	m_ambient(ambient),
	m_specular(specular),
	m_shininess(shininess)
{
	if(!shader)
		error() << "Material has null shader!\n";
}

Material::~Material()
{}

//static Material* Material::loadMtl(std::string fileName);

void Material::bind()
{
	m_shader->setUniformVec3("mtl.ambient", m_ambient);
	m_shader->setUniformVec3("mtl.diffuse", m_diffuse);
	m_shader->setUniformVec3("mtl.specular",m_specular);
	m_shader->setUniformFloat("mtl.shininess",m_shininess);
}
