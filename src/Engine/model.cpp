#include "model.h"

Model::Model(Shader* shader, Mesh * mesh, Material * material, Texture* texture)
    :m_shader(shader), m_mesh(mesh), m_material(material), m_texture(texture)
{
    //identity matrix
    m_scale = glm::mat4(1);
    m_rotation= glm::mat4(1);
    m_translation= glm::mat4(1);
}

Model::~Model()
{
    //only delete mesh. Shaders and material are shared
    if(m_mesh)
        delete m_mesh;
}
//view projection matrix,
void Model::render( const glm::mat4& projection, const glm::mat4& view, const glm::vec3& eye )
{
    m_shader->use();
    //set modelMatrix in shader
    m_shader->setUniformVec3("v_eye", eye); //set the "eye" vectors
    m_shader->setUniformMatrix4("m_view", view);
    m_shader->setUniformMatrix4("m_projection", projection);
    m_shader->setUniformMatrix4("m_model", getTransform());
    if(m_material)
        m_material->bind(); //bind material
    if(m_texture)
        m_texture->bind();
    m_mesh->render();
}
void Model::setMaterial(Material* material)
{
    if(material)
        m_material = material;
}
void Model::setTexture(Texture * texture)
{
    if(texture)
        m_texture = texture;
}

void Model::setShader(Shader* shader)
{
    if(shader)
        m_shader = shader;
}
Model* Model::loadObj(Shader *shader, std::string objFile, bool dynamic)
{
    Model* model;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureUVs;
    //faces determine indices
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint indexCount = 0;
    std::ifstream inFile(objFile);

    Material *material  = 0;
    Mesh* mesh = 0;
    Texture* texture = 0;
    if(inFile.is_open())
    {
        std::string line, tag, temp;
        //parse line
        //usemtl texture
        //v     vertex  : x y z
        //vt    textureUV :  u v
        //vn    normals : x y z
        //f     face : v, v/vt, v/vt/vn or v//vn
        std::stringstream oss;
        while(std::getline(inFile, line, '\n'))
        {
            oss << line << ' ';
            oss.flush(); //flush data to be read
            std::getline(oss, tag, ' ');

            if(tag == "v")
            {
                glm::vec3 pos;
                //parse x y z into vertex
                std::getline(oss, temp, ' ');
                pos.x = std::stof(temp);
                std::getline(oss, temp, ' ');
                pos.y = std::stof(temp);
                std::getline(oss, temp, ' ');
                pos.z = std::stof(temp);
                positions.push_back(pos);
            }
            else if(tag == "vn")
            {
                glm::vec3 normal;
                //parse x y z into vertex
                std::getline(oss, temp, ' ');
                normal.x = std::stof(temp);
                std::getline(oss, temp, ' ');
                normal.y = std::stof(temp);
                std::getline(oss, temp, ' ');
                normal.z = std::stof(temp);
                normals.push_back(normal);
            }
            else if(tag == "vt")
            {
                glm::vec2 uv;
                //parse x y z into vertex
                std::getline(oss, temp, ' ');
                uv.x = std::stof(temp);
                std::getline(oss, temp, ' ');
                uv.y = std::stof(temp);
                textureUVs.push_back(uv);
            }
            else if(tag == "f")
            {

                //assume v/vt/vn is getline fails add vec(0)
                Vertex vertex;

                //3 vertices for each
                std::string lines[3];
                std::getline(oss, lines[0], ' ');
                std::getline(oss, lines[1], ' ');
                std::getline(oss, lines[2], ' ');

                for(int i =0; i < 3; i++)
                {
                    //indices start at 1 for objs
                    // so grab from vector at i-1
                    //write as "v/vt/vn " to parse or v/vt/vn
                    oss.str("");
                    oss.clear();
                    oss << lines[i] << ' ';
                    //get position
                    std::getline(oss, temp, '/');
                    vertex.position = positions[std::stoi(temp)-1];
                    //get texture uv
                    std::getline(oss, temp, '/');
                    if(temp.size()==0)
                        //set to invalid uv
                        vertex.textureUV = glm::vec2(-1);
                    else    
                        vertex.textureUV = textureUVs[std::stoi(temp)-1];
                    //get normal
                    std::getline(oss, temp, ' ');
                    vertex.normal = normals[std::stoi(temp)-1];
                    //add vertex
                    vertices.push_back(vertex);
                    indices.push_back(indexCount++);
                }

            }
            else if(tag == "usemtl")
            {
                //TODO
                //load material coeffs and texture from mtl file with same basename!
            }
            //clear any flags and reset buffer as empty
            oss.str("");
            oss.clear();
        }
        mesh = new Mesh(shader, &vertices[0], vertices.size(), &indices[0], indices.size(), dynamic);
        //pass shader to mesh to allow Mesh to get locations of vertex attributes
        model = new Model(shader, mesh, material,texture);

    }
  //  else
 //       Log::error << "Model::loadObj: File not found:" << objFile;

    return model;
}
