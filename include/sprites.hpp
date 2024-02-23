#ifndef SPRITES_H
#define SPRITES_H
#include <nds.h>

const int SPRITE_PALETTE_LENGTH = 16;
const int MAX_SPRITES_PER_SCREEN = 128;
const int MAX_PALETTES_PER_SCREEN = 16;

class Sprite { // a class for dealing with tiled sprites and palettes

private:
  void updateData();

public:
  OamState *screenOam;
  SpriteSize spriteSize;
  int id;
  u16 *spriteGfxPointer;
  int x;
  int y;
  int priority;
  int paletteNumber;

  Sprite(OamState *screenOam, SpriteSize spriteSize, int id, int x, int y,
         int priority);

  void setX(int x); // max x is 255

  void setY(int y); // max y is 191

  void setPriority(int priority); // between 0 and 3

  void setPaletteNumber(int paletteNumber); // between 1 and 16

  void setTiles(const unsigned int tiles[], unsigned int tilesLen);
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
  SpriteController();

  int createNewSprite(bool mainScreen, SpriteSize spriteSize, int x, int y,
                      int priority);

  void clearSprites(bool mainScreen, bool subScreen);

  void updateDisplays(bool main, bool sub);

  void addPalette(int paletteNumber, bool mainScreen,
                  const unsigned short palette[], unsigned short paletteLen);

  void setSpriteX(int spriteId, bool mainScreen, int x);

  void setSpriteY(int spriteId, bool mainScreen, int y);

  void setSpritePriority(int spriteId, bool mainScreen, int priority);

  void setSpritePaletteNumber(int spriteId, bool mainScreen, int paletteNumber);

  void setSpriteTiles(int spriteId, bool mainScreen, const unsigned int tiles[],
                      unsigned int tilesLen);
};

#endif
