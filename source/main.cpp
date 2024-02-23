#include <stdio.h>
#include <nds.h>
#include "sprites.hpp"

int main(){

	videoSetMode(MODE_5_2D);//set video mode main
	videoSetModeSub(MODE_5_2D);
  lcdMainOnTop(); //set main screen to top
  while (1){

  }

  return 0;
  
}
