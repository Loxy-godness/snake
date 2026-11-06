#pragma once

#include "Config.h"

class Snake;

void clearScreen();
void render(const Snake& snake, Point food, int score);
void renderGameover(int score);