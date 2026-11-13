
#include "Game.hpp"

///////////////////////////////////////////////////////////////////////////////
// utils
///////////////////////////////////////////////////////////////////////////////

int distance2(const Position & p1, const Position & p2) {
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return dx*dx + dy*dy;
}

///////////////////////////////////////////////////////////////////////////////
// Desk
///////////////////////////////////////////////////////////////////////////////

Desk::Desk(const Position & p) :
  pos(p),
  rng(std::random_device{}())
{
  reset();
}

const Position & Desk::getPos() const {
  return pos;
}

Desk::Status Desk::getStatus() const {
  return status;
}

void Desk::reset() {
  status = Status::Empty;
  time = 0;
}

void Desk::step(const double dt) {
  time += dt;
  if (time >= gBillTime) {
    if (status != Status::Empty) {
      status = Status::Empty;
    }
    else {
      std::uniform_real_distribution<double> dist(0, 1);
      double xi = dist(rng);
      if (xi < gRngCoef*time) {
        status = Status::Smile;
      }
    }
    time = 0;
  }
}

bool Desk::launchPie(const Position & p) {
  int d2 = distance2(pos, p);
  if (status == Status::Smile and d2 < gBillDist) {
    status = Status::Pie;
    time = 0;
    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
// Game
///////////////////////////////////////////////////////////////////////////////

Game::Game():
  status(Status::Ready),
  score(0),
  playRemTime(gPlayTime),
  pauseRemTime(gPauseTime),
  piePos(0, 0)
{

  // 1st row
  desks.push_back(Desk({300, 100}));
  desks.push_back(Desk({500, 100}));
  desks.push_back(Desk({700, 100}));
  desks.push_back(Desk({900, 100}));

  // 2nd row
  desks.push_back(Desk({200,  400}));
  desks.push_back(Desk({400,  400}));
  desks.push_back(Desk({600,  400}));
  desks.push_back(Desk({800,  400}));
  desks.push_back(Desk({1000, 400}));

  // 3rd row
  desks.push_back(Desk({300, 700}));
  desks.push_back(Desk({500, 700}));
  desks.push_back(Desk({700, 700}));
  desks.push_back(Desk({900, 700}));
}

Game::Status Game::getStatus() const {
  return status;
}

int Game::getScore() const {
  return score;
}

double Game::getPlayRemTime() const {
  return playRemTime;
}

const Position & Game::getPiePos() const {
  return piePos;
}

const std::vector<Desk> & Game::getDesks() const {
  return desks;
}

void Game::step(const double dt) {
  if (status == Status::Play) {
    playRemTime -= dt;
    for (auto & d : desks) 
      d.step(dt);
    if (playRemTime <= 0) {
      status = Status::Pause;
      pauseRemTime = gPauseTime;
    }
  }
  else if (status == Status::Pause) {
    pauseRemTime -= dt;
    if (pauseRemTime <= 0) {
      status = Status::Ready;
    }
  }
}

void Game::launchPie() {
  if (status == Status::Play) {
    for (auto & d : desks) {
      bool hasPie = d.launchPie(piePos);
      if (hasPie)
        score++;
    }
  }
  else if (status == Status::Ready) {
    for (auto & d : desks) 
      d.reset();
    score = 0;
    playRemTime = gPlayTime;
    status = Status::Play;
  }
}

void Game::movePie(const Position & p) {
  piePos = p;
}

