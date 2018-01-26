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
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), width/height, 0.0001f, 50.0f);

    glm::vec3 pos(0,0,2);
    glm::vec3 dir(0,0,-1);
    glm::vec3 up(0,1,0);
    Camera camera(pos, dir, up);

    Shader shader("glsl/phong");
	if(!shader.valid())
        return -1;
    
    Model* suzanne = Model::loadObj(&shader, "res/suzanne.obj");
    Model* armadillo = Model::loadObj(&shader, "res/armadillo.obj");
    //material defs from http://devernay.free.fr/cours/opengl/materials.html
    Material materialGold(&shader,
        glm::vec3(0.24725,0.1995,0.0745), //ambient
        glm::vec3(0.75164,0.60648,0.22648),   //diffuse
        glm::vec3(0.628281,0.555802,0.366065),//specular
        0.4*128//shiniess
        );
	Material materialJade(&shader,
 	 	glm::vec3(0.135,0.2225 ,0.1575), //ambient
        glm::vec3(0.54,0.89,0.63 ),   //diffuse
        glm::vec3(0.316228,0.316228, 0.316228 ),//specular
        0.1*128//shiniess
        );
        Material materialEmerald(&shader,
        glm::vec3(0.0215,0.1745 ,0.0215), //ambient
        glm::vec3(0.07568,0.61424,0.07568 ),   //diffuse
        glm::vec3(0.633,0.727811, 0.633 ),//specular
        0.6*128//shiniess
        );

    int mouseX, mouseY;
	float time;
	while(window.isOpen())
    {
		time += 0.05;
    	shader.setUniformFloat("time", time);
        shader.setUniformVec3("ambientLight", glm::vec3(0,0,0));
		//camera.setPosition(glm::vec3(0,0,sin(time)));
        window.getMousePosition(mouseX, mouseY);
        window.clear(0,0,0,1);


	    suzanne->setMaterial(&materialGold);
        suzanne->scale(glm::vec3(0.5,0.5,0.5));
        suzanne->translate(glm::vec3(1.0,0.0,0));
        suzanne->rotate(time, glm::vec3(sin(time),cos(time),sin(cos(time))));
        suzanne->render(projection, camera.getView(), camera.getEye());
		
		armadillo->setMaterial(&materialEmerald);
		armadillo->scale(glm::vec3(1.0,1.0,1.0));
        armadillo->translate(glm::vec3(-0.4,-1.0,-1));
        armadillo->rotate(time, glm::vec3(0,1,0));
        armadillo->render(projection, camera.getView(), camera.getEye());

        window.update();
    }
    delete suzanne;
    delete armadillo;
    //close logger
    Log::close();
    return 0;
}
