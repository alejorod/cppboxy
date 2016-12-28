#include <glh.h>
#include <window.h>
#include <events.h>
#include <buffer_manager.h>
#include <shader_manager.h>

int main()
{
  glh::GLH env = glh::GLH();
  glh::Window window = glh::Window("demo", 200, 200, 200, 200, glh::Window::SHOWN);
  glh::Event event;

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  GLfloat g_vertex_buffer_data[] = {
     -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
  };

  GLuint buffer_id = glh::BufferManager::create(g_vertex_buffer_data);
  GLuint shader_id = glh::ShaderManager::load("vertex_shader.glsl", "fragment_shader.glsl");

  glh::ShaderManager::use(shader_id);
  glh::BufferManager::bind(buffer_id);

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

    window.clear();
    window.draw(shader_id, buffer_id);
    window.swap();
  }

  return 0;
}
