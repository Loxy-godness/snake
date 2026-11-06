#include <windows.h>

#include "Game.h"
#include "Render.h"

#include <conio.h>
#include <iostream>

Game::Game() : rng_(std::random_device{}()) {
    food_ = spawnFood();
}

void Game::run() {
    while (state_ != Gamestate::Exit) {
        if (state_ == Gamestate::Running)
            updateRunning();
        else if (state_ == Gamestate::Gameover)
            updateGameover();
    }
    std::cout << "哼~,杂鱼~";
}

bool Game::handleInput(){
    while (_kbhit() ) {
        int ch = _getch() ;

        if (ch == 0 || ch == 224){
            int code = _getch();

            switch (code) {
                case 72:
                    snake_.pushDirection(Direction::UP);
                    break;
                case 80:
                    snake_.pushDirection(Direction::DOWN);
                    break;
                case 75:
                    snake_.pushDirection(Direction::LEFT);
                    break;
                case 77:
                    snake_.pushDirection(Direction::RIGHT);
                    break;
            }
            continue;
        }

        switch (ch) {
            case 'w': case 'W':
                snake_.pushDirection(Direction::UP);
                break;
            case 's': case 'S':
                snake_.pushDirection(Direction::DOWN);
                break;
            case 'a': case 'A':
                snake_.pushDirection(Direction::LEFT);
                break;
            case 'd': case 'D':
                snake_.pushDirection(Direction::RIGHT);
                break;
            case 'q': case 'Q':
                return false;
        }
    }
            return true;
}

Point Game::spawnFood() {
    std::uniform_int_distribution<int> distX(1, W - 2);
    std::uniform_int_distribution<int> distY(1, H - 2);

    while (true) {
        Point p{distX(rng_),distY(rng_)};
        if (!snake_.occupied(p)) {
            return p;
        }
    }
}


void Game::updateRunning() {
            if (!handleInput()) {
                state_ = Gamestate::Exit;
                return;
            }

            Point next = snake_.next_head();
            if (isOutside(next)) {
                state_ = Gamestate::Gameover;
                renderGameover(score_);
                return;
            }

            bool eated = (is_point_equal(food_, next));

            snake_.move(eated);

            if (snake_.selfCollision()) {
                state_ = Gamestate::Gameover;
                renderGameover(score_);
                return;
            }

            if (eated) {
                ++score_;
                food_ = spawnFood();
            }

            render(snake_, food_, score_);
            Sleep(100);
        }

void Game::updateGameover() {
            if (_kbhit()) {
                int ch = _getch();

                if (ch == 'r' || ch == 'R') {
                    snake_.reset();
                    food_ = spawnFood();
                    score_ = 0;
                    state_ = Gamestate::Running;
                }
                    else if (ch == 'q' || ch == 'Q') {
                        state_ = Gamestate::Exit;
                    }
                }
                Sleep(50);
        }