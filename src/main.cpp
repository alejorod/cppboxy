#include <glh.h>
#include <events.h>
#include <window.h>
#include <primitives.h>
#include <shader_manager.h>
#include <buffer_manager.h>
#include <drawer.h>
#include <voxel_chunk.h>
#include <world.h>

#include <iostream>
#include <PerlinNoise.h>

#include <algorithm>


int main()
{
  glh::GLH env;
  glh::Window window { "demo", 200, 200, 800, 600, glh::Window::SHOWN | glh::Window::OPENGL };
  glh::Drawer drawer { window };
  glh::Camera camera { 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f };
  glh::Event event;
  glh::World world { 8, 16, 100 * 10, 300 };

  GLuint shader = glh::ShaderManager::load("vertex_shader.glsl", "fragment_shader.glsl");

  glh::Drawer::set_default_shader(shader);

  bool run = true;
  float count = 1.0f;

  while(run)
  {
    while(glh::poll_event(&event))
    {
      if (event.type == glh::events::quit)
      {
        run = false;
      }
    }

    camera.update();
    world.update(camera);
    drawer.clear();

    for(auto b: world.get_drawables(camera))
    {
      drawer.draw(camera, b);
    }

    drawer.swap();
  }

  return 0;
}
