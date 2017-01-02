#include <transformable.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

glh::Transformable::Transformable()
: tx(0.0f), ty(0.0f), tz(0.0f), sx(1.0f), sy(1.0f), sz(1.0f), pitch(0.0f), yaw(0.0f)
{}

void glh::Transformable::translate(float x, float y, float z)
{
  tx += x;
  ty += y;
  tz += z;
}

void glh::Transformable::scale(float x, float y, float z)
{
  sx += x;
  sy += y;
  sz += z;
}

void glh::Transformable::rotate(float p_angle, float y_angle, float r_angle)
{
  pitch += p_angle;
  yaw += y_angle;
  roll += r_angle;
}

glm::mat4 glh::Transformable::get_rotation_matrix()
{
  glm::mat4 pitch_matrix = glm::rotate(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 yaw_matrix = glm::rotate(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 roll_matrix = glm::rotate(glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));

  return pitch_matrix * yaw_matrix * roll_matrix;
}

glm::mat4 glh::Transformable::get_inverse_rotation_matrix()
{
  glm::mat4 pitch_matrix = glm::rotate(glm::radians(-pitch), glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 yaw_matrix = glm::rotate(glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 roll_matrix = glm::rotate(glm::radians(-roll), glm::vec3(0.0f, 0.0f, 1.0f));

  return  pitch_matrix * yaw_matrix * roll_matrix;
}

glm::mat4 glh::Transformable::get_model_matrix()
{
  glm::mat4 translation_matrix = glm::translate(glm::vec3(tx, ty, tz));
  glm::mat4 scale_matrix = glm::scale(glm::vec3(sx, sy, sz));

  return translation_matrix * get_rotation_matrix() * scale_matrix;
}

glm::mat4 glh::Transformable::get_inverse_model_matrix()
{
  glm::mat4 translation_matrix = glm::translate(glm::vec3(-tx, -ty, -tz));
  glm::mat4 scale_matrix = glm::scale(glm::vec3(1.0f / sx, 1.0f / sy, 1.0f / sz));

  return scale_matrix * get_inverse_rotation_matrix() * translation_matrix;
}
