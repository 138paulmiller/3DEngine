#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 dir, glm::vec3 up)
{
    m_position = position;
    m_dir = dir;
    m_up = up;
}


void Camera::setPosition(glm::vec3 pos)
{
	m_position = pos;
}
glm::mat4 Camera::getView()
{
//    return glm::lookAt(m_position, m_target, m_up);
      return glm::lookAt(m_position, m_position+m_dir, m_up);
}

glm::vec3 Camera::getEye()
{
    return m_position;
}
