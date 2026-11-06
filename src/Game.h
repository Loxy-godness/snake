#pragma once

#include <random>
#include "Config.h"
#include "Snake.h"

class Game {
public:
    Game();
    void run();

private:
    bool handleInput();
    void updateRunning();
    void updateGameover();
    Point spawnFood();

    Snake snake_;
    Point food_;
    int score_ = 0;
    Gamestate state_ = Gamestate::Running;
    std::mt19937 rng_;
};