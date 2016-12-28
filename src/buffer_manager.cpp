#include <buffer_manager.h>

GLuint glh::BufferManager::create(GLfloat* data)
{
  GLuint buffer_id;
  glGenBuffers(1, &buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 3, data, GL_STATIC_DRAW);

  return buffer_id;
}

void glh::BufferManager::bind(GLuint buffer_id)
{
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}
