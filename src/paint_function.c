#include "main.h"

SDL_Surface *paint;

static inline drawline(int x0, int x1, int y0, int y1, Uint32 color)
{
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy)/2, e2;

  for(;;)
  {
    putpixel(paint, x0, y0, color);
    if (x0 == x1 && y0 == y1) break;
    e2 = err;
    if (e2 >- dx)
    {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy)
    {
      err += dx;
      y0 += sy;
    }
  }
  return 0;
}
void *rubber()
{
  SDL_Event event;
  int x1, x;
  int y1, y;
  int continuer = 1;
  int is_pressed = 0;

  while (continuer == 1)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          continuer = 0;
          break;
        case SDL_MOUSEBUTTONDOWN:
          switch (event.button.button)
          {
            case SDL_BUTTON_LEFT:
              is_pressed = 1;
              x1 = event.button.x;
              y1 = event.button.y;
            break;
          }
        case SDL_MOUSEMOTION:
          if (is_pressed == 1)
          {
            x = event.button.x;
            y = event.button.y;
            
            drawline(x1, x, y1, y, SDL_MapRGB(paint->format,0 ,255 , 0));
            SDL_Flip(paint);
            x1 = x;
            y1 = y;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          is_pressed = 0;
          break;
      }
    }
  }
  pthread_exit(NULL);

}

void *draw()
{
  SDL_Event event;
  int x1, x;
  int y1, y;
  int continuer = 1;
  int is_pressed = 0;

  while (continuer == 1)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          continuer = 0;
          break;
        case SDL_MOUSEBUTTONDOWN:
          switch (event.button.button)
          {
            case SDL_BUTTON_LEFT:
              is_pressed = 1;
              x1 = event.button.x;
              y1 = event.button.y;
            break;
          }
        case SDL_MOUSEMOTION:
          if (is_pressed == 1)
          {
            x = event.button.x;
            y = event.button.y;
            
            drawline(x1, x, y1, y, SDL_MapRGB(paint->format, 0, 0, 255));
            SDL_Flip(paint);
            x1 = x;
            y1 = y;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          is_pressed = 0;
          break;
      }
    }
  }
  pthread_exit(NULL);

}


