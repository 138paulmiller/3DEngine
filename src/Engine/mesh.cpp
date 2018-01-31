#include "mesh.h"

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 textureUV)
    :position(position), normal(normal), textureUV(textureUV)
{}

Vertex::Vertex(const Vertex& other)
    :position(other.position), normal(other.normal), textureUV(other.textureUV)
{}


Mesh::Mesh(Shader* shader, Vertex *vertices, GLuint numVertices, GLuint * indices, GLuint numIndices, bool dynamic )
{
    if(shader == 0)  //check shader!
		return;
    //create 1 VAO
    glGenVertexArrays(1, &m_vertexArray);
    //create the buffers
    glGenBuffers(1, &m_vertexBuffer);
    glGenBuffers(1, &m_elementBuffer);
    //bind VAO
    glBindVertexArray(m_vertexArray);

    //bind and buffer element data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

    //bind and buffer the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    //dynamic, wiil vertices be updated??
    glBufferData(GL_ARRAY_BUFFER, numVertices* sizeof(vertices[0]), vertices, dynamic?GL_DYNAMIC_DRAW:GL_STATIC_DRAW);

    //specify attributes in vertex buffer
    //add offset by number of components * size of previous attrib
    //pointer spec = (index,  numComponents , type, normlized, stride, offset_pointer)
    GLsizei stride = sizeof(Vertex);

    GLuint attrPosition = shader->getAttribLocation("v_position");
    GLuint attrNormal = shader->getAttribLocation("v_normal");
    GLuint attrTextureUV = shader->getAttribLocation("v_textureUV");

    if(attrPosition < 0 ){
        Log::error() << "Mesh: Position Attribute Not found!\n";
    }
	else
    {
        glVertexAttribPointer(attrPosition , 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(0*sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(attrPosition );
    }

    if(attrNormal < 0 ){
        Log::error() << "Mesh: Normal Attribute Not found!\n";
    }
	else
    {
        glVertexAttribPointer(attrNormal, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3*sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(attrNormal);
    }

    if(attrTextureUV < 0 ){
        Log::error() << "Mesh: Texture Attribute Not found!\n";
    }
	else
    {
        glVertexAttribPointer(attrTextureUV, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6*sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(attrTextureUV);
    }


    //unbind all used buffers and array indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    m_numIndices = numIndices;
    m_numVertices = numVertices;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArray);
    for(int i = 0; i < ATTR_COUNT; i++)
        glDisableVertexAttribArray(m_vertexAttribs[ATTR_POSITION]);
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_elementBuffer);

}

//bind to use
void Mesh::render(GLuint mode)
{
    //bind the VAO and its element buffer
    glBindVertexArray(m_vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glDrawElements(mode, m_numIndices, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
