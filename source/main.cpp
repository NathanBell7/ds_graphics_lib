#include "sprites.hpp"
#include <nds.h>
#include <stdio.h>

#include "blue_head_down.h"
#include "blue_head_down_2.h"

int main() {

  videoSetMode(MODE_5_2D); // set video mode main
  videoSetModeSub(MODE_5_2D);

  lcdMainOnTop(); // set main screen to top
                  

  SpriteController *spriteController = new SpriteController();

  spriteController->initializeDisplays(true, false);

  int sprite1 =
      spriteController->createNewSprite(true, SpriteSize_16x16, 50, 50, 1);

  spriteController->addPalette(0, true, blue_head_downPal,
                               blue_head_downPalLen);
  spriteController->setSpritePaletteNumber(0, true, 0);
  spriteController->setSpriteTiles(0, true, blue_head_downTiles,
                                   blue_head_downTilesLen);


  int sprite2 =
      spriteController->createNewSprite(true, SpriteSize_16x16, 100, 100, 1);

  spriteController->addPalette(1, true, blue_head_down_2Pal,
                               blue_head_down_2PalLen);
  spriteController->setSpritePaletteNumber(1, true, 1);
  spriteController->setSpriteTiles(1, true, blue_head_down_2Tiles,
                                   blue_head_down_2TilesLen);


  while (1) {
		scanKeys();

		if(keysDown() & KEY_LEFT){
      spriteController->setSpriteX(0, true, spriteController->getSpriteX(0, true) - 5);
		}

		if(keysDown() & KEY_RIGHT){
      spriteController->setSpriteX(0, true, spriteController->getSpriteX(0, true) + 5);
		}

		if(keysDown() & KEY_UP){
      spriteController->setSpriteY(0, true, spriteController->getSpriteY(0, true) - 5);
		}

		if(keysDown() & KEY_DOWN){
      spriteController->setSpriteY(0, true, spriteController->getSpriteY(0, true) + 5);
		}

    spriteController->updateDisplays(true, false);
  }

  return 0;
}
