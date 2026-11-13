
#include "ViewSdl.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <filesystem>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// World
///////////////////////////////////////////////////////////////////////////////

struct World {
  SDL_Window * window;
  SDL_Renderer * renderer;
  uint64_t oldT;
  double pauseTime;
  View view;
  Game game;

  World() :
    window(nullptr),
    renderer(nullptr),
    oldT(0),
    pauseTime(0),
    view(),
    game()
  {}
};

///////////////////////////////////////////////////////////////////////////////
// quit
///////////////////////////////////////////////////////////////////////////////

void quit(World & world) {

  SDL_DestroyRenderer(world.renderer);
  SDL_DestroyWindow(world.window);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

#ifdef __EMSCRIPTEN__
  emscripten_cancel_main_loop();
#else
  exit(0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// mainLoop
///////////////////////////////////////////////////////////////////////////////

void mainLoop(void * pWorld) {

  World & world = *static_cast<World*>(pWorld);

  // process events
  SDL_Event event;
  if (SDL_PollEvent(&event)) {

    // quit
    if (event.type == SDL_QUIT)
      quit(world);

    // keyboard
    else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE)
        quit(world);
      if (event.key.keysym.scancode == SDL_SCANCODE_Q)
        quit(world);
    }

    // mouse motion
    else if (event.type == SDL_MOUSEMOTION) {
      int x = event.button.x;
      int y = event.button.y;
      world.game.movePie({x, y});
    }

    // mouse button
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
      if (event.button.button == 1) {
        int x = event.button.x;
        int y = event.button.y;
        world.game.movePie({x, y});
        world.game.launchPie();
      }
    }

  }

  // update game
  uint64_t newT = SDL_GetTicks64();
  double dt = double(newT - world.oldT) * 0.001;
  world.oldT = newT;
  world.game.step(dt);

  // draw 
  SDL_SetRenderDrawColor(world.renderer, gBgColor[0], gBgColor[1], gBgColor[2], gBgColor[3]);
  SDL_RenderClear(world.renderer);
  world.view.draw(world.game);
  SDL_RenderPresent(world.renderer);

}

///////////////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////////////

int main(int, char ** argv) {

  World world;
  void * pWorld = static_cast<void*>(&world);

  // SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
    exit(-1);
  }

  if (TTF_Init() != 0) {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    exit(-1);
  }

  world.window = SDL_CreateWindow(gAppName, 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
      gWinSize[0], gWinSize[1],
      0);
  if (world.window == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  world.renderer = SDL_CreateRenderer(world.window, -1, SDL_RENDERER_ACCELERATED);
  if (world.renderer == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  // assets
#ifdef __EMSCRIPTEN__
  const std::string dataDir = "data/";
#else
  const std::string dataDir = 
    (std::filesystem::path(argv[0]).parent_path() / "../data/").string();
#endif

  // view
  world.view.init(dataDir, world.renderer);

  // game
  world.game.movePie({gWinSize[0]/2, gWinSize[1]/2});

  // run main loop
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(mainLoop, pWorld, 120, 1);
#else
  while (true) mainLoop(pWorld);
#endif

  return 0;
}

