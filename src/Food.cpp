#include "Food.h"
#include "Snake.h"
#include "Game.h"

Food::Food(Position position) : GameObject(position) {}

void Food::applyEffect(Snake& snake, Game& game) {
    snake.grow();
    game.addScore(10);
    game.spawnFood();
}

sf::Color Food::getColor() const {
    return sf::Color(220, 50, 50);
}

char Food::getSymbol() const {
    return 'F';
}
