#pragma once

#include "Game.hpp"

#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <random>

///////////////////////////////////////////////////////////////////////////////
// Player
///////////////////////////////////////////////////////////////////////////////

class Player {
  public:
    virtual ~Player() = default;
    virtual void externalMove(const int move);
    virtual bool canPlay() const;
    virtual int genMove(const Game & game) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// PlayerHuman
///////////////////////////////////////////////////////////////////////////////

class PlayerHuman : public Player {
  private:
    std::optional<int> _moveOpt;

  public:
    void externalMove(const int move) override;
    bool canPlay() const override;
    int genMove(const Game & game) override;
};

///////////////////////////////////////////////////////////////////////////////
// PlayerRandom
///////////////////////////////////////////////////////////////////////////////

class PlayerRandom : public Player {
  private:
    std::default_random_engine _engine;

  public:
    PlayerRandom();
    int genMove(const Game & game) override;
};

///////////////////////////////////////////////////////////////////////////////
// PlayerMc
///////////////////////////////////////////////////////////////////////////////

class PlayerMc : public Player {
  private:
    int _nbSimsPerMove;
    PlayerRandom _randomPlayer;

  public:
    PlayerMc(const int nbSimsPerMove);
    int genMove(const Game & game) override;
};

///////////////////////////////////////////////////////////////////////////////
// player factory
///////////////////////////////////////////////////////////////////////////////

static std::map<std::string, std::function<std::unique_ptr<Player>()>> gPlayerFactory {
  {"human", [](){ return std::make_unique<PlayerHuman>(); }},
  {"random", [](){ return std::make_unique<PlayerRandom>(); }},
  {"mc100", [](){ return std::make_unique<PlayerMc>(100); }},
  {"mc1k", [](){ return std::make_unique<PlayerMc>(1000); }},
  {"mc10k", [](){ return std::make_unique<PlayerMc>(1000); }}
};

