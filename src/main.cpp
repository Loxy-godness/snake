#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <_mingw_mac.h>
#include <random>

using namespace std;

const int W = 20;
const int H = 20;

struct Point {
    int x = 0;
    int y = 0;
};

bool is_point_equal(Point a,Point b) {
    return (a.x == b.x && a.y == b.y);
}

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

    Point next_head() const {
        Direction dir = pending_.empty() ? dir_ : pending_.front();
        Point head = body_.front();
        switch (dir) {
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
        return head;
    }

    void move(bool growed) {
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
        if (!growed)
            body_.pop_back();
    }

    bool occupied(Point p) const{
        for (const auto& s : body_) {
            if ( is_point_equal(p, s) )
                return true;
        }
        return false;
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

Point spawnFood(const Snake& snake, mt19937& rng) {
    uniform_int_distribution<int> distX(1, W - 2);
    uniform_int_distribution<int> distY(1, H - 2);

    while (true) {
        Point p{distX(rng) , distY(rng)};
        if (!snake.occupied(p)) {
            return p;
        }
    }
}

void render(const Snake& snake, Point food, int score) {
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

    board[food.y][food.x] = '*';

    for ( const auto& p : snake.body() ) {
        if ( !isOutside(p) ) {
            board[p.y][p.x] = '0';
        }
    }

    for (int y = 0; y < H ; ++y ) {
        cout << board[y] << '\n';
    }

    cout << "Score: " << score << '\n';
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
    random_device rd;
    mt19937 rng(rd());

    Snake snake;
    Point food = spawnFood(snake, rng);
    int score = 0;

    while (true) {
        handleInput(snake);

        Point next = snake.next_head();

        bool eated = (is_point_equal(food, next));

        snake.move(eated);

        if (eated) {
            ++score;
            food = spawnFood(snake, rng);
        }

        if ( isOutside(snake.body().front() ) ) {
            cout << "Snake out of board. Day 5 will add collision.\n";
            break;
        }

        render(snake, food, score);
        Sleep(200);
    }

    return 0;
}