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

