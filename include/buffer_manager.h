#ifndef GLH_BUFFER_MANAGER
#define GLH_BUFFER_MANAGER

#include <vector>
#include <GL/glew.h>

namespace glh
{

struct InterleavedBufferData
{
  std::vector<GLfloat> vertexs;
  std::vector<unsigned int> indexes;
  int stride;
};

class BufferManager
{
public:
  static GLuint create(InterleavedBufferData);
  static void bind(GLuint);
};

}

#endif
