#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int W = 20;
const int H = 20;

struct Point {
    int x = 0;
    int y = 0;
};

int main() {
    vector<string> board(H,string(W,' '));

    for (int x = 0 ; x < W ; x++ ) {
        board[0][x] = '#';
        board[H - 1][x] = '#';
    }
    for (int y = 0; y < H ; y++ ) {
        board[y][0] = '#';
        board[y][W - 1] = '#';
    }

    vector<Point> snake = {
        {W / 2 , H / 2 },
        {W / 2 - 1 , H / 2 },
        {W / 2 - 2, H / 2},
    };
    for (const auto& p : snake) {
        board[p.y][p.x] = '0';
    }

    Point food = {5 , 5};
    board[food.y][food.x] = '*';

    for (int y = 0; y < H ; ++y ) {
        cout << board[y] << '\n';
    }

    return 0;
}