#include <keyboard.h>

bool glh::keyboard::is_pressed(glh::Key key_code)
{
  return (bool) SDL_GetKeyboardState(NULL)[SDL_GetScancodeFromKey(key_code)];
}
