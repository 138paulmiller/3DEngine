#include "shader.h"

Shader::Shader(std::string filename)
{
    m_shaders[VERTEX] = loadShader(filename+".vs", GL_VERTEX_SHADER);
    m_shaders[FRAGMENT] = loadShader(filename+".fs", GL_FRAGMENT_SHADER);
    //link programs
    m_program = glCreateProgram();
    for(int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);
    glLinkProgram(m_program);
    debug() << "Linking program ...\n";
    if(m_valid)
        m_valid = checkError(m_program, GL_LINK_STATUS, true);
    glValidateProgram(m_program);
    debug() << "Validating program ...\n";
    if(m_valid)
        m_valid = checkError(m_program, GL_VALIDATE_STATUS, true);
}


Shader::~Shader()
{

    for(int i = 0; i < NUM_SHADERS; i++)
        if(m_shaders[i])
        {
            glDetachShader(m_program, m_shaders[i]);
            glDeleteShader(m_shaders[i]); // removes

        }
    if(m_program)
        glDeleteProgram(m_program);

}
bool Shader::valid()
{
    return m_valid;
}
GLuint Shader::loadShader(std::string filename, GLuint type)
{
    //Open and read file into string
    std::string text = "";
    std::ifstream fileIn(filename);
    if(fileIn.is_open())
    {
        std::string line = "";
        while(std::getline(fileIn, line))
            text+= line+"\n";
        fileIn.close();
    }
    //Compile program
    GLuint shader = glCreateShader(type);
    const GLchar* source = (GLchar*)(text.c_str());
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    debug() << "\nCompiling " << (type==GL_VERTEX_SHADER?"VERTEX":"FRAGMENT") << " shader \n";
    if(!checkError(shader, GL_COMPILE_STATUS))
        m_valid = shader = 0;
    return shader;
}

GLuint Shader::getAttribLocation(std::string id)
{
    int location = glGetAttribLocation(m_program, id.c_str());
    if(location < 0)
        error() << "Shader: Could not get attrib:" << id << " \n";
    return location;
}
GLuint Shader::getUniformLocation(std::string id)
{
    int location = glGetUniformLocation(m_program, id.c_str());
    if(location< 0)
        error() << "Shader: Could not get uniform:" << id << " \n";
    return location;
}
void Shader::setUniformFloat(std::string id,  GLfloat value)
{
    int location = getUniformLocation(id);
    //set the vector as you would an array since in GLSL vectors are "essentially" arrays
    if(location >= 0)
        glUniform1f(location, value);
}

void Shader::setUniformVector(std::string id, const GLfloat* vector, GLuint numComponents)
{
    int location = getUniformLocation(id);
    //set the vector as you would an array since in GLSL vectors are "essentially" arrays
    if(location >= 0)
        glUniform1fv(location, numComponents, vector);
}
void Shader::setUniformMatrix4(std::string id, const glm::mat4& matrix)
{
    int location = getUniformLocation(id);
    if(location >= 0)
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}


bool Shader::checkError(GLuint shader, GLuint flag,  bool isProgram)
{
    GLint status = 0;
    isProgram?
        glGetProgramiv(shader, flag, &status )
        :glGetShaderiv(shader, flag, &status );
    if(status == GL_FALSE)
    {
        GLint errorLen = 0;
        isProgram?
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorLen)
            :glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLen);
        char* errorMsg = new char[errorLen];
        isProgram?
            glGetProgramInfoLog(shader, errorLen, &errorLen, errorMsg)
            :glGetShaderInfoLog(shader, errorLen, &errorLen, errorMsg);
        error() << errorMsg;
        delete errorMsg;
        return false;
   }
    return true;
}

void Shader::use()
{
    glUseProgram(m_program);
}
