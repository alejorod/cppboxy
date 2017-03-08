#include <buffer_manager.h>

GLuint glh::BufferManager::create(InterleavedBufferData data)
{
  GLuint vao_id;
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  GLuint buffer_id;
  glGenBuffers(1, &buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.vertexs.size(), &data.vertexs.front(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
     0,
     3,
     GL_FLOAT,
     GL_FALSE,
     data.stride * sizeof(GLfloat),
     NULL
  );

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
     1,
     3,
     GL_FLOAT,
     GL_FALSE,
     data.stride * sizeof(GLfloat),
     (GLvoid*) (3 * sizeof(GLfloat))
  );

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
     2,
     3,
     GL_FLOAT,
     GL_FALSE,
     data.stride * sizeof(GLfloat),
     (GLvoid*) (6 * sizeof(GLfloat))
  );

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(
     3,
     1,
     GL_FLOAT,
     GL_FALSE,
     data.stride * sizeof(GLfloat),
     (GLvoid*) (9 * sizeof(GLfloat))
  );

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(
     4,
     1,
     GL_FLOAT,
     GL_FALSE,
     data.stride * sizeof(GLfloat),
     (GLvoid*) (9 * sizeof(GLfloat))
  );

  GLuint index_buffer;
  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indexes.size() * sizeof(unsigned int), &data.indexes.front(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glDeleteBuffers(1, &buffer_id);
  glDeleteBuffers(1, &index_buffer);

  return vao_id;
}

void glh::BufferManager::bind(GLuint buffer_id)
{
  glBindVertexArray(buffer_id);
}
