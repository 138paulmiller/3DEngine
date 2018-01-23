#version 130

//Streamed values
attribute vec3 v_position;
attribute vec3 v_normal;
attribute vec2 v_textureUV;

uniform vec3 v_eye;
//Matrices
uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

//to be sent to frag shader
out vec3 position;
smooth out vec3 normal;
out vec2 textureUV;
out vec3 eye; //view vector
void main(){
   eye = v_eye;
   normal = (m_view * m_model* vec4(v_normal,1)).xyz ;
   textureUV = v_textureUV;
   position = (m_projection * m_view * m_model * vec4(v_position,1)).xyz;
   gl_Position = vec4(position, 1.0);
}
