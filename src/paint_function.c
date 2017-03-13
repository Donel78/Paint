#include "main.h"

SDL_Surface *paint;
SDL_Surface *img;

static inline void drawline(int x0, int x1, int y0, int y1, Uint32 color)
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
}
void *rubber()
{
  SDL_Event event;
  int x1 = 0;
  int x = 0;
  int y1 = 0;
  int y = 0;
  int continuer = 1;
  int is_pressed = 0;

  while (continuer == 1)
  {
    while (SDL_WaitEvent(&event))
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
            
            drawline(x1, x, y1, y, SDL_MapRGB(paint->format,255 ,255 , 255));
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
  int x1 = 0;
  int x = 0;
  int y1 = 0;
  int y = 0;
  int continuer = 1;
  int is_pressed = 0;
  while (continuer == 1)
  {
    while (SDL_WaitEvent(&event))
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
            
            drawline(x1, x, y1, y, SDL_MapRGB(paint->format, color->red * 255, color->green * 255,color->blue * 255));
            printf("%f\n",color->red);
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
void *text()
{
  SDL_Surface *text = NULL;
  SDL_Surface *buffer = NULL;
  TTF_Font *police = NULL;
  SDL_Rect positionText;
  SDL_Rect positionBuffer;
  positionBuffer.x = 0;
  positionBuffer.y = 0;
  positionText.x = 50;
  positionText.y = 50;
  SDL_Color black = {color->red * 255, color->green * 255, color->blue * 255,42};
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  police = TTF_OpenFont("LongTime.ttf",25);

  SDL_SaveBMP(paint,"tmpimage/painttmp.bmp");
  buffer = SDL_LoadBMP("tmpimage/painttmp.bmp");
  char mot[500];
//  int is_pressed = 0;

  SDL_Event event;
  size_t pos = 0;
  int continuer = 1;
  SDL_EnableUNICODE(1);
  while (continuer == 1)
  {
    while (SDL_WaitEvent(&event))
    {
      switch (event.type)
      {
        case SDL_MOUSEBUTTONDOWN:
          switch (event.button.button)
          {
            case SDL_BUTTON_LEFT:
  //            is_pressed = 1;
              positionText.x = event.button.x;
              positionText.y = event.button.y;
            break;
          }
          break;
 
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
            case SDLK_RETURN:
              mot[pos] = '\n';
              break;

            case SDLK_ESCAPE:
              continuer = 0;
              break;

            default:
              printf("Touche %d enfoncée : %c\n",event.key.keysym.sym,event.key.keysym.unicode); 
              mot[pos] = event.key.keysym.unicode;
              printf("%c\n",mot[pos]);
              pos++;
              text = TTF_RenderText_Blended(police, mot, black);
              printf("coord (%d,%d)\n", positionText.x, positionText.y);
              SDL_BlitSurface(buffer,NULL,paint,&positionBuffer);
              SDL_BlitSurface(text,NULL,paint, &positionText);
              SDL_Flip(paint);

              break;
          }   
      }
    }
  }


  SDL_EnableUNICODE(0);
  pthread_exit(NULL);
  return 0;
}

void *load(char *image_path)
{
  img = IMG_Load(image_path);
  if (!img)
    errx(3,"can't load %s: %s","image",IMG_GetError());
  paint = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);

  if (paint == NULL)
  {
    errx(1,"Couldnt set %dx%d video modde : %s\n",
    img->w, img->h, SDL_GetError());
  }
  if (SDL_BlitSurface(img, NULL, paint, NULL) < 0)
    warnx("BlitSurface error: %s\n",SDL_GetError());
  SDL_UpdateRect(paint ,0 ,0 ,img->w, img->h );
  return 0;
}

void *save(char *save_path)
{
  int r = SDL_SaveBMP(paint,save_path);
  if (r != 0)
    puts("err");
  return 0;
}
