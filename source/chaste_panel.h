/*chastity tetris*/

/*Part 1: Declaring variables and constants.*/

struct panel_player
{
 int size,color;
 SDL_Rect rect;
 int x,y;
};


struct panel_player player;

void player_init()
{
 /*set up the values of the player*/
 player.color=SDL_MapRGB(surface->format,255,255,0);
 player.size=36;
 player.rect.x=1*player.size;
 player.rect.y=1*player.size;
 player.rect.w=player.size;
 player.rect.h=player.size;
 player.x=4;
 player.y=4;
}

#define tetris_array_size 0x1000

/*main block structure*/
struct tetris_grid
{
 int array[tetris_array_size];
};

struct tetris_grid main_grid,temp_grid;

int grid_width=10,grid_height=20;

/*main block structure*/
struct tetris_block
{
 int array[16];
 int color;
 int spawn_x,spawn_y; /*where block spawns on entry*/
 int x,y; /*current location of block*/
 int width_used; /*width of block actually used*/
 int id;
};

/*details of main block*/

struct tetris_block main_block,hold_block,temp_block; /*the structures which will be the main,hold,temp block*/


int moves=0; /*number of valid moves*/
int moves_tried=0; /*number of attempted moves*/
int last_move_spin=0; /*was the last move a t spin?*/
int last_move_fail; /*did the last move fail?*/
int back_to_back=0;
int score=0;

char move_log[0x1000000]; /*large array to store moves*/

int empty_color=0x000000;

void grid_clear()
{
 int x,y;
 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   main_grid.array[x+y*grid_width]=empty_color;
   x+=1;
  }
  y+=1;
 }
}


/*all things about moving down*/
void down()
{
 player.y+=1;
 if(player.y==grid_height){player.y-=1;}
}

/*all things about moving up*/
void up()
{
 player.y-=1;
 if(player.y<0){player.y+=1;}
}

/*all things about moving right*/
void right()
{
 player.x+=1;
 if(player.x==grid_width-1){player.x-=1;}
}

/*all things about moving left*/
void left()
{
 player.x-=1;
 if(player.x<0){player.x+=1;}
}


