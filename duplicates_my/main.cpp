
#include "duplicates_brute.cpp"
#include "duplicates_quick.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

using namespace std;
using namespace std:: chrono;

template <typename S> void print(const S& s) {
    
    for (const auto& p : s) {
        cout <<p<<" " ;
    }

    cout << endl;
    cout << "size="<<s.size();
    cout << endl;
}


vector<int> generateRandomVectorWithDuplicates(int size, int min, int max, double duplicatePercentage=0.3) {
    if (size <= 0 || min > max || duplicatePercentage < 0.0 || duplicatePercentage > 1.0) {
        cerr << "Invalid input parameters." << endl;
        return vector<int>();
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);

    vector<int> result;
    int numDuplicates = static_cast<int>(size * duplicatePercentage);

    for (int i = 0; i < numDuplicates; ++i) {
        result.push_back(distribution(gen));
    }

    for (int i = numDuplicates; i < size; ++i) {
        int value = distribution(gen);
        result.push_back(value);
    }

    shuffle(result.begin(), result.end(), gen);

    return result;
}

std::vector<int> generateRandomVectorWithoutDuplicates(int size, int min, int max) {
    if (size <= 0 || min > max) {
        std::cerr << "Invalid input parameters." << std::endl;
        return std::vector<int>();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    std::vector<int> result;
    while (result.size() < size) {
        int value = distribution(gen);
        if (std::find(result.begin(), result.end(), value) == result.end()) {
            result.push_back(value);
        }
    }

    return result;
}


int main(int argc, char **argv) {
    int size,vmin,vmax;
    
    cin>>size>>vmin>>vmax;

    vector<int> gen_duplicates = generateRandomVectorWithDuplicates(size, vmin, vmax);
    
    auto t1=steady_clock::now();
    has_duplicates_brute(gen_duplicates);
    auto t2=steady_clock::now();
    cout <<"for size="<< size << " time has_duplicates_brute is :" <<duration<double>(t2 - t1).count()<<endl;

    /*
    t1=steady_clock::now();
    get_duplicates_brute(gen_duplicates);
    t2=steady_clock::now();
    cout <<"for size="<< size << " time get_duplicates_brute is :" <<duration<double>(t2 - t1).count()<<endl;
    */

    
    t1=steady_clock::now();
    has_duplicates_quick(gen_duplicates);
    t2=steady_clock::now();
    cout <<"for size="<< size << " time has_duplicates_quick is :" <<duration<double>(t2 - t1).count()<<endl;

    t1=steady_clock::now();
    get_duplicates_quick(gen_duplicates);
    t2=steady_clock::now();
    cout <<"for size="<< size << " time get_duplicates_quick is :" <<duration<double>(t2 - t1).count()<<endl;

    }
