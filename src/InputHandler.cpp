#include "InputHandler.h"
#include "Snake.h"
#include "Game.h"

void InputHandler::handleEvent(const sf::Event& event, Game& game, Snake& snake) const {
    const auto* keyPressed = event.getIf<sf::Event::KeyPressed>();
    if (keyPressed == nullptr) {
        return;
    }

    switch (keyPressed->code) {
        case sf::Keyboard::Key::Escape:
            game.requestExit();
            break;
        case sf::Keyboard::Key::Enter:
            game.handleEnterKey();
            break;
        case sf::Keyboard::Key::Num1:
        case sf::Keyboard::Key::Numpad1:
            game.startNewGame(false);
            break;
        case sf::Keyboard::Key::Num2:
        case sf::Keyboard::Key::Numpad2:
            game.startNewGame(true);
            break;
        case sf::Keyboard::Key::Up:
        case sf::Keyboard::Key::W:
            snake.setDirection(Direction::Up);
            break;
        case sf::Keyboard::Key::Down:
        case sf::Keyboard::Key::S:
            snake.setDirection(Direction::Down);
            break;
        case sf::Keyboard::Key::Left:
        case sf::Keyboard::Key::A:
            snake.setDirection(Direction::Left);
            break;
        case sf::Keyboard::Key::Right:
        case sf::Keyboard::Key::D:
            snake.setDirection(Direction::Right);
            break;
        default:
            break;
    }
}
