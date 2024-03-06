#include "sprites.hpp"
#include <nds.h>
#include <stdio.h>

SpriteController::SpriteController() {
  this->currentIdMainScreen = 0;
  this->currentIdSubScreen = 0;
}

void SpriteController::initializeDisplays(bool mainScreen, bool subScreen) {
  if (mainScreen == true) {
    for (int i = 0; i < MAX_SPRITES_PER_SCREEN; i++) {
      spritesMain[i] = 0;
    }
    oamInit(&oamMain, SpriteMapping_1D_128, false);
    currentIdMainScreen = 0;
  }
  if (subScreen == true) {
    for (int i = 0; i < MAX_SPRITES_PER_SCREEN; i++) {
      spritesSub[i] = 0;
    }
    oamInit(&oamSub, SpriteMapping_1D_128, false);
    currentIdSubScreen = 0;
  }
}

int SpriteController::createNewSprite(bool isMainScreen, SpriteSize spriteSize,
                                      int x, int y, int priority) {
  if (!this->validatePriority(priority)) {
    return -1;
  }
  if (isMainScreen == true) {
    if (currentIdMainScreen < MAX_SPRITES_PER_SCREEN - 1) {
      Sprite *sprite =
          new Sprite(&oamMain, spriteSize, currentIdMainScreen, x, y, priority);
      spritesMain[this->currentIdMainScreen] = sprite;
      this->currentIdMainScreen++;
      return this->currentIdMainScreen - 1;
    } else {
      return -1;
    }
  } else {
    if (currentIdSubScreen < MAX_SPRITES_PER_SCREEN - 1) {
      Sprite *sprite =
          new Sprite(&oamSub, spriteSize, currentIdSubScreen, x, y, priority);
      spritesSub[this->currentIdSubScreen] = sprite;
      this->currentIdSubScreen++;
      return this->currentIdSubScreen - 1;
    } else {
      return -1;
    }
  }
}

void SpriteController::updateDisplays(bool isMainScreen, bool subScreen) {
  swiWaitForVBlank();
  if (isMainScreen == true) {
    oamUpdate(&oamMain);
  }
  if (subScreen == true) {
    oamUpdate(&oamSub);
  }
}

int SpriteController::addPalette(int paletteNumber, bool isMainScreen,
                                 const unsigned short palette[],
                                 unsigned short paletteLen) {
  if (!this->validatePaletteNumber(paletteNumber)) {
    return -1;
  }
  if (isMainScreen == true) {
    dmaCopy(palette, &SPRITE_PALETTE[paletteNumber * COLOURS_PER_PALETTE],
            paletteLen);
    initialisedPalettesMain[paletteNumber] = true;
  } else {
    dmaCopy(palette, &SPRITE_PALETTE_SUB[paletteNumber * COLOURS_PER_PALETTE],
            paletteLen);
    initialisedPalettesSub[paletteNumber] = true;
  }
  return 1;
}

int SpriteController::setSpriteX(int spriteId, bool isMainScreen, int x) {
  if (!this->validateSpriteId(spriteId, isMainScreen)) {
    return -1;
  }
  if (isMainScreen == true) {
    spritesMain[spriteId]->setX(x);
  } else {
    spritesSub[spriteId]->setX(x);
  }
  return 1;
}

int SpriteController::setSpriteY(int spriteId, bool isMainScreen, int y) {
  if (!this->validateSpriteId(spriteId, isMainScreen)) {
    return -1;
  }
  if (isMainScreen == true) {
    spritesMain[spriteId]->setY(y);
  } else {
    spritesSub[spriteId]->setY(y);
  }
  return 1;
}

int SpriteController::setSpritePriority(int spriteId, bool isMainScreen,
                                        int priority) {
  if (!this->validatePriority(priority) ||
      !this->validateSpriteId(spriteId, isMainScreen)) {
    return -1;
  }
  if (isMainScreen == true) {
    spritesMain[spriteId]->setPriority(priority);
  } else {
    spritesSub[spriteId]->setPriority(priority);
  }
  return 1;
}

int SpriteController::setSpritePaletteNumber(int spriteId, bool isMainScreen,
                                             int paletteNumber) {

  if (!this->validateSpriteId(spriteId, isMainScreen) ||
      !this->validateSpritePaletteNumber(paletteNumber, isMainScreen)) {
    return -1;
  }
  if (isMainScreen == true) {
    spritesMain[spriteId]->setPaletteNumber(paletteNumber);
  } else {
    spritesSub[spriteId]->setPaletteNumber(paletteNumber);
  }
  return 1;
}

int SpriteController::setSpriteTiles(int spriteId, bool isMainScreen,
                                     const unsigned int tiles[],
                                     unsigned int tilesLen) {
  if (!this->validateSpriteId(spriteId, isMainScreen)) {
    return -1;
  }
  if (isMainScreen == true) {
    spritesMain[spriteId]->setTiles(tiles, tilesLen);
  } else {
    spritesSub[spriteId]->setTiles(tiles, tilesLen);
  }
  return 1;
}

bool SpriteController::validateSpriteId(int spriteId, bool isMainScreen) {
  if (((isMainScreen && spriteId <= currentIdMainScreen) ||
       (!isMainScreen && spriteId <= currentIdSubScreen)) &&
      spriteId >= 0) {
    return true;
  } else {
    return false;
  }
}

bool SpriteController::validateSpritePaletteNumber(int paletteNumber,
                                                   bool isMainScreen) {
  if (validatePaletteNumber(paletteNumber) &&
      ((isMainScreen && this->initialisedPalettesMain[paletteNumber]) ||
       (!isMainScreen && this->initialisedPalettesSub[paletteNumber]))) {
    return true;
  } else {
    return false;
  }
}

bool SpriteController::validatePaletteNumber(int paletteNumber) {
  if (paletteNumber >= 0 && paletteNumber <= 15) {
    return true;
  } else {
    return false;
  }
}

bool SpriteController::validatePriority(int priority) {
  return (priority >= 0 && priority <= 3);
}
