#include "algo_brute.cpp"
#include <cassert>


/*
void test_empty_points() {
    std::vector<Point> points = {};
    try {
        closest_pair_divide_and_rule(points);
    } catch (invalid_argument) {// должно быть исключение т.е должны попасть сюда
}

void test_single_point() {
    const std::vector<Point> points = {Point(1, 1)};
    try {
        closest_pair(points);
        assrt(false && No excepton thrown for single point vector);
    } catch (...) {
        // Expected exception
    }
}
*/
std:: pair<Point,Point> sort_pair (std:: pair<Point,Point> my_pair ){
    if (my_pair.first.x<my_pair.second.x){
        return my_pair;
    }
    if (my_pair.first.x>my_pair.second.x){
        return make_pair(my_pair.second,my_pair.first);
    }
    else {if(my_pair.first.y>my_pair.second.y){return make_pair(my_pair.second,my_pair.first);}
            else{return my_pair;}}
}

void test_two_points() {
    std::vector<Point> points = {Point(2, 3), Point(3, 4)};
    auto result = sort_pair(closest_pair_brute(points));
    assert(result == make_pair(Point(2, 3), Point(3, 4)));
}

void test_three_points() {
    std::vector<Point> points = {Point(2, 3), Point(1, 9), Point(6, 2)};
    auto result = sort_pair(closest_pair_brute(points));
    assert(result == make_pair(Point(2, 3), Point(6, 2)));
}

void test_duplicate_points() {
    std::vector<Point> points = {Point(2, 3), Point(2, 3), Point(3, 4)};
    auto result = sort_pair(closest_pair_brute(points));
    assert(result == make_pair(Point(2, 3), Point(2, 3)));
}

void test_same_x_coordinate() {
    std::vector<Point> points = {
        Point(2, 9), Point(2, 4), 
        Point(2, 1), Point(2, -8)};
    auto result = sort_pair(closest_pair_brute(points));
    assert(result== make_pair(Point(2, 1), Point(2, 4)));
}

void test_many_points() {
    std::vector<Point> points = {
        Point(2, 3), Point(0, 4), Point(11, 9), Point(2, 8),
        Point(4, 4), Point(3, 6), Point(6, 5), Point(1, 9)};
    auto result = sort_pair(closest_pair_brute(points));
    assert(result == make_pair(Point(1, 9), Point(2, 8)));
}

void test_negative_points() {
    std::vector<Point> points = {
        Point(-5, 6), Point(1, 2), Point(4, -2), Point(-9, 0),
        Point(-1, -2), Point(0, 7), Point(2, -1), Point(-3, 1)};
    auto result = sort_pair(closest_pair_brute(points));;
    assert(result == make_pair(Point(2, -1), Point(4, -2)));
}

void test_closest_points_from_stripe() {
    std::vector<Point> points = {
        Point(-1, 20), Point(-1.5, 10), Point(-2, -10), Point(-2.7, -20),
        Point(-10, 20), Point(-10.5, 10), Point(-11.7, -10), Point(-12.2, -20),
        Point(1, 21), Point(1.5, 11), Point(2, -9), Point(2.7, -19),
        Point(10, 21), Point(10.5, 11), Point(11.7, -9), Point(12.2, -19)};
    auto result = sort_pair(closest_pair_brute(points));
    assert(result == make_pair(Point(-1, 20), Point(1, 21)));
}

int main() {
    //test_empty_points();
    //test_single_point(); проверил вручную все работает
    test_two_points();
    test_three_points();
    test_duplicate_points();
    test_same_x_coordinate();
    test_many_points();
    test_negative_points();
    test_closest_points_from_stripe();

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}