#include "model.h"

Model::Model(Shader* shader, Mesh * mesh, Material * material)
    :m_shader(shader), m_mesh(mesh), m_material(material)
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
void Model::render( const glm::mat4& projection, const glm::mat4& view, const glm::vec3& eye, GLuint mode )
{
    m_shader->use();
    //set modelMatrix in shader
    m_shader->setUniformVec3("v_eye", eye); //set the "eye" vectors
    m_shader->setUniformMatrix4("m_view", view);
    m_shader->setUniformMatrix4("m_projection", projection);
    m_shader->setUniformMatrix4("m_model", getTransform());
    if(m_material)
        m_material->bind(m_shader); //bind material
    m_mesh->render(mode);
    if(m_material)
        m_material->unbind(m_shader);
}
void Model::setMaterial(Material* material)
{
    if(material)
        m_material = material;
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
//TODO Load material files
    //load phone coeeficients 
    //map_kd refers to texture
    //map_bump is normal map
    //newmtl means create new material
    //Generate a map of materials and
    //map<string, Material>

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
             	oss >>pos.x;
				oss >>pos.y;
				oss >>pos.z;
                positions.push_back(pos);
            }
            else if(tag == "vn")
            {
                glm::vec3 normal;
             	oss >>normal.x;
				oss >>normal.y;
				oss >>normal.z;
                normals.push_back(normal);
            }
            else if(tag == "vt")
            {
                glm::vec2 uv;
                //parse x y z into vertex
            	oss >>uv.x;
				oss >>uv.y;
                textureUVs.push_back(uv);
            }
            else if(tag == "f")
            {

                //Face = v/vt/vn  v/vt/vn  v/vt/vn 
                Vertex vertex;
				int index;
                //3 vertices for each
                std::string verts[3];
                std::getline(oss, verts[0], ' ');
                std::getline(oss, verts[1], ' ');
                std::getline(oss, verts[2], ' ');
                for(int i =0; i < 3; i++)
                {
                    //indices start at 1 for objs so sub by 1!
                    // so grab from vector at i-1
                    //write as "v/vt/vn " to parse or v/vt/vn
                    oss.str("");
                    oss.clear();
                    oss << verts[i] << ' ';
                    //get position
                    oss >> index;
					oss.get(); //skip / or \ws
                    vertex.position = positions[index-1];
                    //get texture uv
					std::getline(oss, temp, '/');
					
					if(temp.size() > 0 )
					{
					    vertex.textureUV = textureUVs[std::stoi(temp)-1];
					}
					//get normal
                    oss >> index;
					if(index <= normals.size()) 
						vertex.normal = normals[(index-1)];
					else{
						std::cout << index;
						std::cin.get();						                    
					}//add vertex
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
        }
        mesh = new Mesh(shader, &vertices[0], vertices.size(), &indices[0], indices.size(), dynamic);
        //pass shader to mesh to allow Mesh to get locations of vertex attributes
       model = new Model(shader, mesh, material);

    }
  //  else
 //       Log::error << "Model::loadObj: File not found:" << objFile;

    return model;
}
