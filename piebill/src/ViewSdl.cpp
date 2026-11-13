
#include "ViewSdl.hpp"

#include <iostream>

View::View() :
  _renderer(nullptr),
  _pieTexture(nullptr),
  _pieRect(0, 0, gSizePie[0], gSizePie[1]),
  _deskTexture(nullptr),
  _billSmileTexture(nullptr),
  _billPieTexture(nullptr),
  _font(nullptr)
{
}

void View::init(const std::string & dataDir, SDL_Renderer * renderer) {

  if (_renderer) {
    std::cerr << "View is already initialized" << std::endl;
    exit(-1);
  }

  _renderer = renderer;
  _pieTexture = loadTexture(dataDir + "pie.png");
  _deskTexture = loadTexture(dataDir + "desk.png");
  _billSmileTexture = loadTexture(dataDir + "bill-smile.png");
  _billPieTexture = loadTexture(dataDir + "bill-pie.png");

  _font = loadFont(dataDir + "arial.ttf", 50);
}

View::~View() {

  if (_pieTexture)        SDL_DestroyTexture(_pieTexture);
  if (_deskTexture)       SDL_DestroyTexture(_deskTexture);
  if (_billSmileTexture)  SDL_DestroyTexture(_billSmileTexture);
  if (_billPieTexture)    SDL_DestroyTexture(_billPieTexture);

  if (_font)              TTF_CloseFont(_font);
}

void View::draw(const Game & game) {

  const Position & piePos = game.getPiePos();
  _pieRect.x = piePos.x + gDeltaPie[0];
  _pieRect.y = piePos.y + gDeltaPie[1];

  // draw welcome message or desks
  auto gameStatus = game.getStatus();
  if (gameStatus == Game::Status::Pause) {
    SDL_RenderCopy(_renderer, _pieTexture, nullptr, &_pieRect);
  }
  else if (gameStatus == Game::Status::Ready) {
    SDL_RenderCopy(_renderer, _pieTexture, nullptr, &_pieRect);
    renderText("Click to start", 450, 400);
  }
  else {  // play
    for (const Desk & d : game.getDesks()) {

      Desk::Status deskStatus = d.getStatus();
      Position deskPos = d.getPos();
      int dx = deskPos.x;
      int dy = deskPos.y;

      // desk
      SDL_Rect deskSprite = {dx+gDeltaDesk[0], dy+gDeltaDesk[1], gSizeDesk[0], gSizeDesk[1]};
      SDL_RenderCopy(_renderer, _deskTexture, nullptr, &deskSprite);

      // bill
      if (deskStatus == Desk::Status::Smile) {
        SDL_Rect billSmileSprite = {dx+gDeltaBill[0], dy+gDeltaBill[1], gSizeBill[0], gSizeBill[1]};
        SDL_RenderCopy(_renderer, _billSmileTexture, nullptr, &billSmileSprite);
      }
      else if (deskStatus == Desk::Status::Pie) {
        SDL_Rect billPieSprite = {dx+gDeltaBill[0], dy+gDeltaBill[1], gSizeBill[0], gSizeBill[1]};
        SDL_RenderCopy(_renderer, _billPieTexture, nullptr, &billPieSprite);
      }
    }

    SDL_RenderCopy(_renderer, _pieTexture, nullptr, &_pieRect);
  }

  // draw score
  renderText("Score: " + std::to_string(game.getScore()), 20, 10);

  // draw remaining time
  renderText("Time: " + std::to_string(int(game.getPlayRemTime())), gWinSize[0] - 220, 10);

}

TTF_Font * View::loadFont(const std::string & filename, int ptsize) {
  TTF_Font * font = TTF_OpenFont(filename.c_str(), ptsize);
  if (font == nullptr) {
    std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    exit(-1);
  }
  return font;
}

SDL_Texture * View::loadTexture(const std::string & filename) {

  SDL_Surface * surface = IMG_Load(filename.c_str());
  if (surface == nullptr) {
    std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
    exit(-1);
  }

  SDL_Texture * texture = SDL_CreateTextureFromSurface(_renderer, surface);
  if (texture == nullptr) {
    std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  SDL_FreeSurface(surface);

  return texture;
}

void View::renderText(const std::string & str, int x, int y) {
  SDL_Surface * surface = TTF_RenderText_Solid(_font, str.c_str(), SDL_Color {255, 0, 0, 255});
  SDL_Rect rect{ x, y, surface->w, surface->h };
  SDL_Texture * texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_FreeSurface(surface);
  SDL_RenderCopy(_renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}

