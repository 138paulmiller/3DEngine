#include "window.h"
#include "model.h"
#include "camera.h"

int main(int argc, char**argv)
{
    //open log with std::cout
    Log::open();
    GLfloat width  = 1080;
    GLfloat height = 720;
    Window window("3DEngine", width, height);
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), width/height, 0.1f, 5.0f);

    glm::vec3 pos(0,0,0);
    glm::vec3 dir(0,0,-1);
    glm::vec3 up(0,1,0);
    Camera camera(pos, dir, up);

    Shader shader("glsl/phong");
    if(!shader.valid())
        return -1;
    
    Model* suzanne = Model::loadObj(&shader, "res/suzanne.obj");
    
    Material materialGold(&shader,
        glm::vec3(0.24725,0.1995,0.0745), //ambient
        glm::vec3(0.75164,0.60648,0.22648),   //diffuse
        glm::vec3(0.628281,0.555802,0.366065),//specular
        0.4*128//shiniess
        );

    suzanne->setMaterial(&materialGold);
    float time=0;
    int mouseX, mouseY;
    while(window.isOpen())
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        time += 0.05;
        window.getMousePosition(mouseX, mouseY);
        window.clear(0,0,0,1);
        suzanne->scale(glm::vec3(0.45,0.45,0.45));
        //suzanne->translate(glm::vec3(0,0,sin(time)));
        suzanne->rotate(time, glm::vec3(0,1,0));
        shader.setUniformFloat("time",time);
        suzanne->render(projection, camera.getView(), camera.getEye());
        window.update();
    }
    delete suzanne;
    warn() << "Warning\n";
    //close logger
    Log::close();
    return 0;
}
