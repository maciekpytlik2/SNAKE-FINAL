#include "Game.h"
#include "Food.h"
#include "BonusFood.h"
#include "Obstacle.h"
#include <chrono>
#include <memory>
#include <stdexcept>
#include <optional>

Game::Game()
    : window(sf::VideoMode({static_cast<unsigned int>(BoardWidth * CellSize), static_cast<unsigned int>(BoardHeight * CellSize + TopPanelHeight)}), "Snake SFML"),
      board(BoardWidth, BoardHeight),
      snake({BoardWidth / 2, BoardHeight / 2}),
      scoreManager("scores.txt"),
      renderer(CellSize),
      randomEngine(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())) {
    window.setFramerateLimit(60);
    renderer.loadFont();

    try {
        bestScore = scoreManager.getBestScore();
    } catch (...) {
        bestScore = 0;
    }
}

void Game::run() {
    while (window.isOpen() && state != GameState::Exit) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            requestExit();
            continue;
        }
        inputHandler.handleEvent(*event, *this, snake);
    }
}

void Game::update() {
    if (state == GameState::Playing) {
        updatePlaying();
    }
}

void Game::updatePlaying() {
    if (movementClock.getElapsedTime().asSeconds() < stepTime) {
        return;
    }

    movementClock.restart();
    snake.move();

    const Position head = snake.getHead();

    if (!board.isInside(head) || snake.collidesWithSelf()) {
        endGame();
        return;
    }

    if (GameObject* object = board.findObjectAt(head)) {
        object->applyEffect(snake, *this);
        board.removeObjectAt(head);
    }
}

void Game::render() {
    renderer.render(window, *this);
    window.display();
}

void Game::startNewGame(bool withObstacles) {
    obstacleMode = withObstacles;
    score = 0;
    stepTime = 0.12f;
    scoreSaved = false;
    board.clearObjects();
    snake.reset({BoardWidth / 2, BoardHeight / 2});

    if (obstacleMode) {
        addObstacles();
    }

    spawnFood();
    state = GameState::Playing;
    movementClock.restart();
}

void Game::spawnFood() {
    Position position = randomFreePosition();
    std::uniform_int_distribution<int> bonusChance(1, 5);

    if (bonusChance(randomEngine) == 1) {
        board.addObject(std::make_unique<BonusFood>(position));
    } else {
        board.addObject(std::make_unique<Food>(position));
    }
}

Position Game::randomFreePosition() {
    std::uniform_int_distribution<int> xDistribution(0, BoardWidth - 1);
    std::uniform_int_distribution<int> yDistribution(0, BoardHeight - 1);

    for (int attempt = 0; attempt < 1000; ++attempt) {
        Position candidate{xDistribution(randomEngine), yDistribution(randomEngine)};
        if (!snake.contains(candidate) && !board.isOccupied(candidate)) {
            return candidate;
        }
    }

    return {1, 1};
}

void Game::addObstacles() {
    for (int x = 5; x < BoardWidth - 5; x += 4) {
        board.addObject(std::make_unique<Obstacle>(Position{x, 5}));
        board.addObject(std::make_unique<Obstacle>(Position{x, BoardHeight - 6}));
    }
}

void Game::endGame() {
    state = GameState::GameOver;

    if (!scoreSaved) {
        try {
            scoreManager.saveScore("Player", score);
            bestScore = scoreManager.getBestScore();
        } catch (...) {
            if (score > bestScore) {
                bestScore = score;
            }
        }
        scoreSaved = true;
    }
}

void Game::requestExit() {
    state = GameState::Exit;
    window.close();
}

void Game::handleEnterKey() {
    if (state == GameState::GameOver) {
        state = GameState::Menu;
    }
}

void Game::addScore(int value) {
    score += value;
}

void Game::decreaseStepTime(float value) {
    stepTime -= value;
    if (stepTime < 0.06f) {
        stepTime = 0.06f;
    }
}

const Board& Game::getBoard() const {
    return board;
}

const Snake& Game::getSnake() const {
    return snake;
}

GameState Game::getState() const {
    return state;
}

int Game::getScore() const {
    return score;
}

int Game::getBestScore() const {
    return bestScore;
}

bool Game::isObstacleMode() const {
    return obstacleMode;
}
