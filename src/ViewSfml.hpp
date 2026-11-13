#pragma once

#include "Game.hpp"

#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////////////////
// global parameters
///////////////////////////////////////////////////////////////////////////////

const std::string gAppName = "piebill-sfml";
const sf::Vector2u gWinSize {1200, 900};
const sf::Vector2f gWinSizeF(gWinSize);
const sf::Color gBgColor(100, 180, 250, 255);
const sf::Color gTextColor(200, 0, 0, 255);
const sf::Vector2f gDeltaPie {-50, -37};
const sf::Vector2f gDeltaDesk {-100, 75};
const sf::Vector2f gDeltaBill {-100, -75};

///////////////////////////////////////////////////////////////////////////////
// view
///////////////////////////////////////////////////////////////////////////////

class View {

  private:

    sf::Texture pieTexture;
    sf::Sprite pieSprite;

    sf::Texture deskTexture;
    sf::Sprite deskSprite;

    sf::Texture billSmileTexture;
    sf::Sprite billSmileSprite;

    sf::Texture billPieTexture;
    sf::Sprite billPieSprite;

    sf::Font textFont;
    sf::Text scoreText;
    sf::Text timeText;
    sf::Text welcomeText;

  public:
    explicit View(const std::string & dataDir);
    View(const View & v) = delete;

    void draw(sf::RenderWindow & window, const Game & game);

};

