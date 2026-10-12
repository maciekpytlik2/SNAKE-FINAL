#include "Renderer.h"
#include "Game.h"
#include <sstream>
#include <vector>

Renderer::Renderer(int cellSize) : cellSize(cellSize) {}

void Renderer::loadFont() {
    const std::vector<std::string> possibleFonts = {
        "assets/DejaVuSans.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/System/Library/Fonts/Supplemental/Verdana.ttf",
        "/Library/Fonts/Arial.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    for (const auto& path : possibleFonts) {
        if (font.openFromFile(path)) {
            fontLoaded = true;
            return;
        }
    }

    fontLoaded = false;
}

void Renderer::drawText(sf::RenderWindow& window, const std::string& text, unsigned int size, float x, float y) const {
    if (!fontLoaded) {
        return;
    }

    sf::Text drawableText(font, text, size);
    drawableText.setFillColor(sf::Color::White);
    drawableText.setPosition({x, y});
    window.draw(drawableText);
}

void Renderer::render(sf::RenderWindow& window, const Game& game) const {
    switch (game.getState()) {
        case GameState::Menu:
            renderMenu(window, game);
            break;
        case GameState::Playing:
            renderGame(window, game);
            break;
        case GameState::GameOver:
            renderGameOver(window, game);
            break;
        case GameState::Exit:
            break;
    }
}

void Renderer::renderMenu(sf::RenderWindow& window, const Game& game) const {
    window.clear(sf::Color(25, 25, 35));
    drawText(window, "SNAKE - projekt C++ / SFML", 32, 70.f, 70.f);
    drawText(window, "1 - Nowa gra klasyczna", 22, 90.f, 150.f);
    drawText(window, "2 - Nowa gra z przeszkodami", 22, 90.f, 190.f);
    drawText(window, "ESC - Wyjscie", 22, 90.f, 230.f);

    std::ostringstream oss;
    oss << "Najlepszy wynik: " << game.getBestScore();
    drawText(window, oss.str(), 20, 90.f, 300.f);
    drawText(window, "Sterowanie: strzalki lub WASD", 18, 90.f, 360.f);
}

void Renderer::renderGame(sf::RenderWindow& window, const Game& game) const {
    window.clear(sf::Color(20, 22, 28));

    const Board& board = game.getBoard();
    const Snake& snake = game.getSnake();
    const int topOffset = 60;

    sf::RectangleShape background(sf::Vector2f{static_cast<float>(board.getWidth() * cellSize), static_cast<float>(board.getHeight() * cellSize)});
    background.setPosition({0.f, static_cast<float>(topOffset)});
    background.setFillColor(sf::Color(35, 42, 47));
    window.draw(background);

    sf::RectangleShape gridCell(sf::Vector2f{static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1)});
    gridCell.setFillColor(sf::Color(42, 50, 55));

    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            gridCell.setPosition({static_cast<float>(x * cellSize), static_cast<float>(topOffset + y * cellSize)});
            window.draw(gridCell);
        }
    }

    sf::RectangleShape snakePart(sf::Vector2f{static_cast<float>(cellSize - 2), static_cast<float>(cellSize - 2)});
    bool head = true;
    for (const auto& segment : snake.getSegments()) {
        snakePart.setPosition({static_cast<float>(segment.x * cellSize + 1), static_cast<float>(topOffset + segment.y * cellSize + 1)});
        snakePart.setFillColor(head ? sf::Color(70, 230, 120) : sf::Color(40, 170, 90));
        window.draw(snakePart);
        head = false;
    }

    for (const auto& object : board.getObjects()) {
        sf::CircleShape item(static_cast<float>(cellSize) / 2.f - 2.f);
        item.setPosition({static_cast<float>(object->getPosition().x * cellSize + 2), static_cast<float>(topOffset + object->getPosition().y * cellSize + 2)});
        item.setFillColor(object->getColor());
        window.draw(item);
    }

    std::ostringstream info;
    info << "Wynik: " << game.getScore()
         << "    Najlepszy: " << game.getBestScore()
         << "    Tryb: " << (game.isObstacleMode() ? "z przeszkodami" : "klasyczny");
    drawText(window, info.str(), 18, 10.f, 18.f);
}

void Renderer::renderGameOver(sf::RenderWindow& window, const Game& game) const {
    window.clear(sf::Color(35, 25, 30));
    drawText(window, "KONIEC GRY", 34, 100.f, 80.f);

    std::ostringstream score;
    score << "Twoj wynik: " << game.getScore();
    drawText(window, score.str(), 24, 120.f, 160.f);

    drawText(window, "ENTER - powrot do menu", 22, 100.f, 240.f);
    drawText(window, "1 - zagraj ponownie klasycznie", 20, 100.f, 285.f);
    drawText(window, "2 - zagraj z przeszkodami", 20, 100.f, 325.f);
    drawText(window, "ESC - wyjscie", 20, 100.f, 365.f);
}
