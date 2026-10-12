#include "Obstacle.h"
#include "Game.h"
#include "Snake.h"

Obstacle::Obstacle(Position position) : GameObject(position) {}

void Obstacle::applyEffect(Snake&, Game& game) {
    game.endGame();
}

sf::Color Obstacle::getColor() const {
    return sf::Color(100, 100, 110);
}

char Obstacle::getSymbol() const {
    return 'O';
}
