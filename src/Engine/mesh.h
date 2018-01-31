#ifndef MESH_H
#define MESH_H

#include <map>
#include "shader.h"


struct Vertex
{
    Vertex(glm::vec3 position=glm::vec3(0,0,0), glm::vec3 normal=glm::vec3(0,0,0), glm::vec2 textureUV=glm::vec2(0,0));
    Vertex(const Vertex& other);

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureUV;
};

class Mesh
{
public:
    Mesh(Shader* shader, Vertex *vertices, GLuint numVertices, GLuint * indices, GLuint numIndices, bool dynamic=false );
    ~Mesh();
    //bind to use
    void render(GLuint mode=GL_TRIANGLES);

private:
    //Vertex Attributes
    enum ATTR
    {
        ATTR_POSITION=0, ATTR_NORMAL, ATTR_TEXTUREUV, ATTR_COUNT
    };


    //VAO
    GLuint m_vertexArray;
    //VBO
    GLuint m_vertexBuffer;
    //EBO
    GLuint m_elementBuffer;
    //Attributes in vertex buffer
    std::map<ATTR, GLuint> m_vertexAttribs;
    //number to draw
    GLuint m_numIndices;
    GLuint m_numVertices;
};

#endif // MESH_H
