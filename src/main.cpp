#include <glh.h>
#include <events.h>
#include <window.h>
#include <primitives.h>
#include <shader_manager.h>
#include <buffer_manager.h>
#include <drawer.h>

int main()
{
  glh::GLH env;
  glh::Window window { "demo", 200, 200, 800, 600, glh::Window::SHOWN };
  glh::Drawer drawer { window };
  glh::Camera camera { 45.0f, 800.0f / 600.0f, 0.1f, 100.0f };
  glh::Event event;

  camera.translate(0.0, 0.0, 4.0);

  GLuint shader = glh::ShaderManager::load("vertex_shader.glsl", "fragment_shader.glsl");
  GLuint traingle_vao = glh::BufferManager::create(glh::primitives::cube);
  glh::Drawable triangle = glh::Drawer::create_drawable(shader, traingle_vao, 6 * 2 * 3);

  bool run = true;
  float count = 0.0f;

  while(run)
  {
    count += 0.001f;
    while(glh::poll_event(&event))
    {
      if (event.type == glh::events::quit)
      {
        run = false;
      }
    }

    triangle.rotate_y(count * 30);
    camera.translate(0.0f, 0.0f, count);

    drawer.clear();
    drawer.draw(camera, triangle);
    drawer.swap();
  }

  return 0;
}
