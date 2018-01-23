#version 130

uniform float time;

uniform sampler2D sampler0;
in vec3 position;	//position
smooth in vec3 normal;	//vertex normals
in vec2 textureUV;	//texture coords
in vec3 eye;
void main()
{
    //material defs from http://devernay.free.fr/cours/opengl/materials.html
    vec3 light_pos  = vec3(sin(time),1,1); //hard code for now

    vec3 color = texture2D(sampler0, textureUV).xyz;

    float shininess = 0.4*128;
    //ambient color of object
    vec3 c_a = vec3(0.24725,0.1995,0.0745);
    //diffuse color of object
    vec3 c_d = vec3(0.75164,0.60648,0.22648);
    //specular color of object
    vec3 c_s = vec3(0.628281,0.555802,0.366065);

    //diffuse color for light
    vec3 l_d = vec3(1.0,1.0,1.0);
    //specular color for lights
    vec3 l_s = vec3(1.0,1.0,1.0);
    //ambient color for light
    vec3 l_a = vec3(0.0,0.0,0.0);

    //diffuse = c_d, l_d
    //specular = c_s, l_s
    //ambient = ca_, l_a
    //diffuse + specular + ambient = phong
    //c_d*l_d = [c_dr * l_dr, c_dbg * l_dg, c_db * l_db]  r,g,b = RGB


    //l = incoming light (from light to point)
    //n = normal of the vertex
    //r = reflection from light
    //v = from point to the camera

    vec3 l  = normalize(light_pos - position );
    vec3 n  = normalize(normal);
    vec3 v  = normalize(position - eye);
    vec3 r  = normal*dot(l, normal);

    //Diffuse - lambertian reflectance
    //cannot have negative intensity
    vec3 diffuse =  max(0, dot(n, l)) * c_d * l_d;

    //Specular - blinn-phong
    //vector half way bewteen v and l
    vec3 h = normalize(v + l);
    vec3 specular = pow(dot(n, h), shininess)* c_s * l_s;

    //Ambient - independent of camera
    vec3 ambient = c_a + l_a;

    gl_FragColor = vec4(ambient+diffuse+specular, 1.0);
}
