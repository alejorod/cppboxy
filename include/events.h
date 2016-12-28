#ifndef GLH_EVENTS
#define GLH_EVENTS

#include <SDL.h>

namespace glh
{

namespace events
{
  const Uint32 quit = SDL_QUIT;
}

typedef SDL_Event Event;

int poll_event(Event*);

}

#endif
