#pragma once

const int W = 20;
const int H = 20;

struct Point {
    int x = 0;
    int y = 0;
};

inline bool is_point_equal(Point a,Point b) {
    return (a.x == b.x && a.y == b.y);
}

enum class Gamestate {
    Running,
    Gameover,
    Exit
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

inline bool isOutside(Point p) {
    return (p.x < 0 || p.x >= W || p.y < 0 || p.y >= H);
}

inline bool isOpposite(Direction a, Direction b) {
    return      (a == Direction::UP && b == Direction::DOWN) ||
                (a == Direction::DOWN && b == Direction::UP) ||
                (a == Direction::RIGHT && b == Direction::LEFT) ||
                (a == Direction::LEFT && b == Direction::RIGHT);
}
