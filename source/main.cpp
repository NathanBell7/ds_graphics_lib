#include "sprites.hpp"
#include <nds.h>
#include <stdio.h>

#include "blue_head_down.h"

int main() {

  lcdMainOnTop();          // set main screen to top
                           //
  videoSetMode(MODE_5_2D); // set video mode main
  videoSetModeSub(MODE_5_2D);
  consoleDemoInit();

  SpriteController *spriteController = new SpriteController();

  spriteController->initializeDisplays(true, false);

  int spriteX = 50;
  int spriteY = 50;
  int priority = 0;
  int paletteNumber = 0;
  bool isMainScreen = true;

  int spriteId = spriteController->createNewSprite(isMainScreen, SpriteSize_16x16,
                                                   spriteX, spriteY, priority);

  spriteController->addPalette(paletteNumber, isMainScreen, blue_head_downPal,
                               blue_head_downPalLen);

  spriteController->setSpritePaletteNumber(spriteId, isMainScreen, paletteNumber);

  spriteController->setSpriteTiles(spriteId, isMainScreen, blue_head_downTiles,
                                   blue_head_downTilesLen);

  while (1) {
    scanKeys();

    if (keysHeld() & KEY_LEFT) {
      spriteX -= 5;
      spriteController->setSpriteX(spriteId, isMainScreen, spriteX);
    }

    if (keysHeld() & KEY_RIGHT) {
      spriteX += 5;
      spriteController->setSpriteX(spriteId, isMainScreen, spriteX);
    }

    if (keysHeld() & KEY_UP) {
      spriteY -= 5;
      spriteController->setSpriteY(spriteId, isMainScreen, spriteY);
    }

    if (keysHeld() & KEY_DOWN) {
      spriteY += 5;
      spriteController->setSpriteY(spriteId, isMainScreen, spriteY);
    }

    spriteController->updateDisplays(true, true);
  }

  return 0;
}
