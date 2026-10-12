#include "BonusFood.h"
#include "Snake.h"
#include "Game.h"

BonusFood::BonusFood(Position position) : GameObject(position) {}

void BonusFood::applyEffect(Snake& snake, Game& game) {
    snake.grow();
    snake.grow();
    game.addScore(30);
    game.decreaseStepTime(0.005f);
    game.spawnFood();
}

sf::Color BonusFood::getColor() const {
    return sf::Color(245, 205, 45);
}

char BonusFood::getSymbol() const {
    return 'B';
}
