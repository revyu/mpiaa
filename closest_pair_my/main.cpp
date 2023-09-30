#include "algo_divide_and_rule.cpp"

#include <random>
#include <chrono>

using namespace std;
using namespace std:: chrono;

vector<Point> generatePoints(int n) {
    std::vector<Point> res_points;

    // Инициализируем генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < n; i++) {
        int x = dis(gen);  // Генерируем случайное значение для x
        int y = dis(gen);  // Генерируем случайное значение для y
        res_points.push_back(Point(x, y));
    }

    return res_points;
}

int main() {
    int n;
    cin>>n;
    vector<Point> points =generatePoints(n);

    auto t1=steady_clock::now();
    closest_pair_divide_and_rule(points);
    auto t2=steady_clock::now();
    cout <<"for size="<< n << " closest_pair_divide_and_rule is :" <<duration<double>(t2 - t1).count()<<endl;
    
    t1=steady_clock::now();
    closest_pair_brute(points);
    t2=steady_clock::now();
    cout <<"for size="<< n << " closest_pair_brute is :" <<duration<double>(t2 - t1).count()<<endl;
    


}




