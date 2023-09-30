#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;

namespace {
    static const double EPS = 1e-8;

    bool equal(double a, double b) {
        return abs(a - b) < EPS;
    }
}

class Point {
public:
    Point() {}
    Point(double xx, double yy) : x(xx), y(yy) {}

    double distance(const Point& p) const;

    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
    bool operator<(const Point& p) const;
    bool operator<=(const Point& p) const;

public:
    double x{ 0.0 };
    double y{ 0.0 };
};


double Point::distance(const Point& p) const {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

bool Point::operator==(const Point& p) const {
    return equal(x, p.x) && equal(y, p.y);
}

bool Point::operator!=(const Point& p) const {
    return !equal(x, p.x) || !equal(y, p.y);
}

bool Point::operator<(const Point& p) const {
    return (x < p.x) || (equal(x, p.x) && y < p.y);
}

bool Point::operator<=(const Point& p) const {
    return (x < p.x) || (equal(x, p.x) && ((y < p.y) || equal(y, p.y)));
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

bool compare_x(Point& a, Point& b) {
    return a.x < b.x;
}

bool compare_y(Point& a, Point& b) {
    return a.y < b.y;
}

template <typename S> void print_vp(const S& s) {// print vector of points

    for (const auto& p : s) {
        cout << p.x << " " << p.y << endl;
    }

    cout << "size=" << s.size();
    cout << endl;
}