#pragma once

#include "Game.hpp"

#include <iostream>

class ViewConsole {
  private:
    const Game & _refGame;

  public:
    ViewConsole(const Game & refGame);
    void printGame() const;
    int askMove() const;
};

char fmtCell(const Cell c);

std::string fmtStatus(const Status s);

