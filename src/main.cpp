#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <_mingw_mac.h>

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

bool isOpposite(Direction a, Direction b) {
    return      (a == Direction::UP && b == Direction::DOWN) ||
                (a == Direction::DOWN && b == Direction::UP) ||
                (a == Direction::RIGHT && b == Direction::LEFT) ||
                (a == Direction::LEFT && b == Direction::RIGHT);
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
        pending_.clear();
    }

    void pushDirection(Direction dir) {
        Direction last = pending_.empty() ? dir_ : pending_.back();
        if (last == dir || isOpposite(last, dir))
            return;
        pending_.push_back(dir);
    }

    void move() {
        if (!pending_.empty()) {
            dir_ = pending_.front();
            pending_.pop_front();
        }

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
    deque<Direction> pending_;
};

void clearScreen() {
    system("cls");
}

void render(const Snake& snake) {
    clearScreen();
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

void handleInput(Snake& snake) {
    while (_kbhit() ) {
        int ch = _getch() ;

        if (ch == 0 || ch == 224){
            int code = _getch();
            switch (code) {
                case 72:
                    snake.pushDirection(Direction::UP);
                    break;
                case 80:
                    snake.pushDirection(Direction::DOWN);
                    break;
                case 75:
                    snake.pushDirection(Direction::LEFT);
                    break;
                case 77:
                    snake.pushDirection(Direction::RIGHT);
                    break;
            }
            continue;
    }

        switch (ch) {
            case 'w': case 'W':
                snake.pushDirection(Direction::UP);
                break;
            case 's': case 'S':
                snake.pushDirection(Direction::DOWN);
                break;
            case 'a': case 'A':
                snake.pushDirection(Direction::LEFT);
                break;
            case 'd': case 'D':
                snake.pushDirection(Direction::RIGHT);
                break;
            case 'q': case 'Q':
                exit(0);
        }

    }
}

int main() {
    Snake snake;

    while (true) {
        handleInput(snake);
        snake.move();

        if ( isOutside(snake.body().front() ) ) {
            cout << "Snake out of board. Day 5 will add collision.\n";
            clearScreen();
            break;
        }

        render(snake);
        Sleep(300);
    }

    return 0;
}