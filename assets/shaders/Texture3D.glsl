#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec4 v_Color;

void main() {
  v_Color = a_Color;
  gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

//// ---------------------------------------------- ////
//// ---------------------------------------------- ////

#type fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec4 v_Color;

void main() { FragColor = v_Color; }
