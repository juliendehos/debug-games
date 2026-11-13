#pragma once

#include "Game.hpp"

// #include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

///////////////////////////////////////////////////////////////////////////////
// global parameters
///////////////////////////////////////////////////////////////////////////////

const char gAppName [] = "piebill-sdl";
const int gWinSize [2] {1200, 900};
const uint8_t gBgColor [4] {100, 180, 250, 255};

const int gSizePie [2] {100, 75};
const int gSizeDesk [2] {200, 100};
const int gSizeBill [2] {200, 150};

const int gDeltaPie [2] {-50, -37};
const int gDeltaDesk [2] {-100, 75};
const int gDeltaBill [2] {-100, -75};

///////////////////////////////////////////////////////////////////////////////
// view
///////////////////////////////////////////////////////////////////////////////

class View {
  private:
    SDL_Renderer * _renderer;

    SDL_Texture * _pieTexture;
    SDL_Rect _pieRect;

    SDL_Texture * _deskTexture;

    SDL_Texture * _billSmileTexture;

    SDL_Texture * _billPieTexture;

    TTF_Font *_font;

  public:
    View();
    View(const View & v) = delete;
    ~View();

    void init(const std::string & dataDir, SDL_Renderer * renderer);
    void draw(const Game & game);

  private:
    TTF_Font * loadFont(const std::string & filename, int ptsize);
    SDL_Texture * loadTexture(const std::string & filename);
    void renderText(const std::string & str, int x, int y);
};

