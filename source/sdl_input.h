/*sdl_input.h*/

int log_loop_begin=0; /*special secret variable I am experimenting with*/

/*this function is an SDL port of the keyboard function from the Raylib version of Chaste Tris*/
void keyboard()
{
 int key;
 SDL_PollEvent( &e );
  if( e.type == SDL_QUIT ){loop=0; printf("X clicked! This program will close!\n");}
  if (e.type == SDL_KEYDOWN && e.key.repeat==0)
  {


   key=e.key.keysym.sym;

   switch(key)
   {
    case SDLK_ESCAPE:
    loop=0;
    break;

    case SDLK_z:
     move_id='Z';
     /*block_rotate_left_basic();*/
    break;
    case SDLK_x:
     move_id='X';
     /*block_rotate_right_basic();*/
    break;

    /*the main 4 directions*/
    case SDLK_UP:
    case SDLK_w:
     move_id='W';
     tetris_move_up();
    break;
    case SDLK_DOWN:
    case SDLK_s:
     move_id='S';
     tetris_move_down();
    break;
    case SDLK_LEFT:
    case SDLK_a:
     move_id='A';
    tetris_move_left();
    break;
    case SDLK_RIGHT:
    case SDLK_d:
     move_id='D';
     tetris_move_right();
    break;

   }

  }

}



