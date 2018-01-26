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
uniform vec3 ambientLight; //background light

smooth in vec3 normal;	//vertex normals
smooth in vec3 position;   //position
in vec2 textureUV;	//texture coords
in vec3 eye;

void main()
{

    vec3 color = texture2D(sampler0, textureUV).xyz;
//LIGHT TODO

    vec3 l_pos  = vec3(3*sin(time),cos(time)*3,sin(time)*3); //hard code for now

    //diffuse color for light
    vec3 l_d = vec3(1.0,1.0,1.0);
    //specular color for lights
    vec3 l_s = vec3(1.0,1.0,1.0);

  

//for each light

    //incoming light (from light to point)
    vec3 l  = normalize(l_pos - position );
    
    //normal of the vertex
    vec3 n  = normalize(normal);
    
    //direction from position to eye 
    vec3 v  = normalize(position - eye);

    //reflection from light
    vec3 r  = 2*dot(l, n)*n-l;

    //Diffuse - lambertian reflectance
    //cannot have negative intensity
    vec3 diffuse =  max(0, dot(l, n)) * mtl.diffuse * l_d;

    //Specular - blinn-phong
    //vector half way bewteen v and l
    vec3 h = normalize(v + l);
    //vec3 specular = pow(dot(n, h), mtl.shininess)* mtl.specular * l_s;

    vec3 specular = pow(dot(r, v), mtl.shininess)* mtl.specular * l_s;
//end for each light
    //Ambient - independent of camera
    vec3 ambient = mtl.ambient + ambientLight;

    //phong = ambient + foreach(light){diffuse + specular } 

    gl_FragColor = vec4(ambient+diffuse+specular, 1.0);

}
