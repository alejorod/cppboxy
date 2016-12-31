#include <buffer_manager.h>

GLuint glh::BufferManager::create(GLfloat* data)
{
  GLuint vao_id;
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  GLuint buffer_id;
  glGenBuffers(1, &buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 3, data, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     NULL                // array buffer offset
  );

  glBindVertexArray(0);

  return vao_id;
}

void glh::BufferManager::bind(GLuint buffer_id)
{
  glBindVertexArray(buffer_id);
}
