#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.h"
#include "GameState.h"

class Snake;
class Game;

class InputHandler {
public:
    void handleEvent(const sf::Event& event, Game& game, Snake& snake) const;
};
