#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "shader.h"


class Material 
{
public:
	Material(Shader* shader,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess );
	virtual ~Material();

	//static Material* loadMtl(std::string fileName);
	//Set the uniforms in the shader
	void bind();
private:
	//Phong coeeficients
	Shader* m_shader;
	glm::vec3 m_diffuse;
	glm::vec3 m_ambient;
	glm::vec3 m_specular;
	GLfloat m_shininess;

};

#endif //MATERIAL_H