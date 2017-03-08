#ifndef GLH_TRANSFORMABLE
#define GLH_TRANSFORMABLE

#include <glm/mat4x4.hpp>
#include <vector>

namespace glh
{

class Transformable
{
protected:
  float tx, ty, tz;
  float sx, sy, sz;
  float pitch, yaw, roll;

public:
  Transformable();
  void translate(float, float, float);
  void scale(float, float, float);
  void rotate(float, float, float);
  std::vector<int> get_position();

  glm::mat4 get_model_matrix();
  glm::mat4 get_inverse_model_matrix();
  glm::mat4 get_rotation_matrix();
  glm::mat4 get_inverse_rotation_matrix();

};

}

#endif
