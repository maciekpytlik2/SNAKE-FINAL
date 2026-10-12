#if defined(SNAKE_USE_STD_MODULES)
import std;
#else
#include <algorithm>
#include <fstream>
#include <ranges>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>
#endif

#include "ScoreManager.h"

namespace {
const std::regex kPlayerNamePattern{R"(^[A-Za-z0-9_-]{1,20}$)"};
const std::regex kScoreLinePattern{R"(^([A-Za-z0-9_-]{1,20})\s+(\d+)$)"};

bool isValidPlayerName(const std::string& name) {
    return std::regex_match(name, kPlayerNamePattern);
}

bool parseScoreLine(const std::string& line, ScoreEntry& entry) {
    std::smatch match;
    if (!std::regex_match(line, match, kScoreLinePattern)) {
        return false;
    }

    entry.name = match[1].str();
    entry.score = std::stoi(match[2].str());
    return true;
}
}

ScoreManager::ScoreManager(std::filesystem::path scoreFile) : scoreFile(std::move(scoreFile)) {}

void ScoreManager::saveScore(const std::string& name, int score) const {
    if (!isValidPlayerName(name)) {
        throw std::runtime_error("Nazwa gracza moze zawierac tylko litery, cyfry, _ i -.");
    }

    std::ofstream file(scoreFile, std::ios::app);
    if (!file) {
        throw std::runtime_error("Nie mozna otworzyc pliku wynikow do zapisu.");
    }

    file << name << ' ' << score << '\n';
}

std::vector<ScoreEntry> ScoreManager::loadScores() const {
    std::vector<ScoreEntry> scores;

    if (!std::filesystem::exists(scoreFile)) {
        return scores;
    }

    std::ifstream file(scoreFile);
    if (!file) {
        throw std::runtime_error("Nie mozna otworzyc pliku wynikow do odczytu.");
    }

    std::string line;
    ScoreEntry entry;
    while (std::getline(file, line)) {
        if (parseScoreLine(line, entry)) {
            scores.push_back(entry);
        }
    }

    std::ranges::sort(scores, [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    return scores;
}

int ScoreManager::getBestScore() const {
    auto scores = loadScores();
    if (scores.empty()) {
        return 0;
    }

    return scores.front().score;
}
