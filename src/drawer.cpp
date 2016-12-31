#include <drawer.h>
#include <buffer_manager.h>
#include <shader_manager.h>

glh::Drawer::Drawer(glh::Window &win)
: window(win)
{
  context = window.create_context();
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

void glh::Drawer::draw(glh::Drawable drawable)
{
  glh::ShaderManager::use(drawable.shader);
  glh::BufferManager::bind(drawable.vao);
  glDrawArrays(GL_TRIANGLES, 0, drawable.count);
}
