
#include "Render.h"
#include "Snake.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

void clearScreen() {
    system("cls");
}
void render(const Snake& snake, Point food, int score) {
    clearScreen();
    std::vector<string> board(H,string(W,' '));

    for (int x = 0 ; x < W ; x++ ) {
        board[0][x] = '#';
        board[H - 1][x] = '#';
    }
    for (int y = 0; y < H ; y++ ) {
        board[y][0] = '#';
        board[y][W - 1] = '#';
    }

    board[food.y][food.x] = '*';

    for ( const auto& p : snake.body() ) {
        if ( !isOutside(p) ) {
            board[p.y][p.x] = '0';
        }
    }

    for (int y = 0; y < H ; ++y ) {
        std::cout << board[y] << '\n';
    }

    std::cout << "Score: " << score << '\n';
    std::cout.flush();
}

void renderGameover(int score) {
    clearScreen();
    std::cout << "==================================\n";
    std::cout << "        哼~,杂鱼就是杂鱼~          \n";
    std::cout << "==================================\n";
    std::cout << "Score: " << score << "\n\n";
    std::cout << "按 R 再来一次哦~\n";
    std::cout << "杂鱼先生，要按 Q 退出吗，嘻嘻~\n";
    std::cout.flush();
}
