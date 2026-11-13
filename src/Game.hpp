#pragma once

#include <random>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// global parameters
///////////////////////////////////////////////////////////////////////////////

const double gBillTime = 1;
const double gPlayTime = 30;
const double gPauseTime = 1;
const double gRngCoef = 0.15;
const int gBillDist = 2500;

///////////////////////////////////////////////////////////////////////////////
// Position
///////////////////////////////////////////////////////////////////////////////

struct Position {
  int x;
  int y;
};

///////////////////////////////////////////////////////////////////////////////
// Desk
///////////////////////////////////////////////////////////////////////////////

class Desk {
  public:
    enum class Status {
      Empty,
      Smile,
      Pie
    };

  private:

    Position pos;
    Status status;
    double time;
    std::default_random_engine rng;

  public:
    Desk(const Position & p);

    const Position & getPos() const;
    Status getStatus() const;

    void step(const double dt);
    bool launchPie(const Position & p);
    void reset();
};

///////////////////////////////////////////////////////////////////////////////
// Game
///////////////////////////////////////////////////////////////////////////////

class Game {
  public:
    enum class Status {
      Play,
      Pause,
      Ready
    };

  private:
    std::vector<Desk> desks;
    Status status;
    int score;
    double playRemTime;
    double pauseRemTime;
    Position piePos;

  public:
    Game();

    const std::vector<Desk> & getDesks() const;
    Status getStatus() const;
    int getScore() const;
    double getPlayRemTime() const;
    const Position & getPiePos() const;

    void step(const double dt);
    void launchPie();
    void movePie(const Position & p);
};

