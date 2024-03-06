#ifndef SPRITES_H
#define SPRITES_H
#include <nds.h>

const int COLOURS_PER_PALETTE = 16;
const int MAX_SPRITES_PER_SCREEN = 128;
const int MAX_PALETTES_PER_SCREEN = 16;

// TODO: Write up method explanations
class SpriteController {

public:
  SpriteController();

  /* Description:
   *
   *  A method to initialize the specified screen for displaying sprite
   * graphics. This should be called before any sprites are attempted to be
   * rendered on a given screen.
   *
   *
   * Parameters:
   *
   *  - mainScreen - should the main screen be initialized?
   *  - subScreen - should the sub screen be initialized?
   *
   *
   * Returns:
   *
   *  Returns nothing/void.
   *
   */
  void initializeDisplays(bool mainScreen, bool subScreen);

  int createNewSprite(bool isMainScreen, SpriteSize spriteSize, int x, int y,
                      int priority);

  void updateDisplays(bool isMainScreen, bool subScreen);

  int addPalette(int paletteNumber, bool isMainScreen,
                 const unsigned short palette[], unsigned short paletteLen);

  int setSpriteX(int spriteId, bool isMainScreen, int x);

  int setSpriteY(int spriteId, bool isMainScreen, int y);

  int setSpritePriority(int spriteId, bool isMainScreen, int priority);

  int setSpritePaletteNumber(int spriteId, bool isMainScreen,
                             int paletteNumber);

  int setSpriteTiles(int spriteId, bool isMainScreen,
                     const unsigned int tiles[], unsigned int tilesLen);

private:
  class Sprite {

  public:
    Sprite(OamState *screenOam, SpriteSize spriteSize, int id, int x, int y,
           int priority);

    void setX(int x);

    void setY(int y);

    void setPriority(int priority);

    void setPaletteNumber(int paletteNumber);

    void setTiles(const unsigned int tiles[], unsigned int tilesLen);

  private:
    OamState *screenOam;
    SpriteSize spriteSize;
    int id;
    u16 *spriteGfxPointer;
    int x;
    int y;
    int priority;
    int paletteNumber;

    void updateData();
  };

  int currentIdMainScreen;
  int currentIdSubScreen;
  Sprite *spritesMain[MAX_SPRITES_PER_SCREEN];
  Sprite *spritesSub[MAX_SPRITES_PER_SCREEN];
  bool initialisedPalettesMain[MAX_PALETTES_PER_SCREEN];
  bool initialisedPalettesSub[MAX_PALETTES_PER_SCREEN];

  bool validateSpriteId(int spriteId, bool mainScreen);
  bool validateSpritePaletteNumber(int paletteNumber, bool mainScreen);
  bool validatePaletteNumber(int paletteNumber);
  bool validatePriority(int priority);
};

#endif
