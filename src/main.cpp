#include <glh.h>
#include <window.h>
#include <events.h>
#include <buffer_manager.h>
#include <shader_manager.h>
#include <primitives.h>
#include <drawer.h>

int main()
{
  glh::GLH env;
  glh::Window window { "demo", 200, 200, 800, 600, glh::Window::SHOWN };
  glh::Drawer drawer { window };
  glh::Event event;

  GLuint traingle_vao = glh::BufferManager::create(glh::primitives::triangle);
  GLuint shader = glh::ShaderManager::load("vertex_shader.glsl", "fragment_shader.glsl");
  glh::Drawable triangle = glh::Drawer::create_drawable(shader, traingle_vao, 3);

  bool run = true;

  while(run)
  {
    while(glh::poll_event(&event))
    {
      if (event.type == glh::events::quit)
      {
        run = false;
      }
    }

    drawer.clear();
    drawer.draw(triangle);
    drawer.swap();
  }

  return 0;
}
