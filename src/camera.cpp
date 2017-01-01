#include <camera.h>
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
