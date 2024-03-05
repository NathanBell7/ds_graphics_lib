#ifndef SPRITES_H
#define SPRITES_H
#include <nds.h>

const int COLOURS_PER_PALETTE = 16;
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

  void initializeDisplays(bool mainScreen, bool subScreen);

  int createNewSprite(bool isMainScreen, SpriteSize spriteSize, int x, int y,
                      int priority);

  void updateDisplays(bool isMainScreen, bool subScreen);

  int addPalette(int paletteNumber, bool isMainScreen,
                 const unsigned short palette[], unsigned short paletteLen);

  int setSpriteX(int spriteId, bool isMainScreen, int x);

  int setSpriteY(int spriteId, bool isMainScreen, int y);

  int setSpritePriority(int spriteId, bool isMainScreen, int priority);

  int setSpritePaletteNumber(int spriteId, bool isMainScreen, int paletteNumber);

  int setSpriteTiles(int spriteId, bool isMainScreen, const unsigned int tiles[],
                     unsigned int tilesLen);

  bool validateSpriteId(int spriteId, bool mainScreen);

  bool validateSpritePaletteNumber(int paletteNumber, bool mainScreen);

  bool validatePaletteNumber(int paletteNumber);

  bool validatePriority(int priority);
};

#endif
