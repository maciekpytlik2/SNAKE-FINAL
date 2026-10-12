#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Snake.h"
#include "GameState.h"

class Game;

class Renderer {
private:
    int cellSize;
    sf::Font font;
    bool fontLoaded{false};

    void drawText(sf::RenderWindow& window, const std::string& text, unsigned int size, float x, float y) const;

public:
    explicit Renderer(int cellSize);

    void loadFont();
    void render(sf::RenderWindow& window, const Game& game) const;
    void renderMenu(sf::RenderWindow& window, const Game& game) const;
    void renderGame(sf::RenderWindow& window, const Game& game) const;
    void renderGameOver(sf::RenderWindow& window, const Game& game) const;
};
