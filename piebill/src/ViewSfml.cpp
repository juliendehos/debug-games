
#include "ViewSfml.hpp"

View::View(const std::string & dataDir) :
  pieTexture(dataDir + "pie.png"),
  pieSprite(pieTexture),
  deskTexture(dataDir + "desk.png"),
  deskSprite(deskTexture),
  billSmileTexture(dataDir + "bill-smile.png"),
  billSmileSprite(billSmileTexture),
  billPieTexture(dataDir + "bill-pie.png"),
  billPieSprite(billPieTexture),
  textFont(dataDir + "arial.ttf"),
  scoreText(textFont, "", 50),
  timeText(textFont, "", 50),
  welcomeText(textFont, "Click to start", 50)
{
  scoreText.setFillColor(gTextColor);
  scoreText.setPosition({20, 10});
  timeText.setFillColor(gTextColor);
  timeText.setPosition({gWinSizeF.x - 220, 10});
  welcomeText.setFillColor(gTextColor);
  welcomeText.setPosition({450, 400});
}

void View::draw(sf::RenderWindow & window, const Game & game) {

  // set pie position
  const Position & piePos = game.getPiePos();
  sf::Vector2f pieVec { float(piePos.x), float(piePos.y) };
  pieSprite.setPosition(pieVec + gDeltaPie);

  // draw welcome message or desks
  const auto gameStatus = game.getStatus();
  if (gameStatus == Game::Status::Pause) {
    window.draw(pieSprite);
  }

  else if (gameStatus == Game::Status::Ready) {
    window.draw(pieSprite);
    window.draw(welcomeText);
  }

  else {  // play
    for (const Desk & d : game.getDesks()) {
      Position deskPos = d.getPos();
      sf::Vector2f deskVec { float(deskPos.x), float(deskPos.y) };
      Desk::Status status = d.getStatus();

      // desk
      deskSprite.setPosition(deskVec + gDeltaDesk);
      window.draw(deskSprite);

      // bill
      if (status == Desk::Status::Smile) {
        billSmileSprite.setPosition(deskVec + gDeltaBill);
        window.draw(billSmileSprite);
      }
      else if (status == Desk::Status::Pie) {
        billPieSprite.setPosition(deskVec + gDeltaBill);
        window.draw(billPieSprite);
      }
    }

    window.draw(pieSprite);
  }

  // draw score
  scoreText.setString("Score: " + std::to_string(game.getScore()));
  window.draw(scoreText);

  // draw remaining time
  timeText.setString("Time: " + std::to_string(int(game.getPlayRemTime())));
  window.draw(timeText);

}

