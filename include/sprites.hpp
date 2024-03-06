#ifndef SPRITES_H
#define SPRITES_H
#include <nds.h>

const int COLOURS_PER_PALETTE = 16;
const int MAX_SPRITES_PER_SCREEN = 128;
const int MAX_PALETTES_PER_SCREEN = 16;

// TODO: Write up method explanations
class SpriteController {

private:

  class Sprite {

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
             0, // affine index (if < 0 or > 31 the sprite will be unrotated)
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

    void setTiles(const unsigned int tiles[], unsigned int tilesLen) {
      dmaCopy(tiles, this->spriteGfxPointer, tilesLen);
      this->updateData();
    }
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
};

#endif
