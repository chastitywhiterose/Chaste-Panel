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
     flip();
    break;
    case SDLK_x:
     move_id='X';
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










/*
this function gets input from a previous log file and autoplays the moves from  it.
This feature was first used in Chaste Tris and is great for making demo videos by playing back moves fast
*/
void next_file_input()
{
 int c;
 if(fp_input==NULL){return;}

 c=fgetc(fp_input);

 if(feof(fp_input))
 {
  printf("End of file reached.\n");
  printf("Now use keyboard input.\n");
  /*
   printf("Going back to beginning\n");
   fseek(fp_input,0,SEEK_SET);
  */

  fclose(fp_input); fp_input=NULL;  return;
 }

 else
 {
  /*printf("Character==%c\n",c);*/

  move_id=c;

  if(c=='W'){up();}
  if(c=='S'){down();}
  if(c=='A'){left();}
  if(c=='D'){right();}

  if(c=='Z'){flip();}
  if(c=='X'){more();}
 
 }
}
