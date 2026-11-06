
#include "Snake.h"

Snake::Snake() {
        reset();
    }

void Snake::reset() {
        body_.clear();
        body_.push_back({W / 2, H / 2});
        body_.push_back({W / 2 - 1, H / 2});
        body_.push_back({W / 2 - 2, H / 2});
        dir_ = Direction::RIGHT;
        pending_.clear();
    }

void Snake::pushDirection(Direction dir) {
        Direction last = pending_.empty() ? dir_ : pending_.back();
        if (last == dir || isOpposite(last, dir))
            return;
        pending_.push_back(dir);
    }

    Point Snake::next_head() const {
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

void Snake::move(bool growed) {
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

bool Snake::selfCollision() const{
        if (body_.size() <= 1)
            return false;
        const Point& head = body_.front();
        for (size_t i = 1; i < body_.size() ; ++i) {
            if (is_point_equal(body_[i],head))
                return true;
        }
        return false;
    }

bool Snake::occupied(Point p) const{
        for (const auto& s : body_) {
            if ( is_point_equal(p, s) )
                return true;
        }
        return false;
    }

const deque<Point>& Snake::body() const {
        return body_;
    }
