#ifndef GLH_CAMARA
#define GLH_CAMARA

#include <transformable.h>
#include <glm/mat4x4.hpp>

namespace glh
{

class Camera : public Transformable
{
protected:
  glm::mat4 projection_matrix;

public:
  Camera(float, float, float, float);
  glm::mat4 get_projection_matrix();
  glm::mat4 get_view_matrix();
};
}

#endif
