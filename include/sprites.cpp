const int SPRITE_PALETTE_LENGTH = 16;
const int MAX_SPRITES_PER_SCREEN = 128;
const int MAX_PALETTES_PER_SCREEN = 16;

class Sprite { // a class for dealing with tiled sprites and 16 colour palettes

private:
  OamState *screenOam;
  SpriteSize spriteSize;
  int id;
  u16 *spriteGfxPointer;
  int x;
  int y;
  int priority;
  int paletteNumber;

  void updateData() {
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

public:
  Sprite(OamState *screenOam, SpriteSize spriteSize, int id, int x, int y,
         int priority) {
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

  void setX(int x) {
    this->x = x;
    this->updateData();
  }

  void setY(int y) {
    this->y = y;
    this->updateData();
  }

  void setPriority(int priority) {
    this->priority = priority;
    this->updateData();
  }

  void setPaletteNumber(int paletteNumber) {
    this->paletteNumber = paletteNumber;
    this->updateData();
  }

  void setSpriteTiles(const unsigned int tiles[], unsigned int tilesLen) {
    dmaCopy(tiles, this->spriteGfxPointer, tilesLen);
    this->updateData();
  }
};

class SpriteController {

private:
  int currentIdMainScreen;
  int currentIdSubScreen;
  Sprite *spritesMain[MAX_SPRITES_PER_SCREEN];
  Sprite *spritesSub[MAX_SPRITES_PER_SCREEN];
  bool initialisedPalettesMain[MAX_PALETTES_PER_SCREEN];
  bool initialisedPalettesSub[MAX_PALETTES_PER_SCREEN];

public:
  SpriteController() {
    this->currentIdMainScreen = 0;
    this->currentIdSubScreen = 0;
  }

  int createNewSprite(bool mainScreen, SpriteSize spriteSize, int x, int y,
                      int priority) {
    if (mainScreen == true) {
      if (currentIdMainScreen < MAX_SPRITES_PER_SCREEN - 1) {
        Sprite *sprite = new Sprite(screenOam, spriteSize, currentIdMainScreen,
                                    x, y, priority);
        spritesMain[this->currentIdMainScreen] = sprite;
        this->currentIdMainScreen++;
        return this->currentIdMainScreen - 1;
      }
    } else {
      if (currentIdSubScreen < MAX_SPRITES_PER_SCREEN - 1) {
        Sprite *sprite = new Sprite(screenOam, spriteSize, currentIdSubScreen,
                                    x, y, priority);
        spritesSub[this->currentIdSubScreen] = sprite;
        this->currentIdSubScreen++;
        return this->currentIdSubScreen - 1;
      }
    }
  }

  void clearSprites(bool mainScreen, bool subScreen) {
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

  void updateDisplays(bool mainScreen, bool subScreen) {
    swiWaitForVBlank();
    if (mainScreen == true) {
      oamUpdate(&oamMain);
    }
    if (subScreen == true) {
      oamUpdate(&oamSub);
    }
  }

  void addPalette(const unsigned short palette[], unsigned short paletteLen,
                  int paletteNumber, bool mainScreen) {
    if (mainScreen == true) {
      dmaCopy(palette, &SPRITE_PALETTE[paletteNumber * SPRITE_PALETTE_LENGTH],
              paletteLen);
      initialisedPalettesMain[paletteNumber] = true;
    } else {
      dmaCopy(palette,
              &SPRITE_PALETTE_SUB[paletteNumber * SPRITE_PALETTE_LENGTH],
              paletteLen);
      initialisedPalettesMain[paletteNumber] = true;
    }
  }

  void setSpriteX(int spriteId, bool mainScreen, int x) {
    if (mainScreen == true) {
      spritesMain[spriteId]->setX(x);
    } else {
      spritesSub[spriteId]->setX(x);
    }
  }

  void setSpriteY(int spriteId, bool mainScreen, int y) {
    if (mainScreen == true) {
      spritesMain[spriteId]->setY(y);
    } else {
      spritesSub[spriteId]->setY(y);
    }
  }

  void setSpritePriority(int spriteId, bool mainScreen, int priority) {
    if (mainScreen == true) {
      spritesMain[spriteId]->setPriority(priority);
    } else {
      spritesSub[spriteId]->setPriority(priority);
    }
  }

  void setSpritePaletteNumber(int spriteId, bool mainScreen,
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

  void setSpriteTiles(int spriteId, bool mainScreen, const unsigned int tiles[],
                      unsigned int tilesLen) {
    if (mainScreen == true) {
      spritesMain[spriteId]->setTiles(tiles, tilesLen);
    } else {
      spritesSub[spriteId]->setTiles(tiles, tilesLen);
    }
  }
};
