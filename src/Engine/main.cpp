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
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), width/height, 0.1f, 50.0f);

    glm::vec3 pos(0,0,1);
    glm::vec3 dir(0,0,-1);
    glm::vec3 up(0,1,0);
    Camera camera(pos, dir, up);

    Shader shader("glsl/phong");
	if(!shader.valid())
        return -1;
    
    Model* suzanne = Model::loadObj(&shader, "res/suzanne.obj");
    //material defs from http://devernay.free.fr/cours/opengl/materials.html
    Material materialGold(&shader,
        glm::vec3(0.24725,0.1995,0.0745), //ambient
        glm::vec3(0.75164,0.60648,0.22648),   //diffuse
        glm::vec3(0.628281,0.555802,0.366065),//specular
        0.4*128//shiniess
        );
	Material materialTest(&shader,
 	 	glm::vec3(0.135,0.2225 ,0.1575), //ambient
        glm::vec3(0.54,0.89,0.63 ),   //diffuse
        glm::vec3(0.316228,0.316228, 0.316228 ),//specular
        0.2*128//shiniess
        );

    int mouseX, mouseY;
	float time;
	while(window.isOpen())
    {
		time += 0.05;
    	shader.setUniformFloat("time", time);
		//camera.setPosition(glm::vec3(0,0,sin(time)));
        window.getMousePosition(mouseX, mouseY);
        window.clear(0,0,0,1);


	    suzanne->setMaterial(&materialGold);
        suzanne->scale(glm::vec3(0.35,0.35,0.35));
        suzanne->translate(glm::vec3(0,0,1));
      //  suzanne->rotate(time, glm::vec3(0,1,0));
        suzanne->render(projection, camera.getView(), camera.getEye());
		
		suzanne->setMaterial(&materialTest);
		suzanne->scale(glm::vec3(0.15,0.15,0.15));
      suzanne->translate(glm::vec3(-0.3,0,1));
       //   suzanne->translate(glm::vec3(sin(time)*0.25,cos(time)*0.25,1));
       // suzanne->rotate(time, glm::vec3(0,1,0));
        suzanne->render(projection, camera.getView(), camera.getEye());

        window.update();
    }
    delete suzanne;

    //close logger
    Log::close();
    return 0;
}
