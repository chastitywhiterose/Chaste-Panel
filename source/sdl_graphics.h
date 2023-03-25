/*
sdl_graphics.h

this header file is meant to contain all the functions which write things to the screen
*/



/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{
 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));

 text_x=main_font.char_height*1;

 sprintf(text,"Chaste \n Panel");
 chaste_font_draw_string_scaled(text,100,main_font.char_height*1,20);


 sprintf(text,"Press Enter to Begin game.");
 chaste_font_draw_string_scaled(text,200,400,4);

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the C Programming Language.\nThe font handling is done with the font library Chastity wrote and named Chaste Font.\nSDL is used for the graphics API including rectangles and textures.\n\nThis game is based on Panel de Pon, also known as Tetris Attack.");
 chaste_font_draw_string(text,200,500);

 SDL_UpdateWindowSurface(window); /*update the screen*/

 loop=1;
 while(loop)
 {
  SDL_PollEvent( &e );
  if( e.type == SDL_QUIT ){loop=0;}
  if(e.type == SDL_KEYUP)
  {
   if(e.key.keysym.sym==SDLK_RETURN){loop=0;}
  }
 }

}






 int fps_current; /*only used when I am debugging the game*/

 void draw_stats_chaste_font_centered()
 {
  int scale=4;
 
  text_x=32;

sprintf(text,"Chaste\n Panel");
 chaste_font_draw_string_scaled(text,text_x,main_font.char_height*1,8);

  sprintf(text,"Score %d",score);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*6*scale,scale);

  time(&time1);
  
  seconds=time1-time0; /*subtract current time from start time to get seconds since game started*/
  
/*  
  sprintf(text,"Frame %d",frame);
  chaste_font_draw_string(text,text_x,main_font.char_height*15);
  
  if(seconds!=0)
  {
   fps_current=frame/seconds;
   sprintf(text,"FPS %d",fps_current);
   chaste_font_draw_string(text,text_x,main_font.char_height*16);
  }
*/
  
  minutes=seconds/60;
  seconds%=60;
  
  sprintf(text,"Time %d:%02d",minutes,seconds);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*13*scale,scale);
  





 }
 
 /*a function pointer that points to whichever function I currently use to draw the game stats to the screen*/
void (*stats_func)()=draw_stats_chaste_font_centered;
 
 
/*more global variables to be defined before game loop function*/
int block_size;
int border_size;
int grid_offset_x;


int wall_color=0x808080;

/*display the tetris grid*/
void show_grid()
{
 int x,y;
 int pixel,r,g,b;

 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   pixel=main_grid.array[x+y*grid_width];
   r=(pixel&0xFF0000)>>16;
   g=(pixel&0x00FF00)>>8;
   b=(pixel&0x0000FF);

/*
 printf("x=%d y=%d ",x,y);
 printf("red=%d green=%d blue=%d\n",r,g,b);
*/

rect_color=SDL_MapRGB(surface->format,r,g,b);

/*set up the rectangle structure with the needed data to square the squares*/
   rect.x=grid_offset_x+x*block_size;
   rect.y=y*block_size;
   rect.w=block_size;
   rect.h=block_size;
   SDL_FillRect(surface,&rect,rect_color);

   x+=1;
  }
  y+=1;
 }
 
 
  /*draw the boundary walls*/

/*
 set up the rectangle structure with the needed data to square the walls
*/
 rect.x=grid_offset_x-border_size;
 rect.y=0*block_size;
 rect.w=border_size;
 rect.h=height;

 SDL_FillRect(surface,&rect,wall_color);

 rect.x=grid_offset_x+grid_width*block_size;
 SDL_FillRect(surface,&rect,wall_color);
 /*end of drawing code for walls*/
 
 stats_func();

 SDL_UpdateWindowSurface(window);
}

/*
this is a function which is called by main after window is created. It is the game loop.
*/
void sdl_chaste_panel()
{

 int x=0,y=0,i;
 




 block_size=height/grid_height;
 grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/

 /*printf("block_size==%d\n",block_size);*/
 
 /*setup the grid offset and border*/

 grid_offset_x=(width-(20/2*block_size))/2; /*to center of screen*/
 border_size=12;

 /*spawn_block();*/
 
 player_init();
 
 
 player.rect.x=4*player.size;
 player.rect.y=4*player.size;


 /*first empty the grid*/
 grid_clear();
 
 /*attempt to setup initial blocks*/

 color_index=0;
 
 y=10;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   main_grid.array[x+y*grid_width]=colors[color_index];
   color_index=(color_index+1)%6;
   x++;
  }
  y++;
 }

 delay=1000/fps;
 
 /*get time before the game starts using standard library time function*/
 time(&time0);
 
 loop=1;
  /* Loop until the user closes the window */
 while(loop)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));


 show_grid();







 keyboard();
 
 SDL_SetRenderDrawColor(renderer,255,255,255,255);

/*first draw of player selection*/
 rect.x=grid_offset_x+player.x*block_size;
 rect.y=player.y*block_size;
 rect.w=block_size;
 rect.h=block_size;

/*second drawing with smaller squares for visibility*/
 i=4;
 SDL_RenderDrawRect(renderer,&rect);
 rect.x+=block_size;
 SDL_RenderDrawRect(renderer,&rect);

 rect.x=grid_offset_x+player.x*block_size;
 rect.y=player.y*block_size;
 rect.w=block_size;
 rect.h=block_size;
 
 rect.x+=i;
 rect.y+=i;
 rect.w-=i*2;
 rect.h-=i*2;

 SDL_SetRenderDrawColor(renderer,0,0,0,255);
 SDL_RenderDrawRect(renderer,&rect);
 rect.x+=block_size;
 SDL_RenderDrawRect(renderer,&rect);
 

 SDL_UpdateWindowSurface(window); /*update the screen*/


 while(sdl_time<sdl_time1)
 {
  sdl_time=SDL_GetTicks();
 }

 frame++;

 }

}



/*
https://wiki.libsdl.org/SDL2/SDL_RenderDrawRect
*/


