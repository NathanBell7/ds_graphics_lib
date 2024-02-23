#ifndef SPRITES_H
#define SPRITES_H

class Sprite { // a class for dealing with tiled sprites and palettes

public:
  Sprite(OamState *screenOam, SpriteSize spriteSize, int id, int x, int y,
         int priority);

  void setX(int x); // max x is 255

  void setY(int y); // max y is 191

  void setPriority(int priority); // between 0 and 3

  void setPaletteNumber(int paletteNumber); // between 1 and 16

  void setTiles(const unsigned int tiles[], unsigned int tilesLen);
};

class SpriteController {

public:
  SpriteController();

  int createNewSprite(bool mainScreen, SpriteSize spriteSize, int x, int y,
                      int priority);

  void clearSprites(bool mainScreen, bool subScreen);

  void updateDisplays(bool main, bool sub);

  void addPalette(const unsigned short palette[], unsigned short paletteLen);

  void setSpriteX(int spriteId, bool mainScreen, int x);

  void setSpriteY(int spriteId, bool mainScreen, int y);

  void setSpritePriority(int spriteId, bool mainScreen, int priority);

  void setSpritePaletteNumber(int spriteId, bool mainScreen, int paletteNumber);

  void setSpriteTiles(int spriteId, bool mainScreen, const unsigned int tiles[],
                      unsigned int tilesLen);
};

#endif
