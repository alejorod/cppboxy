#include <glh.h>
#include <events.h>
#include <window.h>
#include <primitives.h>
#include <shader_manager.h>
#include <buffer_manager.h>
#include <drawer.h>
#include <voxel_chunk.h>

#include <iostream>
#include <PerlinNoise.h>

#include <algorithm>

std::vector<std::vector<int>> generate_world()
{
  PerlinNoise pn;
  int size = 300;
  int w_size = 200;
  std::vector<std::vector<int>> w;
  w.resize(w_size);

  for (int i = 0; i < w.size(); i++) {
    w[i].resize(w_size);
    for (int j = 0; j < w[i].size(); j++) {
      double x = (double) j / (double) (size);
      double y = (double) i / (double) (size);

      double n = std::abs(pn.noise(x, y, 0))
                + 0.5 * std::abs(pn.noise(2 * x, 2 * y, 0))
                + 0.25 * std::abs(pn.noise(4 * x, 2 * y, 0));

      w[i][j] = (int) floor(n * size / 2);

    }
  }
  return w;
}

int main()
{
  glh::GLH env;
  glh::Window window { "demo", 200, 200, 800, 600, glh::Window::SHOWN | glh::Window::OPENGL };
  glh::Drawer drawer { window };
  glh::Camera camera { 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f };
  glh::Event event;

  GLuint shader = glh::ShaderManager::load("vertex_shader.glsl", "fragment_shader.glsl");
  glh::VoxelChunk voxel_chunk;
  voxel_chunk.set_chunk_data(generate_world());
  glh::InterleavedBufferData buffer_data = voxel_chunk.get_buffer_data();
  GLuint vao = glh::BufferManager::create(buffer_data);
  glh::Drawable triangle = glh::Drawer::create_drawable(shader, vao, buffer_data.indexes.size());

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

    drawer.clear();
    drawer.draw(camera, triangle);
    drawer.swap();
  }

  return 0;
}
