#include <events.h>

int glh::poll_event(Event* event)
{
  return SDL_PollEvent(event);
}
