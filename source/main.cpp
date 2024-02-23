#include "sprites.hpp"
#include <nds.h>
#include <stdio.h>

#include "blue_head_down.h"

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
  while (1) {

    spriteController->updateDisplays(true, false);
  }

  return 0;
}
