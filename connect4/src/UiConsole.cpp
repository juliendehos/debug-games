#include "UiConsole.hpp"


#include <limits> // for std::numeric_limits

char fmtCell(const Cell c) {
  switch (c) {
    case Cell::Empty:   return '.';
    case Cell::Player1: return 'X';
    case Cell::Player2: return 'O';
  }
  return ' ';
}

std::string fmtStatus(const Status s) {
  switch (s) {
    case Status::Play1: return "X plays";
    case Status::Play2: return "O plays";
    case Status::Win1:  return "X wins";
    case Status::Win2:  return "O wins";
    case Status::Tie:   return "It's a tie";
  }
  return "";
}

ViewConsole::ViewConsole(const Game & refGame) :
  _refGame(refGame)
{}

void ViewConsole::printGame() const {

  std::cout << std::endl;

  for (int j=0; j<N_COLS; j++) {
    std::cout << j;
  }

  std::cout << std::endl;

  for (int i=N_ROWS-1; i>=0; i--) {
    for (int j=0; j<N_COLS; j++) {
      const Cell c = _refGame.cell(i, j);
      std::cout << fmtCell(c);
    }
    std::cout << std::endl;
  }

  const Status s = _refGame.status();
  std::cout << fmtStatus(s) << std::endl;

}

bool hasUnextractedInput() {
  return !std::cin.eof() && std::cin.peek() != '\n';
}

void ignoreLine() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int ViewConsole::askMove() const {
  if (not std::cin)
    exit(-1);

  int move;
  while (true) {
    std::cout << "move? ";
    std::flush(std::cout);
    std::cin >> move;
    if (hasUnextractedInput()) {
      std::cerr << "not a number!" << std::endl;
      ignoreLine();
    }
    else
      break;
  }

  return move;
}

