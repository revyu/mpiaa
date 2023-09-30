#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "point.cpp"

using namespace std;

pair<Point,Point> closest_pair_brute(vector <Point> &points){
    double min_distance=1000000;
    int min_i=0;
    int min_j=1;
    if (points.size() < 2) {
        throw invalid_argument("Not enough points");
    }

    for(int i=0;i<points.size()-1;i++){
        for (int j=i+1;j<points.size();j++){
            if (min_distance>points[i].distance(points[j])){
                min_i=i;
                min_j=j;
                min_distance=points[i].distance(points[j]);
            }
        }
    }
    return make_pair(points[min_i],points[min_j]);

}



pair<Point, Point> closest_pair_between(vector<Point> pleft, vector<Point> pright, double d) {
    sort(pright.begin(), pright.end(), [](const Point& a, const Point& b) {
    return a.y < b.y;
});  // Сортируем PLeft и PRight по y-координате
    sort(pright.begin(), pright.end(), [](const Point& a, const Point& b) {
    return a.y < b.y;
});

    double Xm = (pleft.back().x + pright.front().x) / 2.0;  // Находим Xm 

    vector<Point> Pstripe={Point(INFINITY,INFINITY),Point(-INFINITY,-INFINITY)};

    for (const Point& p : pleft) {
        if (abs(p.x - Xm) < d) {
            Pstripe.push_back(p);
        }
    }

    for (const Point& p : pright) {
        if (abs(p.x - Xm) < d) {
            Pstripe.push_back(p);
        }
    }

    sort(Pstripe.begin(), Pstripe.end(), [](const Point& a, const Point& b) {
    return a.x < b.x;
});

    int min_i = 0;
    int min_j = 1;
    double min_distance = 2 * d;

    for (int i = 0; i < Pstripe.size(); i++) {
        for (int j = i + 1; j < Pstripe.size() && (Pstripe[j].y - Pstripe[i].y) < min_distance; j++) {
            double distance = Pstripe[i].distance(Pstripe[j]);
            if (distance < min_distance) {
                min_i = i;
                min_j = j;
                min_distance = distance;
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
        cout<<"ошибка";
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

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

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