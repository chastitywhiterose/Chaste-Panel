/*
sdl_graphics.h

this header file is meant to contain all the functions which write things to the screen
*/



/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{

 delay=1000/fps;

 loop=1;
 while(loop)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

 SDL_SetRenderDrawColor(renderer,0,0,0,255);
 SDL_RenderClear(renderer);

 text_x=main_font.char_height*1;

 sprintf(text,"Chaste \n Panel");
 chaste_font_draw_string_scaled(text,100,main_font.char_height*1*4,20);

 chaste_palette_index=chaste_palette_index1;
 chaste_font_draw_string_scaled_special(text,100,main_font.char_height*1*4,20);

 chaste_palette_index1++;
 if(chaste_palette_index1>=chaste_palette_length)
 {
  chaste_palette_index1=0;
 }


 sprintf(text,"Press Enter to Begin game.");
 chaste_font_draw_string_scaled(text,200,400,4);

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the C Programming Language.\nThe font handling is done with the font library Chastity wrote and named Chaste Font.\nSDL is used for the graphics API including rectangles and textures.\n\nThis game is based on Panel de Pon, also known as Tetris Attack.");
 chaste_font_draw_string(text,200,500);

 SDL_RenderPresent(renderer);


  SDL_PollEvent( &e );
  if( e.type == SDL_QUIT ){loop=0;}
  if(e.type == SDL_KEYUP)
  {
   if(e.key.keysym.sym==SDLK_RETURN){loop=0;}
  }

 /*delay*/
 while(sdl_time<sdl_time1)
 {
  sdl_time=SDL_GetTicks();
 }



 }

}






 int fps_current; /*only used when I am debugging the game*/

 void draw_stats_chaste_font_centered()
 {
  int scale=4;
 
  text_x=32;


 /*sprintf(text,"Chaste\n Panel");
 chaste_font_draw_string_scaled(text,text_x,main_font.char_height*1,8);*/

  chaste_palette_index=chaste_palette_index1;
  chaste_font_draw_string_scaled_special("Chaste\n Panel",text_x,main_font.char_height*1,8);

  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }

  sprintf(text,"Score %d",score);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*6*scale,scale);
  
   sprintf(text,"Combo %d",combo);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*7*scale,scale);

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
  hours=minutes/60;
  minutes%=60;
  
  sprintf(text,"Time %d:%02d:%02d",hours,minutes,seconds);
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

 SDL_SetRenderDrawColor(renderer,r,g,b,255);

/*set up the rectangle structure with the needed data to square the squares*/
   rect.x=grid_offset_x+x*block_size;
   rect.y=y*block_size;
   rect.w=block_size;
   rect.h=block_size;
   SDL_RenderFillRect(renderer,&rect);

   x+=1;
  }
  y+=1;
 }
 
 
  /*draw the boundary walls*/
SDL_SetRenderDrawColor(renderer,128,128,128,255);

/*
 set up the rectangle structure with the needed data to square the walls
*/
 rect.x=grid_offset_x-border_size;
 rect.y=0*block_size;
 rect.w=border_size;
 rect.h=height;

 SDL_RenderFillRect(renderer,&rect);

 rect.x=grid_offset_x+grid_width*block_size;
 SDL_RenderFillRect(renderer,&rect);
 /*end of drawing code for walls*/
 
 stats_func();

 SDL_RenderPresent(renderer);
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
 
 if(0)
 {
  main_grid.array[6+13*grid_width]=colors[0];
  main_grid.array[6+14*grid_width]=colors[0];
  main_grid.array[5+15*grid_width]=colors[0];
  main_grid.array[7+15*grid_width]=colors[0];
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

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);


  show_grid();






 /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
 
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
 

 SDL_RenderPresent(renderer);

 while(sdl_time<sdl_time1)
 {
  sdl_time=SDL_GetTicks();
 }

 frame++;

  if(!Mix_Playing(0)) /*if music is no longer playing*/
  {
   song_index=(song_index+1)%songs; /*go to next song*/
   chaste_audio_play(music[song_index]); /*start the music at the current song index*/
  }

 }

}



/*
https://wiki.libsdl.org/SDL2/SDL_RenderDrawRect
*/


