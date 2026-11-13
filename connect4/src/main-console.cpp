
#include "Player.hpp"
#include "UiConsole.hpp"

#include <iostream>

int main(int argc, char ** argv) {

  std::unique_ptr<Player> player1 = gPlayerFactory["human"]();
  std::unique_ptr<Player> player2 = gPlayerFactory["mc1k"]();

  int score1 = 0;
  int score2 = 0;

  Game game;
  ViewConsole view(game);

  while (true) {

    while (game.isRunning()) {

      view.printGame();

      const Status status = game.status();
      Player * player = status == Status::Play1 ? player1.get() : player2.get();

      if (not player->canPlay()) {
        const int move = view.askMove();
        player->externalMove(move);
      }

      const int move = player->genMove(game);
      game.playMove(move);
    }

    view.printGame();

    Status status = game.status();
    if (status == Status::Win1)
      score1++;
    else if (status == Status::Win2)
      score2++;

    std::cout << "\n*** Game Over ***" << std::endl;
    std::cout << "score1: " << score1 << std::endl;
    std::cout << "score2: " << score2 << std::endl;

    game.newGame();

  }

  return 0;
}

