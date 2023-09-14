#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <string>
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

// Returns shuffled sequence of unique numbers of specified size, with values from start to start + size - 1.
vector<int> shuffled_sequence(int size, int start = 0) {
    vector<int> result(size);
    iota(result.begin(), result.end(), start);
    random_shuffle(result.begin(), result.end());
    return result;
}

// Returns sequence of random numbers of specified size, with values from 0 to max.
vector<int> random_sequence(int size, int max) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, max);
    vector<int> result;
    for (int i = 0; i < size; i++) {
        result.push_back(distribution(generator));
    }
    return result;
}

int main(int argc, char **argv) {
    const int size = (argc > 1 ? stoi(argv[1]) : 10);
    
    // Container to use.
    vector<int> my_vec_push;
    vector<int> my_vec_ins;
    list<int> my_list_push;
    list<int> my_list_ins;
    set <int> my_set;
    unordered_set <int> my_unordered_set;
 
    //добавление 
    const auto elems_to_add = shuffled_sequence(size);
    
    auto t1=steady_clock:: now();
    for (const auto &elem: elems_to_add) {
        my_vec_push.push_back(elem);
    }
    auto t2=steady_clock::now();

    auto time = duration<double>(t2 - t1).count();
    cout << "vector_pushback for "<< size << " size is:"<<time << " sec." << endl;


    t1=steady_clock:: now();
    
    for (const auto &elem: elems_to_add) {
        my_vec_ins.insert(my_vec_ins.begin(),elem);
    }
    t2=steady_clock::now();

    time = duration<double>(t2 - t1).count();
    cout << "vector insert for "<< size << " size is:"<<time << " sec." << endl;

    t1=steady_clock:: now();
    for (const auto &elem: elems_to_add) {
        my_list_push.push_back(elem);
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "list pushback for "<< size << " size is:"<<time << " sec." << endl;

    t1=steady_clock:: now();
    for (const auto &elem: elems_to_add) {
        my_list_ins.insert(my_list_ins.begin(),elem);
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "list insert for "<< size << " size is:"<<time << " sec." << endl;

    t1=steady_clock:: now();
    for (const auto &elem: elems_to_add) {
        my_set.insert(elem);
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "set insert for "<< size << " size is:"<<time << " sec." << endl;

    t1=steady_clock:: now();
    for (const auto &elem: elems_to_add) {
        my_unordered_set.insert(elem);
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "unordered set insert for "<< size << " size is:"<<time << " sec." << endl;
    
    // Perform search into container.
    
    
    int hits = 0;
    const auto elems_to_search = random_sequence(1000, 2 * size);

    t1=steady_clock:: now();
    for (const auto &elem: elems_to_search) {
        auto it = find(my_vec_push.begin(), my_vec_push.end(), elem);
        if (it != my_vec_push.end()) {
            hits++;
        }        
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "vector find for "<< size << " size is:"<<time << " sec." << endl;

    hits=0;

    t1=steady_clock:: now();
    for (const auto &elem: elems_to_search) {
        auto it = find(my_list_push.begin(), my_list_push.end(), elem);
        if (it != my_list_push.end()) {
            hits++;
        }        
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "list find for "<< size << " size is:"<<time << " sec." << endl;

    hits=0;
    t1=steady_clock:: now();
    for (const auto &elem: elems_to_search) {
        auto it = my_set.find(elem);
        if (it != my_set.end()) {
            hits++;
        }        
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "set find for "<< size << " size is:"<<time << " sec." << endl;

    hits=0;

    t1=steady_clock:: now();
    for (const auto &elem: elems_to_search) {
        auto it = my_unordered_set.find(elem);
        if (it != my_unordered_set.end()) {
            hits++;
        }        
    }
    t2=steady_clock::now();
    time = duration<double>(t2 - t1).count();
    cout << "unordered set find for "<< size << " size is:"<<time << " sec." << endl;

}
