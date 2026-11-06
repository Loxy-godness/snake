#include <windows.h>
#include "Game.h"


int main() {
    SetConsoleOutputCP(65001);
    Game game;
    game.run();
    return 0;
}