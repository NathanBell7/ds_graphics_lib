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
   *  graphics. This should be called before any sprites are attempted to be
   *  rendered on a given screen.
   *
   * Parameters:
   *
   *  - mainScreen - Should the main screen(default top) be initialized?
   *  - subScreen - Should the sub screen(default bottom) be initialized?
   *
   * Returns:
   *
   *  Returns nothing/void.
   *
   */
  void initializeDisplays(bool mainScreen, bool subScreen);

  /* Description:
   *
   *  Creates a new sprite object that will be displayed to the screen. There
   *  can be a maximum of 128 sprites per screen. Can also be used to
   *  "re-initialize" a display and delete all currently existing sprites.
   *
   * Parameters:
   *
   *  - isMainScreen - Should this sprite appear on the main or sub
   *                   screen(default top and bottom).
   *
   *  - spriteSize - The size that the sprite's image will be. In the format
   *                 SpriteSize_<X>x<Y> where the X and Y must be minimum of 8
   *                 and max of 64. All supported sizes in README.md
   *
   *  - x - The x position where the sprite will be displayed(0-255, but can go
   *        outside those values to be offscreen).
   *
   *  - y - The y position where the sprite will be displayed(0-191, but can go
   *        outside those values to be offscreen).
   *
   *  - priority - How "far forward" should the sprite be displayed(0-3).
   *
   * Returns:
   *
   *  Returns the id of the newly created sprite.
   *
   */
  int createNewSprite(bool isMainScreen, SpriteSize spriteSize, int x, int y,
                      int priority);

  /* Description:
   *
   *  Adds a new colour palette that any of the sprites of the same screen can
   *  access. There can be a maximum of 16 palettes per screen.
   *
   * Parameters:
   *
   *  - paletteNumber - Which of the 16 palettes to set(0-15).
   *  - isMainScreen - Is this palette for images on the main screen?
   *  - palette - The actual palette from the gritted image.
   *  - paletteLen - The size of the palette in bytes from the gritted image.
   *
   * Returns:
   *
   *  Returns 1 if the palette was successfully added, returns -1 if not.
   *
   */
  int addPalette(int paletteNumber, bool isMainScreen,
                 const unsigned short palette[], unsigned short paletteLen);

  /* Description:
   *
   *  Sets a Sprite's x position(0-255, but can go outside those values to be
   * offscreen).
   *
   * Parameters:
   *
   *  - spriteId - Which of the 128 sprites to change the x value of.
   *  - isMainScreen - Is the sprite on the main screen or the sub screen.
   *  - x - The new x position of the sprite.
   *
   * Returns:
   *
   *  Returns 1 if the x value was successfully set, -1 if not.
   *
   */
  int setSpriteX(int spriteId, bool isMainScreen, int x);

  /* Description:
   *
   *  Sets a Sprite's y position(0-191, but can go outside those values to be
   *  offscreen).
   *
   * Parameters:
   *
   *  - spriteId - Which of the 128 sprites to change the y value of.
   *  - isMainScreen - Is the sprite on the main screen or the sub screen.
   *  - y - The new y position of the sprite.
   *
   * Returns:
   *
   *  Returns 1 if the y value was successfully set, -1 if not.
   *
   */
  int setSpriteY(int spriteId, bool isMainScreen, int y);

  /* Description:
   *
   *  Sets the priority (which layer to be displayed on) of a specified
   *  sprite(0-3, with 0 being the top layer).
   *
   * Parameters:
   *
   *  - spriteId - Which of the 128 sprites to change the y value of.
   *  - isMainScreen - Is the sprite on the main screen or the sub screen.
   *  - priority - The new priority to set the sprite to.
   *
   * Returns:
   *
   *  Returns 1 if the priority was successfully set, -1 if not.
   *
   */
  int setSpritePriority(int spriteId, bool isMainScreen, int priority);

  /* Description:
   *
   *  Sets which of the 16 palettes that a sprite should use.
   *
   * Parameters:
   *
   *  - spriteId - Which of the 128 sprites to change the y value of.
   *  - isMainScreen - Is the sprite on the main screen or the sub screen.
   *  - paletteNumber - Which of the palettes should the sprite use (0-15)
   *
   * Returns:
   *
   *  Returns 1 if the palette was successfully set, -1 if not.
   *
   */
  int setSpritePaletteNumber(int spriteId, bool isMainScreen,
                             int paletteNumber);

  /* Description:
   *
   *  Sets the image that the sprite will display to the screen
   *
   * Parameters:
   *
   *  - spriteId - Which of the 128 sprites to change the y value of.
   *  - isMainScreen - Is the sprite on the main screen or the sub screen.
   *  - tiles - The image that has been tiled by grit.
   *  - tilesLen - The size of the tiles in bytes.
   *
   * Returns:
   *
   *  Returns 1 if the tiles were successfully set, -1 if not.
   *
   */
  int setSpriteTiles(int spriteId, bool isMainScreen,
                     const unsigned int tiles[], unsigned int tilesLen);

  /* Description:
   *  Displays all of the current sprites to the screen in their current states.
   *  This method must be called to display any changes to the sprites that have
   *  been made(This would usually be at the end of the "game loop"/every
   * frame). These changes include changing the x value, the y value, the
   * palette etc.
   *
   * Parameters:
   *
   *  - mainScreen - Should the main screen be updated?
   *  - subScreen - Should the sub screen be updated?
   *
   * Returns:
   *
   *  Returns void/nothing.
   *
   */
  void updateDisplays(bool mainScreen, bool subScreen);

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
