#pragma once

#include <filesystem>
#include <vector>
#include <string>

struct ScoreEntry {
    std::string name;
    int score{};
};

class ScoreManager {
private:
    std::filesystem::path scoreFile;

public:
    explicit ScoreManager(std::filesystem::path scoreFile = "scores.txt");

    void saveScore(const std::string& name, int score) const;
    std::vector<ScoreEntry> loadScores() const;
    int getBestScore() const;
};
