#version 130

//Material coeeficients for phong illumination
struct material
{
    float shininess;
    //ambient color of object
    vec3 ambient;
    //diffuse color of object
    vec3 diffuse;
    //specular color of object
    vec3 specular;  
};
uniform material mtl; //material definitions


uniform float time;
uniform sampler2D sampler0;


smooth in vec3 normal;	//vertex normals
smooth in vec3 position;   //position
in vec2 textureUV;	//texture coords
in vec3 eye;

void main()
{

    vec3 color = texture2D(sampler0, textureUV).xyz;
//LIGHT TODO

    vec3 light_pos  = vec3(0,0,sin(time)); //hard code for now


    //diffuse color for light
    vec3 l_d = vec3(1.0,1.0,1.0);
    //specular color for lights
    vec3 l_s = vec3(1.0,1.0,1.0);
    //ambient color for light
    vec3 l_a = vec3(0.0,0.0,0.0);

  
    //diffuse + specular + ambient = phong

    //incoming light (from light to point)
    vec3 l  = normalize(light_pos - position );
    //normal of the vertex
    vec3 n  = normalize(normal);
    //reflection from light
    vec3 v  = normalize(position - eye);
    //reflection from point to the camera
    vec3 r  = normal*dot(l, normal);

    //Diffuse - lambertian reflectance
    //cannot have negative intensity
    vec3 diffuse =  max(0, dot(n, l)) * mtl.diffuse * l_d;

    //Specular - blinn-phong
    //vector half way bewteen v and l
    vec3 h = normalize(v + l);
    vec3 specular = pow(dot(n, h), mtl.shininess)* mtl.specular * l_s;

    //Ambient - independent of camera
    vec3 ambient = mtl.ambient + l_a;

    gl_FragColor = vec4(ambient+diffuse+specular, 1.0);

}
