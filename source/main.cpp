#include <stdio.h>
#include <nds.h>
#include "sprites.hpp"

#include "blue_head_down.h"

int main(){

	videoSetMode(MODE_5_2D);//set video mode main
	videoSetModeSub(MODE_5_2D);
  lcdMainOnTop(); //set main screen to top
  SpriteController SpriteController = new SpriteController();
  while (1){

  }

  return 0;
  
}
