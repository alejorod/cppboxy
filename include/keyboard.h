#ifndef GLH_KEYBOARD
#define GLH_KEYBOARD

#include <SDL.h>

namespace glh
{
typedef SDL_Keycode Key;

namespace keyboard
{
  const glh::Key LEFT = SDLK_LEFT;
  const glh::Key RIGHT = SDLK_RIGHT;
  const glh::Key UP = SDLK_UP;
  const glh::Key DOWN = SDLK_DOWN;
  const glh::Key W = SDLK_w;
  const glh::Key A = SDLK_a;
  const glh::Key S = SDLK_s;
  const glh::Key D = SDLK_d;

  bool is_pressed(glh::Key);
}

}

#endif
