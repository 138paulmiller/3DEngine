#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
// include after <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
    Camera(glm::vec3 m_position=glm::vec3(2,2,-2),
           glm::vec3 m_target=glm::vec3(0,0,0),
           glm::vec3 m_up=glm::vec3(0,1,0));

	void setPosition(glm::vec3 pos);
    glm::mat4 getView();
    glm::vec3 getEye();
private:
    //position of camera in space
    glm::vec3 m_position;
    //direction to look
    glm::vec3 m_dir ;
    //vector pointing up
    glm::vec3 m_up ;
};

#endif // CAMERA_H
