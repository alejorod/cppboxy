#include <window.h>
#include <buffer_manager.h>
#include <shader_manager.h>

glh::Window::Window(std::string title, int x, int y, int w, int h, Uint32 flags)
{
  window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  context = SDL_GL_CreateContext(window);
  glewInit();
}

glh::Window::~Window()
{
  SDL_DestroyWindow(window);
}

void glh::Window::swap()
{
  SDL_GL_SwapWindow(window);
}

void glh::Window::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glh::Window::draw(GLuint shader_id, GLuint buffer_id)
{
  glh::ShaderManager::use(shader_id);
  glh::BufferManager::bind(buffer_id);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     NULL            // array buffer offset
  );
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}
