#include "main.h"

SDL_Surface *paint;
SDL_Surface *img;
SDL_Surface *tabsdl[1000];
int nosdl;

void _filling(int x, int y, Uint32 mypix, Uint32 couleur)
{
  struct Stack **s_x = calloc(1000, sizeof(int));
  struct Stack **s_y = calloc(1000, sizeof(int));
  int p = 1;
  int xt = 0;
  int yt = 0;
  if (mypix == couleur)
  {
    return;
  }
  stack_push(s_x,x);
  stack_push(s_y,y);
  while(p != 0)
  {
    xt = stack_pop(s_x);
    yt = stack_pop(s_y);
    p--;
    putpixel(paint, xt, yt, couleur);
    if (xt + 1 < paint->w)
    {
      if (getpixel(paint, xt + 1, yt) == mypix)
      {
        stack_push(s_x,xt + 1);
        stack_push(s_y,yt);
        p++;
      }
    }
    if (xt - 1 >= 0)
    {
      if (getpixel(paint, xt - 1, yt) == mypix)
      {
        stack_push(s_x, xt - 1);
        stack_push(s_y, yt);
        p++;
      }
    }
    if (yt + 1 < paint->h)
    {
      if (getpixel(paint, xt, yt + 1) == mypix)
      {
        stack_push(s_x,xt);
        stack_push(s_y, yt + 1);
        p++;
      }
    }
    if (yt - 1 >= 0)
    {
      if (getpixel(paint, xt, yt - 1) == mypix)
      {
        stack_push(s_x, xt);
        stack_push(s_y, yt - 1);
        p++;
      }
    }
  }
  stack_clear(s_x);
  stack_clear(s_y);

}
void *filling()
{
  SDL_Event event;
  int x = 0;
  int y = 0;
  Uint32 mypix;
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
              x = event.button.x;
              y = event.button.y;
            break;
          }
        case SDL_MOUSEMOTION:
          if (is_pressed == 1)
          {
              mypix = getpixel(paint,x,y);
            _filling(x, y,mypix, SDL_MapRGB(paint->format, color->red, color->green ,color->blue));
            SDL_Flip(paint);
          }
          break;
        case SDL_MOUSEBUTTONUP:
          is_pressed = 0;
          SDL_SaveBMP(paint,"tmpimage/back.bmp");
          tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
          nosdl++;

          break;
      }
    }
  }
  pthread_exit(NULL);
}

void *getcolor()
{
  SDL_Event event;
  int x = 0;
  int y = 0;
  Uint32 getcolor;
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
              x = event.button.x;
              y = event.button.y;
            break;
          }
        case SDL_MOUSEMOTION:
          if (is_pressed == 1)
          {
              getcolor = getpixel(paint,x,y);
              color->red = ((getcolor / (256*256))%256);
              color->green = ((getcolor / 256) % 256);
              color->blue = (getcolor % 256);
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

static inline void drawline(int x0, int x1, int y0, int y1, Uint32 color)
{
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy)/2, e2;

  for(;;)
  {
    for (int i = 0; i <= taille; i++)
    {
        if (x0 + i < paint->w)
          {
            putpixel(paint, x0 + i, y0 , color);
           putpixel(paint, x0 + i , y0  , color);
          }
        if (y0 + i < paint->h)
        {
           putpixel(paint, x0 , y0 + i , color);
           putpixel(paint, x0 , y0 + i , color);
        }
    }
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
          SDL_SaveBMP(paint,"tmpimage/back.bmp");
          tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
          nosdl++;

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
            drawline(x1, x, y1, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
            SDL_Flip(paint);
            x1 = x;
            y1 = y;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          is_pressed = 0;
          SDL_SaveBMP(paint,"tmpimage/back.bmp");
          tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
          nosdl++;
          break;
      }
    }
  }
  pthread_exit(NULL);

}

void *mySelect()
{
  SDL_Event event;
  int x1 = 0;
  int x = 0;
  int y1 = 0;
  int y = 0;
  int continuer = 1;
  int is_pressed = 0;
  int rec_move = 0;
  //int is_moving = 0;
  SDL_Surface *rec = NULL;
  SDL_Rect rec_saved;
  SDL_Rect rec_new;
  SDL_SaveBMP(paint,"tmpimage/painttmp.bmp");
  rec = SDL_LoadBMP("tmpimage/painttmp.bmp");
  SDL_Rect positionRec;
  positionRec.x = 0;
  positionRec.y = 0;

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
              //printf("%d,%d\n",x,rec_new.x);
              
            if (rec_move == 0)
            {
              SDL_BlitSurface(rec, NULL, paint, &positionRec);
              drawline(x1, x1, y1, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
              drawline(x1, x, y1, y1, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
              drawline(x1, x, y, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
              drawline(x, x, y1, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));

              SDL_Flip(paint);
            }
            else if (rec_move == 1  /*&& ((x >= rec_new.x) || (is_moving == 1)) && y > rec_new.y && x < rec_new.w && y < rec_new.h*/)
            {
              //is_moving = 1;
              SDL_BlitSurface(rec, NULL, paint, &positionRec);
              SDL_FillRect(paint, &rec_saved, SDL_MapRGB(paint->format, 255, 255, 255));
              rec_new.x = x;
              rec_new.y = y;
              SDL_BlitSurface(rec, &rec_saved, paint, &rec_new);
              SDL_Flip(paint);
            }
    
          }
         
          break;
        case SDL_MOUSEBUTTONUP:
          is_pressed = 0;
          if (rec_move == 0)
          {
            rec_saved.x = x1;
            rec_saved.y = y1;
            rec_saved.w = x - x1 + 1;
            rec_saved.h = y - y1 + 1;
            rec_new.x = x1 - 1;
            rec_new.y = y1 - 1;
            rec_new.w = x - x1 ;
            rec_new.h = y - y1 ;
            SDL_SaveBMP(paint,"tmpimage/painttmp.bmp");
            rec = SDL_LoadBMP("tmpimage/painttmp.bmp");
            SDL_SaveBMP(paint,"tmpimage/back.bmp");
            SDL_BlitSurface(paint, NULL, NULL, &rec_saved);
            rec_move = 1;
          }
          else if (rec_move == 1)
          {
            tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
            nosdl++;
            //  is_moving = 0;
              rec_move = 0;
              rec_saved.x++;
              rec_saved.y++;
              rec_saved.w--;
              rec_saved.h--;
              SDL_FillRect(paint, &rec_saved, SDL_MapRGB(paint->format, 255, 255, 255));
              SDL_BlitSurface(rec, &rec_saved, paint, &rec_new);
              SDL_Flip(paint);

          }
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
  SDL_Color black = {color->red, color->green, color->blue,42};
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  police = TTF_OpenFont("LongTime.ttf",25);

  SDL_SaveBMP(paint,"tmpimage/painttmp.bmp");
  buffer = SDL_LoadBMP("tmpimage/painttmp.bmp");
  char mot[500];

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
              SDL_SaveBMP(paint,"tmpimage/back.bmp");
              tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
              nosdl++;
              break;

            default:
              mot[pos] = event.key.keysym.unicode;
              pos++;
              text = TTF_RenderText_Blended(police, mot, black);
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

void no_filter()
{
 SDL_Surface *paint2 = NULL;
 paint2 = SDL_LoadBMP("tmpimage/painttmp.bmp");
 SDL_BlitSurface(paint2, NULL, paint, NULL);
 SDL_Flip(paint);
}

void white_black()
{

  SDL_SaveBMP(paint,"tmpimage/painttmp.bmp");
  Uint32 myPix = 0;
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  for (int i = 0; i < paint->w; i++)
  {
    for (int j = 0; j < paint->h; j++)
    {
      myPix = getpixel(paint, i, j);
      SDL_GetRGB(myPix, paint->format, &r, &g, &b);
      putpixel(paint, i, j, SDL_MapRGB(paint->format, (r + g + b) / 3, (r + g + b) / 3, (r + g + b) / 3));
    }
  }

      SDL_Flip(paint);
}
void *droite()
{
  SDL_Event event;
  int x1 = 0;
  int x = 0;
  int y1 = 0;
  int y = 0;
  int continuer = 0;
  int is_pressed = 0;
  SDL_Surface *rec = NULL;
  SDL_SaveBMP(paint,"tmpimage/painttmp.bmp");
  rec = SDL_LoadBMP("tmpimage/painttmp.bmp");
  SDL_Rect positionRec;
  positionRec.x = 0;
  positionRec.y = 0;

  while (continuer == 0)
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
            SDL_BlitSurface(rec, NULL, paint, &positionRec);
            x = event.button.x;
            y = event.button.y;
            drawline(x1 ,x ,y1, y ,SDL_MapRGB(paint->format, color->red, color->green, color->blue));
            SDL_Flip(paint);
          }
          break;
       case SDL_MOUSEBUTTONUP:
          is_pressed = 0;
          SDL_SaveBMP(paint, "tmpimage/back.bmp");
          SDL_SaveBMP(paint, "tmpimage/painttmp.bmp");
          rec = SDL_LoadBMP("tmpimage/painttmp.bmp");
          SDL_BlitSurface(rec, NULL, paint, &positionRec);
          tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
          nosdl++;
          break;
      }
    }
  }
  pthread_exit(NULL);
}


void *swag()
{
  SDL_Event event;
  int x1 = 0;
  int x = 0;
  int y1 = 0;
  int y = 0;
  int continuer = 0;
  int is_pressed = 0;
  while (continuer == 0)
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
            drawline(x1 ,x1 ,y1, y ,SDL_MapRGB(paint->format, color->red, color->green, color->blue));
            drawline(x ,x1 ,y1 ,y ,SDL_MapRGB(paint->format, color->red, color->green, color->blue));
            SDL_Flip(paint);
          }
          break;
       case SDL_MOUSEBUTTONUP:
          is_pressed = 0;
          SDL_SaveBMP(paint, "tmpimage/back.bmp");
          tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
          nosdl++;
          break;
      }
    }
  }
  pthread_exit(NULL);
}




/**************************** GAEL ET TIMOti ****************************/





static inline void _line(int x1, int x2, int y1, int y2, Uint32 color) {
  int x,y;		
  int Dx,Dy;
  int xincr,yincr;
  int erreur;
  int i;
  
  Dx = abs(x2-x1);
  Dy = abs(y2-y1);
  if(x1<x2)
    xincr = 1;
  else
    xincr = -1;
  if(y1<y2)
    yincr = 1;
  else			
    yincr = -1;
  
  x = x1;
  y = y1;
  if(Dx>Dy)
    {
      erreur = Dx/2;
      for(i=0;i<Dx;i++)
	{
	  x += xincr;
	  erreur += Dy;
	  if(erreur>Dx)
	    {
	      erreur -= Dx;
	      y += yincr;
	    }
	  putpixel(paint,x, y,color);
	}
    }
  else
    {
      erreur = Dy/2;
      for(i=0;i<Dy;i++)
	{
	  y += yincr;
	  erreur += Dx;
	  
	  if(erreur>Dy)
	    {
	      erreur -= Dy;
	      x += xincr;
	    }
	  putpixel(paint,x, y,color);
	}
    }
}
static inline void _circle(int x1, int y1, int radius, Uint32 color) {
  int d,x,y,x2m1,max;
  y=radius;
  d= -radius;
  x2m1= -1;
  max = (int)(radius/sqrt(2.0));
  for(x=0;x<=max;x++)
    {  
      x2m1 += 2;
      d+= x2m1;
      if (d>=0) 
        {
	  y--;
	  d -= (y<<1);
        }
      putpixel(paint,x1+x,y1+y,color);
      putpixel(paint,x1-x,y1+y,color);
      putpixel(paint,x1+x,y1-y,color);
      putpixel(paint,x1-x,y1-y,color);
      putpixel(paint,x1+y,y1+x,color);
      putpixel(paint,x1-y,y1+x,color);
      putpixel(paint,x1+y,y1-x,color);
      putpixel(paint,x1-y,y1-x,color);
    }
}

void *line() {
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
	    //x1 = x;
	    //y1 = y;
          }
          break;
        case SDL_MOUSEBUTTONUP:
	  _line(x1, x, y1, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	   SDL_Flip(paint);
	   is_pressed = 0;
	   SDL_SaveBMP(paint,"tmpimage/back.bmp");
	   tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
	   nosdl++;
	   break;
      }
    }
  }
  pthread_exit(NULL);
}

void *rect() {
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
	      //x1 = x;
	      //y1 = y;
	      
	    }
          break;
	case SDL_MOUSEBUTTONUP:
	  _line(x1, x1, y1, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	  _line(x1, x, y1, y1, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	  _line(x, x, y1, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	  _line(x1, x, y, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	  SDL_Flip(paint);
	  is_pressed = 0;
	  SDL_SaveBMP(paint,"tmpimage/back.bmp");
	  tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
	  nosdl++;
	  break;
	}
    }
  }
  pthread_exit(NULL);
}


void *circle() {
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
	      //x1 = x;
	      //y1 = y;
	      
	    }
          break;
	case SDL_MOUSEBUTTONUP:
	  
	  _circle(x1, y1, abs(x1-x)+y-y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	  SDL_Flip(paint);
	  is_pressed = 0;
	  SDL_SaveBMP(paint,"tmpimage/back.bmp");
	  tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
	  nosdl++;
	  break;
	}
    }
  }
  pthread_exit(NULL);
}
void *croix() {
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
	    //x1 = x;
	    //y1 = y;
          }
          break;
        case SDL_MOUSEBUTTONUP:
	  _line(x1, x, y, y1, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	  _line(x1, x, y1, y, SDL_MapRGB(paint->format, color->red, color->green,color->blue));
	   SDL_Flip(paint);
	   is_pressed = 0;
	   SDL_SaveBMP(paint,"tmpimage/back.bmp");
	   tabsdl[nosdl] = IMG_Load("tmpimage/back.bmp");
	   nosdl++;
	   break;
      }
    }
  }
  pthread_exit(NULL);
}
void setPixel(int x, int y, Uint32 coul)
{ 
  *((Uint32*)(paint->pixels) + x + y * paint->w) = coul;                                               
}

void setPixelVerif(int x, int y, Uint32 coul)
{                                                                                                            
  if (x >= 0 && x < paint->w &&                                                                             
      y >= 0 && y < paint->h)                                                                             
    setPixel(x, y, coul);                                                                                   
}                                                                                                          

void ligneHorizontale(int x, int y, int w, Uint32 coul)
{                                                                                     
  SDL_Rect r;                                                                                               
  r.x = x;                                                                                                  
  r.y = y;                                                                                                  
  r.w = w;                                                                                                  
  r.h = 1;                                                                                                  
  SDL_FillRect(paint, &r, coul);                                                                            
}                                                                                                          

void ligneVerticale(int x, int y, int h, Uint32 coul)                                                        
{                                                                                                         
  SDL_Rect r;                                                                                               
  r.x = x;                                                                                                  
  r.y = y;                                                                                                  
  r.w = 1;                                                                                                  
  r.h = h;                                                                                                  
  SDL_FillRect(paint, &r, coul);                                                                            
}                                                                                                    

void _rectangle(int x, int y, int w, int h, Uint32 coul)                                                    
{                                                                                                          
  ligneHorizontale(x, y, w, coul);                                                                          
	ligneHorizontale(x, y + h - 1, w, coul);                                                                  
	ligneVerticale(x, y + 1, h - 2, coul);                                                                    
	ligneVerticale(x + w - 1, y + 1, h - 2, coul);                                                            
}                              

void echangerEntiers(int* x, int* y)                                                                        
{                                                                                                         
  int t = *x;                                                                                            
  *x = *y;                                                                                                 
  *y = t;                                                                                                   
}                                                                                                             
void ligne(int x1, int y1, int x2, int y2, Uint32 coul)                                                   
{                                                                                                          
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;                                                          
  if (abs(x2 - x1) < abs(y2 - y1)) {                                                                        
    /* parcours par l'axe vertical */                                                                     
    if (y1 > y2) {                                                                                        
      echangerEntiers(&x1, &x2);                                                                        
      echangerEntiers(&y1, &y2);                                                                        
    }                                                                                                     

    xincr = x2 > x1 ? 1 : -1;                                                                             
    dy = y2 - y1;                                                                                         
    dx = abs(x2 - x1);                                                                                    
    d = 2 * dx - dy;                                                                                      
    aincr = 2 * (dx - dy);                                                                                
    bincr = 2 * dx;                                                                                       
    x = x1;                                                                                               
    y = y1;                                                                                               

    setPixelVerif(x, y, coul);                                                                            

    for (y = y1+1; y <= y2; ++y) {                                                                        
      if (d >= 0) {                                                                                     
        x += xincr;                                                                                   
        d += aincr;                                                                                   
      } else                                                                                               
        d += bincr;                                                                                   
      setPixelVerif(x, y, coul);                                                                           
    }                                                                                                     

  } else {            
    /* parcours par l'axe horizontal */                                                                   
    if (x1 > x2) {                                                                                        
      echangerEntiers(&x1, &x2);                                                                      
      echangerEntiers(&y1, &y2);                                                                        
    }                                                                                                     

    yincr = y2 > y1 ? 1 : -1;                                                                          
    dx = x2 - x1;                                                                                         
    dy = abs(y2 - y1);                                                                                    
    d = 2 * dy - dx;                                                                                      
   aincr = 2 * (dy - dx);                                                                                    
    bincr = 2 * dy;                                                                                       
    x = x1;                                                                                               
    y = y1;                                                                                               

    setPixelVerif(x, y, coul);                                                                            

    for (x = x1+1; x <= x2; ++x) {                                                                        
     if (d >= 0) {                                                                                           
       y += yincr;                                                                                   
        d += aincr;                                                                                   
      } else                                                                                         
        d += bincr;                                                                                          
      setPixelVerif(x, y, coul);                                                                        
    }                                                                                                    
  }                                                                                                          
}                   



void _triangle(int x, int y, int w, int h, Uint32 coul)                                                      
{                                                                                                          
	ligneHorizontale(x, y, w, coul);                                                                      
	ligneVerticale(x, y + 1, h - 2, coul);                                                               
	ligne(x,y+h-1,x+w-1,y+1,coul);                                                                        
}            

void *triangle()                                                                                             
{                                                                                                            
	SDL_Event event;                                                                                          
	int x = 0;                                                                                                
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
							x = event.button.x;                                                               
							y = event.button.y;                                                               
							break;                                                                            
					}                                                                                         
				case SDL_MOUSEMOTION:                                                                         
					if (is_pressed == 1)                                                                      
					{                                                                                         
						x = event.button.x;                                                                   
						y = event.button.y;                                                                   
						_triangle(x,y,50,50, SDL_MapRGB(paint->format, color->red * 255, color->green * 255,color->blue * 255));                                            SDL_Flip(paint);
					}                                                                                         
					break;                                                                                    
				case SDL_MOUSEBUTTONUP:                                                                       
					is_pressed = 0;   



			}                                                                                                 
		}                                                                                                     
	}                                                                                                         
	pthread_exit(NULL);                                                                                       
}                








