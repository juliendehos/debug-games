#include "Player.hpp"

#include <cassert>

///////////////////////////////////////////////////////////////////////////////
// Player
///////////////////////////////////////////////////////////////////////////////

void Player::externalMove(const int move) {
}

bool Player::canPlay() const {
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// PlayerHuman
///////////////////////////////////////////////////////////////////////////////

bool PlayerHuman::canPlay() const {
  return _moveOpt.has_value();
}

void PlayerHuman::externalMove(const int move) {
  _moveOpt.emplace(move);
}

int PlayerHuman::genMove(const Game & game) {
  const int move = _moveOpt.value();
  _moveOpt.reset();
  return move;
}

///////////////////////////////////////////////////////////////////////////////
// PlayerRandom
///////////////////////////////////////////////////////////////////////////////

PlayerRandom::PlayerRandom() :
  _engine(std::random_device{}())
{
}

int PlayerRandom::genMove(const Game & game) {
  assert(game.isRunning());
  const auto moves = game.computeValidMoves();
  const int nMoves = moves.size();
  assert(nMoves > 0);
  std::uniform_int_distribution<int> dist(0, nMoves-1);
  const int k = dist(_engine);
  assert(k>=0);
  assert(k<nMoves);
  return moves[k];
}

///////////////////////////////////////////////////////////////////////////////
// PlayerRandom
///////////////////////////////////////////////////////////////////////////////

PlayerMc::PlayerMc(const int nbSimsPerMove) :
  _nbSimsPerMove(nbSimsPerMove)
{}

int PlayerMc::genMove(const Game & game) {

  const Status winStatus = game.status() == Status::Play1 ? Status::Win1 : Status::Win2;
  const std::vector<int> moves = game.computeValidMoves();
  std::vector<int> scores(moves.size(), 0);

  // compute every moves
  for (unsigned k=0; k<moves.size(); k++) {
    Game gameK0 = game;
    gameK0.playMove(moves[k]);

    // evaluate the move
    for (int n=0; n<_nbSimsPerMove; n++) {
      // playout
      Game gameK = gameK0;
      while (gameK.isRunning()) {
        const int move = _randomPlayer.genMove(gameK);
        gameK.playMove(move);
      }
      // compute score
      const Status status = gameK.status();
      if (status == winStatus)
        scores[k]++;
      else if (status != Status::Tie)
        scores[k]--;
    }
  }

  // find best move
  int bestMove = moves[0];
  int bestScore = scores[0];
  for (unsigned k=1; k<moves.size(); k++) {
    if (scores[k] > bestScore) {
      bestMove = moves[k];
      bestScore = scores[k];
    }
  }

  return bestMove;
}

