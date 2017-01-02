#version 330 core
layout(location = 0) in vec3 position;

out vec4 pos;

uniform mat4 MVP;

void main(){
  gl_Position = MVP * vec4(position, 1.0);
  pos = vec4(clamp(position.x, 0.2, 1.0), clamp(position.y, 0.2, 1.0), clamp(position.z, 0.2, 1.0), 1.0);
}
