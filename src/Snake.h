#pragma once

#include <deque>
#include "Config.h"

using namespace std;

class Snake {
public:
    Snake();

    void reset();
    void pushDirection(Direction dir);

    Point next_head() const;
    void move(bool growed);

    bool selfCollision() const;
    bool occupied(Point p) const;

    const std::deque<Point>& body() const;

private:
    std::deque<Point> body_;
    Direction dir_ = Direction::RIGHT;
    std::deque<Direction> pending_;
};