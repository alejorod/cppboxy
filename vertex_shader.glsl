#version 330 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in float in_occlusion;
layout(location = 4) in float in_yellow;

out vec4 color;

uniform mat4 MVP;

void main(){
  gl_Position = MVP * vec4(in_position, 1.0);
  float fogFactor = 1.0 - (300.0 - gl_Position.z) / (300.0 - 0.1);
  float directional = dot(normalize(in_normal), vec3(0.1, 0.4, 0.6));
  color = mix(vec4(in_color, 1.0), vec4(1.0, 1.0, 0.0, 1.0), clamp(in_yellow, 0.0, 0.9));
  color = mix(color, vec4(0.7, 0.7, 0.9, 1.0) * directional, 0.3);
  color = mix(color, vec4(0.0, 0.0, 0.9, 1.0), in_occlusion);
  color = mix(color, vec4(0.0, 0.0, 0.0, 1.0), clamp(fogFactor, 0.0, 1.0));
}
