#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <sstream>
#include <glm/gtx/transform.hpp>

#include "mesh.h"
#include "shader.h"
#include "material.h"
// after <glm/glm.hpp>
class Model
{
public:
    Model(Shader* shader, Mesh * mesh, Material * material);
    ~Model();


    void setMaterial(Material*material);
    
    void setShader(Shader* shader);
    //Render the model, with the given view projection matrix, and the viewer pos
    void render( const glm::mat4& projection, const glm::mat4& view, const glm::vec3& eye );
    static Model* loadObj(Shader* shader, std::string objFile, bool dynamic = false);

    //Rotates along vecs where 1 in xyz or z is the axis
    inline void rotate(GLfloat angle, glm::vec3 axis)   {m_rotation = glm::rotate( angle, axis);}

    inline void scale(glm::vec3 scaleVector)    {m_scale = glm::scale( scaleVector);}

    inline void translate(glm::vec3 translateVector)    {m_translation= glm::translate( translateVector);}

    //all transformations - scale, rotate then translate
    inline glm::mat4 getTransform(){return m_translation* m_rotation * m_scale;}
private:
    Mesh *m_mesh;
    Shader* m_shader;
    Material *m_material; //texture and shading
    //Translation, scale, and rotation matrix
    glm::mat4 m_scale;
    glm::mat4 m_translation;
    glm::mat4 m_rotation;
};

#endif // MODEL_H
