#include <camera.h>
#include <keyboard.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

glh::Camera::Camera(float radians, float ratio, float near, float far)
{
  projection_matrix = glm::perspective(glm::radians(radians), ratio, near, far);
}


glm::mat4 glh::Camera::get_projection_matrix()
{
  return projection_matrix;
}

glm::mat4 glh::Camera::get_view_matrix()
{
  return get_inverse_model_matrix();
}

void glh::Camera::update()
{
  glm::vec4 f_dir { 0.0f, 0.0f, -1.0f, 1.0f };
  glm::vec4 l_dir { -1.0f, 0.0f, 0.0f, 1.0f };

  if (glh::keyboard::is_pressed(glh::keyboard::LEFT)) {
    rotate(0.0f, 5.0f, 0.0f);
  }

  if (glh::keyboard::is_pressed(glh::keyboard::RIGHT)) {
    rotate(0.0f, -5.0f, 0.0f);
  }

  if (glh::keyboard::is_pressed(glh::keyboard::UP)) {
    rotate(5.0f, 0.0f, 0.0f);
  }

  if (glh::keyboard::is_pressed(glh::keyboard::DOWN)) {
    rotate(-5.0f, 0.0f, 0.0f);
  }

  f_dir = glm::normalize(get_rotation_matrix() * f_dir);
  l_dir = glm::normalize(get_rotation_matrix() * l_dir);

  if (glh::keyboard::is_pressed(glh::keyboard::S)) {
    translate(-f_dir[0], -f_dir[1], -f_dir[2]);
  }

  if (glh::keyboard::is_pressed(glh::keyboard::W)) {
    translate(f_dir[0], f_dir[1], f_dir[2]);
  }

  if (glh::keyboard::is_pressed(glh::keyboard::D)) {
    translate(-l_dir[0], -l_dir[1], -l_dir[2]);
  }

  if (glh::keyboard::is_pressed(glh::keyboard::A)) {
    translate(l_dir[0], l_dir[1], l_dir[2]);
  }

}
