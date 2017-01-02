#include <drawer.h>
#include <buffer_manager.h>
#include <shader_manager.h>

#include <iostream>

glh::Drawer::Drawer(glh::Window &win)
: window(win)
{
  context = window.create_context();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glewInit();
}

glh::Drawer::~Drawer()
{
  SDL_GL_DeleteContext(context);
}

void glh::Drawer::clear()
{
  window.clear();
}

void glh::Drawer::swap()
{
  window.swap();
}

void glh::Drawer::draw(glh::Camera &camera, glh::Drawable drawable)
{
  glm::mat4 projection_matrix = camera.get_projection_matrix();
  glm::mat4 view_matrix = camera.get_view_matrix();
  glm::mat4 model_matrix = drawable.get_model_matrix();
  glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

  glh::ShaderManager::use(drawable.shader);
  glh::BufferManager::bind(drawable.vao);
  GLuint mvp_location = glGetUniformLocation(drawable.shader, "MVP");
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, drawable.count);
}
