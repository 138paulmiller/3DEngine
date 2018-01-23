#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

#include "glm/glm.hpp"
#include "log.h"
class Shader
{
public:
    //Expects filename, and parses filename.vs and filename.fs
    Shader(std::string filename);
    ~Shader();

    bool valid();
    void use();

    GLuint getAttribLocation(std::string id);
    GLuint getUniformLocation(std::string id);
    void setUniformFloat(std::string id, GLfloat value);
    void setUniformVector(std::string id, const GLfloat* vector, GLuint numComponents);
    void setUniformMatrix4(std::string id, const glm::mat4& matrix);

protected:
    static bool checkError(GLuint shader, GLuint flag, bool isProgram=false);

    GLuint loadShader(std::string filename, GLuint type);
private:
    //Enums for each shader stage in program
    enum ShaderType{VERTEX=0, FRAGMENT, NUM_SHADERS};
    //Shader stages
    GLuint m_shaders[NUM_SHADERS];
    //Shader program
    GLuint m_program;
    bool m_valid; //if shader is valid
};

#endif // SHADER_H
