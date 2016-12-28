#ifndef GLH_BUFFER_MANAGER
#define GLH_BUFFER_MANAGER

#include <GL/glew.h>

namespace glh
{

class BufferManager
{
public:
  static GLuint create(GLfloat* data);
  static void bind(GLuint);
};

}

#endif
