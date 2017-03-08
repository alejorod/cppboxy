#ifndef GLH_DRAWABLE
#define GLH_DRAWABLE

#include <transformable.h>
#include <GL/glew.h>

namespace glh
{

class Drawable : public Transformable {
public:
  GLuint shader;
  GLuint vao;
  int count;

  Drawable();
  Drawable(GLuint, GLuint, int);
};

}

#endif
