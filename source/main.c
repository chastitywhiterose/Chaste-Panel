#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>

/*
most variables in the program are global. Unless I create temporary variables in other functions.
*/
int width=1280,height=720;
int loop=1;
SDL_Window *window = NULL;
SDL_Surface *surface;
SDL_Renderer *renderer; /*renderer used for some things*/
SDL_Event e;
SDL_Rect rect;

int rect_color;


int frame=0,lastframe=0,fps=60,delay,framelimit=1; /*only used for animation demos*/
time_t time0,time1;
int seconds,minutes; /*to keep track of time*/
int sdl_time,sdl_time1;

char gamename[256];
int blocks_used=7;

char text[0x200];
char movetext[256],move_id;
int text_x; /*the x position of where text will go*/

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/

/*declare show_grid here so it is visible to chaste_panel.h*/
void show_grid();

/*music variables section*/
int songs=3,song_index=0,music_is_on=0;
char *music_files[]=
{
 "music/Tetris_Attack_Sound_of_the_Dogfish_OC_ReMix.mp3",
 "music/Final_Fantasy_7_Cosmo_OC_ReMix.mp3",
 "music/Legend_of_Zelda_A_Link_to_the_Past_The_Darkness_and_the_Light_OC_ReMix.mp3"
};

Mix_Chunk *music[3]; /*chunks the music is loaded into*/

#include "sdl_chaste_music.h"
#include "chaste_panel.h"
#include "sdl_chastefont.h"
#include "sdl_input.h"
#include "sdl_graphics.h"

int main(int argc, char **argv)
{
 int i=0;

 chaste_audio_init(); /*get the audio device ready*/
 
 /*load all songs*/
 i=0;
 while(i<songs)
 {
  music[i]=chaste_audio_load(music_files[i]);
  i++;
 }

 if(SDL_Init(SDL_INIT_VIDEO)){printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;}
 window=SDL_CreateWindow( "SDL Chaste Panel",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 /*set up the screen*/
 surface = SDL_GetWindowSurface( window );
 
  /*create a renderer that can draw to the surface*/
 renderer=SDL_CreateSoftwareRenderer(surface);
 if(renderer==NULL){printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0x80,0x80,0x80));
 SDL_UpdateWindowSurface(window);

 
 font_8=chaste_font_load("./font/FreeBASIC Font 8.bmp");

 main_font=font_8;


 welcome_screen_chaste_font();
 
 song_index=0;
 chaste_audio_play(music[song_index]);

 sdl_chaste_panel();
  
 if(fp!=NULL){fclose(fp);}
 if(fp_input!=NULL){fclose(fp_input);}

 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 
  /*unload and free the music*/
 i=0;
 while(i<songs)
 {
  if(music[i]!=NULL)
  {
   Mix_FreeChunk(music[i]);
   music[i]=NULL;
  }
  i++;
 }
 
  if (audio_open)
  {
   Mix_CloseAudio();
   audio_open = 0;
  }
  /*end of music closing section*/
 
 SDL_Quit();

 SDL_FreeSurface(font_8.surface);

 return 0;
}

/*
Compile within Unix/Linux/msys
gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` && ./main

Static Compile within Unix/Linux/msys
gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --static-libs` -static && ./main

Compiling on Windows:

can dynamic link with my msys install
set PATH=C:\msys64\mingw32\bin;
gcc -Wall -ansi -pedantic main.c -o main -IC:\msys64\mingw32\include\SDL2 -Dmain=SDL_main -LC:\msys64\mingw32\lib -lmingw32 -lSDL2main -lSDL2 && main

More frequently, I compile with my official Windows install in C:\SDL
set PATH=C:\TDM-GCC-32\bin;C:\SDL\bin;
gcc -Wall -ansi -pedantic main.c -o main -IC:\SDL\include\SDL2 -Dmain=SDL_main -LC:\SDL\lib -lmingw32 -lSDL2main -lSDL2 && main

can static compile too. (only works with my install in C:\SDL)
gcc -Wall -ansi -pedantic main.c -o main -IC:\SDL\include\SDL2 -Dmain=SDL_main -LC:\SDL\lib -lmingw32 -lSDL2main -lSDL2 -mwindows  -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc -static && main
*/
