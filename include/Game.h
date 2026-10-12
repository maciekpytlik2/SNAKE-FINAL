#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "Board.h"
#include "Snake.h"
#include "ScoreManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "GameState.h"

class Game {
private:
    static constexpr int BoardWidth = 30;
    static constexpr int BoardHeight = 20;
    static constexpr int CellSize = 24;
    static constexpr int TopPanelHeight = 60;

    sf::RenderWindow window;
    Board board;
    Snake snake;
    ScoreManager scoreManager;
    Renderer renderer;
    InputHandler inputHandler;
    GameState state{GameState::Menu};

    std::mt19937 randomEngine;
    sf::Clock movementClock;

    int score{0};
    int bestScore{0};
    float stepTime{0.12f};
    bool obstacleMode{false};
    bool scoreSaved{false};

    Position randomFreePosition();
    void addObstacles();
    void updatePlaying();
    void processEvents();

public:
    Game();

    void run();
    void update();
    void render();

    void startNewGame(bool withObstacles);
    void spawnFood();
    void endGame();
    void requestExit();
    void handleEnterKey();

    void addScore(int value);
    void decreaseStepTime(float value);

    const Board& getBoard() const;
    const Snake& getSnake() const;
    GameState getState() const;
    int getScore() const;
    int getBestScore() const;
    bool isObstacleMode() const;
};
