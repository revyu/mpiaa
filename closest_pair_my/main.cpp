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

pair<Point, Point> closest_pair_between(vector <Point> pleft, vector <Point> pright, double d) {
    double Xm = (pleft[0].x + pright[pright.size() - 1].x) / 2;
    vector <Point> Pstripe = { Point(1000000,1000000),Point(-1000000,-1000000) };
    // приходится добавить фиктивные точки т.к иначе происходят ошибки если в pstripe не попадает ни одна точка
    for (int i = pleft.size()-1; i >= 0; i--) {
        if (abs(pleft[i].x - Xm) < d) { Pstripe.push_back(pleft[i]); }
        else { break; }
    }

    for (int i = pleft.size()-1; i >= 0; i--) {
        if (abs(pright[i].x - Xm) < d) { Pstripe.push_back(pright[i]); }
        else { break; }
    }

    sort(Pstripe.begin(), Pstripe.end(), compare_y);

    int min_i=0;
    int min_j=1;
    double min_distance = 2 * d;
    for (int i = 0; i < Pstripe.size() - 1; i++) {
        for (int j = i + 1; j < Pstripe.size(); j++) {
            if (abs(Pstripe[i].y - Pstripe[j].y) > d) { break; }
            else {
                if (Pstripe[i].distance(Pstripe[j]) < min_distance) {
                    min_i = i;
                    min_j = j;
                    min_distance = Pstripe[i].distance(Pstripe[j]);
                }
            }
        }
    }

    return make_pair(Pstripe[min_i], Pstripe[min_j]);
}

std::pair<Point, Point> closest_pair_divide_and_rule(std::vector<Point>& points) {
    // Return the closest pair of points from given points.
    // Order of points in the result doesn't matter.
    // If there are fewer than 2 points, throw an exception.

    if (points.size() < 2) {
        throw invalid_argument("Not enough points");
    }

    if (points.size() == 2) {
        return make_pair(points[0], points[1]);
    }

    if (points.size() == 3) {
        double a = points[0].distance(points[1]);
        double b = points[0].distance(points[2]);
        double c = points[1].distance(points[2]);

        vector <double> distances = { a,b,c };
        vector<double>::iterator min_elem = min_element(distances.begin(), distances.end());
        if (*min_elem == a) { return make_pair(points[0], points[1]); }
        if (*min_elem == b) { return make_pair(points[0], points[2]); }
        else { return make_pair(points[1], points[2]); }
    }

    sort(points.begin(), points.end(), compare_x);

    vector <Point> pleft;
    vector <Point> pright;
    for (int i = 0; i < points.size(); i++) {
        if (i < points.size() / 2) { pleft.push_back(points[i]); }
        else { pright.push_back(points[i]); }
    }
    pair<Point, Point> pl = closest_pair_divide_and_rule(pleft);
    pair<Point, Point> pr = closest_pair_divide_and_rule(pright);

    double pl_dist = pl.first.distance(pl.second);
    double pr_dist = pr.first.distance(pr.second);

    double d = min(pl_dist, pr_dist);

    pair<Point, Point> pb = closest_pair_between(pleft, pright, d);

    double pb_dist = pb.first.distance(pb.second);

    vector <double> distances = { pl_dist,pr_dist,pb_dist };

    vector<double>::iterator min_elem = min_element(distances.begin(), distances.end());
    if (*min_elem == pl_dist) { return pl; }
    if (*min_elem == pr_dist) { return pr; }
    else { return pb; }


}


int main() {
    vector<Point> points = { Point(3,1),Point(1,1),Point(2,2),Point(4,4) };
    pair <Point, Point> best = closest_pair_divide_and_rule(points);
    cout << best.first << " " << best.second;


}




