/*sdl_input.h*/

/*this function controls all keyboard input*/
void keyboard()
{
 int key;
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
     flip();
    break;
    case SDLK_x:
     move_id='X';
     /*block_rotate_right_basic();*/
     more();
    break;

    /*the main 4 directions*/
    case SDLK_UP:
    case SDLK_w:
     move_id='W';
     up();
    break;
    case SDLK_DOWN:
    case SDLK_s:
     move_id='S';
     down();
    break;
    case SDLK_LEFT:
    case SDLK_a:
     move_id='A';
     left();
    break;
    case SDLK_RIGHT:
    case SDLK_d:
     move_id='D';
     right();
    break;

   }

  }

}



