#ifndef SPRITES_H
#define SPRITES_H

int SPRITE_PALETTE_LENGTH; // length of each sprite palette (16)
int MAX_SPRITES_PER_SCREEN;
int MAX_PALETTES_PER_SCREEN;

class Sprite { // a class for dealing with tiled sprites and palettes

private:
  OamState *screenOam;   // which screen oam to use
  SpriteSize spriteSize; // how big should the sprite be?
  int id;                // max of 128 sprites, so max id 128
  u16 *spriteGfxPointer; // pointer to the sprite object attribute memory
  int x;                 // x position of sprite
  int y;                 // y position of sprite
  int priority;          // which layer should sprite be on (0-3 top to bottom)
  int paletteNumber;     // which palette to use (1 - 16)

  void updateData();

public:
  Sprite(OamState *screenOam, SpriteSize spriteSize, int id, int x, int y,
         int priority);

  void setX(int x); // max x is 255

  void setY(int y); // max y is 191

  void setPriority(int priority); // between 0 and 3

  void setPaletteNumber(int paletteNumber); // between 1 and 16

  void setSpriteTiles(const unsigned int tiles[], unsigned int tilesLen);
};

class SpriteController {

private:
  int currentIdMainScreen;
  int currentIdSubScreen;
  Sprite spritesMain[128];
  Sprite spritesSub[128];

public:
  SpriteController();

  int create_new_sprite(OamState *screenOam, SpriteSize spriteSize,int x, int y, int priority);

  void clearSpritesMain();

  void clearSpritesSub();

  void clearSprites();

  void updateDisplays(bool main, bool sub);

  void addSpritePalette(const unsigned short palette[],
                        unsigned short paletteLen);
};

#endif
