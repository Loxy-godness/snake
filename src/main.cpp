#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <windows.h>

using namespace std;

const int W = 20;
const int H = 20;

struct Point {
    int x = 0;
    int y = 0;
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

bool isOutside(Point p) {
    return (p.x < 0 || p.x >= W || p.y < 0 || p.y >= H);
}

class Snake{
public:
    Snake(){ reset(); }

    void reset() {
        body_.clear();
        body_.push_back({W / 2, H / 2});
        body_.push_back({W / 2 - 1, H / 2});
        body_.push_back({W / 2 - 2, H / 2});
        dir_ = Direction::RIGHT;
    }

    void move() {
        Point head = body_.front();
        switch (dir_) {
            case Direction::UP:
                head.y--;
                break;
            case Direction::DOWN:
                head.y++;
                break;
            case Direction::LEFT:
                head.x--;
                break;
            case Direction::RIGHT:
                head.x++;
                break;
        }
        body_.push_front(head);
        body_.pop_back();
    }

    const deque<Point>& body() const {
        return body_;
    }

private:
    deque<Point> body_;
    Direction dir_ = Direction::RIGHT;
};

void clearScreen() {
    system("cls");
}

void render(const Snake& snake) {
    vector<string> board(H,string(W,' '));

    for (int x = 0 ; x < W ; x++ ) {
        board[0][x] = '#';
        board[H - 1][x] = '#';
    }
    for (int y = 0; y < H ; y++ ) {
        board[y][0] = '#';
        board[y][W - 1] = '#';
    }

    Point food = {5 , 5};
    board[food.y][food.x] = '*';

    for ( const auto& p : snake.body() ) {
        if ( !isOutside(p) ) {
            board[p.y][p.x] = '0';
        }
    }

    for (int y = 0; y < H ; ++y ) {
        cout << board[y] << '\n';
    }

    cout.flush();
}

int main() {
    Snake snake;

    while (true) {
        snake.move();

        if ( isOutside(snake.body().front() ) ) {
            cout << "Snake out of board. Day 5 will add collision.\n";
            clearScreen();
            break;
        }

        clearScreen();
        render(snake);
        Sleep(300);
    }

    return 0;
}