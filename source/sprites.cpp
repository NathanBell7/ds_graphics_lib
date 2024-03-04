#include "sprites.hpp"
#include <nds.h>

Sprite ::Sprite(OamState *screenOam, SpriteSize spriteSize, int id, int x,
                int y, int priority) {
  this->screenOam = screenOam;
  this->spriteSize = spriteSize;
  this->id = id;
  this->spriteGfxPointer = oamAllocateGfx(this->screenOam, this->spriteSize,
                                          SpriteColorFormat_16Color);
  this->x = x;
  this->y = y;
  this->priority = priority;
  this->paletteNumber = paletteNumber;
  this->updateData();
}

void Sprite::updateData() {
  oamSet(this->screenOam,
         this->id,                  // Sprite id
         this->x,                   // X position
         this->y,                   // Y position
         this->priority,            // Priority (lower is better priority)
         this->paletteNumber,       // Which palette to use
         this->spriteSize,          // Sprite size can be 8x8; 16x16; 32x32;
                                    // 16x8 etc;
         SpriteColorFormat_16Color, // Colour format can be
                                    // SpriteColorFormat_16Color;
                                    // SpriteColorFormat_256Color;
         this->spriteGfxPointer,
         0,      // affine index (if < 0 or > 31 the sprite will be unrotated)
         false,  // double sprite size if affine index > 0
         false,  // hidden
         false,  // flip vertical
         false,  // flip horizontal
         false); // mosaic?
}

void Sprite::setX(int x) {
  this->x = x;
  this->updateData();
}

void Sprite::setY(int y) {
  this->y = y;
  this->updateData();
}

int Sprite::getX() {
  return this->x;
}

int Sprite::getY() {
  return this->y;
}

void Sprite::setPriority(int priority) {
  this->priority = priority;
  this->updateData();
}

void Sprite::setPaletteNumber(int paletteNumber) {
  this->paletteNumber = paletteNumber;
  this->updateData();
}

void Sprite::setTiles(const unsigned int tiles[], unsigned int tilesLen) {
  dmaCopy(tiles, this->spriteGfxPointer, tilesLen);
  this->updateData();
}

SpriteController::SpriteController() {
  this->currentIdMainScreen = 0;
  this->currentIdSubScreen = 0;
}

int SpriteController::createNewSprite(bool mainScreen, SpriteSize spriteSize,
                                      int x, int y, int priority) {
  if (mainScreen == true) {
    if (currentIdMainScreen < MAX_SPRITES_PER_SCREEN - 1) {
      Sprite *sprite = new Sprite(&oamMain, spriteSize, currentIdMainScreen, x,
                                  y, priority);
      spritesMain[this->currentIdMainScreen] = sprite;
      this->currentIdMainScreen++;
      return this->currentIdMainScreen;
    }
  } else {
    if (currentIdSubScreen < MAX_SPRITES_PER_SCREEN - 1) {
      Sprite *sprite =
          new Sprite(&oamSub, spriteSize, currentIdSubScreen, x, y, priority);
      spritesSub[this->currentIdSubScreen] = sprite;
      this->currentIdSubScreen++;
      return this->currentIdSubScreen;
    }
  }
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

void SpriteController::updateDisplays(bool mainScreen, bool subScreen) {
  swiWaitForVBlank();
  if (mainScreen == true) {
    oamUpdate(&oamMain);
  }
  if (subScreen == true) {
    oamUpdate(&oamSub);
  }
}

void SpriteController::addPalette(int paletteNumber, bool mainScreen,
                                  const unsigned short palette[],
                                  unsigned short paletteLen) {
  if (mainScreen == true) {
    dmaCopy(palette, &SPRITE_PALETTE[paletteNumber * COLOURS_PER_PALETTE],
            paletteLen);
    initialisedPalettesMain[paletteNumber] = true;
  } else {
    dmaCopy(palette, &SPRITE_PALETTE_SUB[paletteNumber * COLOURS_PER_PALETTE],
            paletteLen);
    initialisedPalettesSub[paletteNumber] = true;
  }
}

int SpriteController::getSpriteX(int spriteId, bool mainScreen) {
  if (mainScreen == true){
    return spritesMain[spriteId]->getX();
  } else{
    return spritesSub[spriteId]->getX();
  }
}

int SpriteController::getSpriteY(int spriteId, bool mainScreen) {
  if (mainScreen == true){
    return spritesMain[spriteId]->getY();
  } else{
    return spritesSub[spriteId]->getY();
  }
}

void SpriteController::setSpriteX(int spriteId, bool mainScreen, int x) {
  if (mainScreen == true) {
    spritesMain[spriteId]->setX(x);
  } else {
    spritesSub[spriteId]->setX(x);
  }
}

void SpriteController::setSpriteY(int spriteId, bool mainScreen, int y) {
  if (mainScreen == true) {
    spritesMain[spriteId]->setY(y);
  } else {
    spritesSub[spriteId]->setY(y);
  }
}

void SpriteController::setSpritePriority(int spriteId, bool mainScreen,
                                         int priority) {
  if (mainScreen == true) {
    spritesMain[spriteId]->setPriority(priority);
  } else {
    spritesSub[spriteId]->setPriority(priority);
  }
}

void SpriteController::setSpritePaletteNumber(int spriteId, bool mainScreen,
                                              int paletteNumber) {
  if (mainScreen == true) {
    if (initialisedPalettesMain[paletteNumber] == false) {
      // trying to set uninitialized palette
    }
    spritesMain[spriteId]->setPaletteNumber(paletteNumber);
  } else {
    if (initialisedPalettesSub[paletteNumber] == false) {
      // trying to set uninitialized palette
    }
    spritesSub[spriteId]->setPaletteNumber(paletteNumber);
  }
}

void SpriteController::setSpriteTiles(int spriteId, bool mainScreen,
                                      const unsigned int tiles[],
                                      unsigned int tilesLen) {
  if (mainScreen == true) {
    spritesMain[spriteId]->setTiles(tiles, tilesLen);
  } else {
    spritesSub[spriteId]->setTiles(tiles, tilesLen);
  }
}
