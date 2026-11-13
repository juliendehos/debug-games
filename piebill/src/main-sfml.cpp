
#include "ViewSfml.hpp"

int main(int, char ** argv) {

  // SFML
  sf::RenderWindow window(sf::VideoMode(gWinSize), gAppName, sf::Style::Close);
  window.setFramerateLimit(60);
  window.setPosition({50, 50});

  // assets
  const std::string dataDir = 
    (std::filesystem::path(argv[0]).parent_path() / "../data/").string();

  // view
  View view(dataDir);

  // game
  Game game;
  const sf::Vector2f winSize05 = gWinSizeF*0.5f;
  game.movePie({int(winSize05.x), int(winSize05.y)});

  // clock
  sf::Clock clock;

  // main loop
  while (window.isOpen()) {

    // handle events
    while (const std::optional event = window.pollEvent()) {
      // window closed
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // keyboard
      else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        auto code = keyPressed->scancode;
        if (code == sf::Keyboard::Scancode::Escape or code == sf::Keyboard::Scancode::Q)
          window.close();
      }
      // mouse motion
      else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
        const sf::Vector2i p = mouseMoved->position;
        game.movePie({p.x, p.y});
      }
      // mouse button
      else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
          const sf::Vector2i p = mouseButtonPressed->position;
          game.movePie({p.x, p.y});
          game.launchPie();
        }
      }

    }

    // update game
    sf::Time elapsed = clock.restart();
    double dt = elapsed.asSeconds();
    game.step(dt);

    // refresh display
    window.clear(gBgColor);
    view.draw(window, game);
    window.display();
  }

  return 0;
}

