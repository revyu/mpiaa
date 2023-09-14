#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

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
    cout<<size<< endl;
    // Container to use.
    vector<int> my_vec_push;
    vector<int> my_vec_ins;
    list<int> my_list_push;
    list<int> my_list_ins;
    set <int> my_set;
    unordered_set <int> my_unordered_set;
 
    //добавление 
    const auto elems_to_add = shuffled_sequence(size);
    // pushback into vector 
    for (const auto &elem: elems_to_add) {
        my_vec_push.push_back(elem);
    }
    // insert into begin
    for (const auto &elem: elems_to_add) {
        my_vec_ins.insert(my_vec_ins.begin(),elem);
    }

    for (const auto &elem: elems_to_add) {
        my_list_push.push_back(elem);
    }

    for (const auto &elem: elems_to_add) {
        my_list_ins.insert(my_list_ins.begin(),elem);
    }

    for (const auto &elem: elems_to_add) {
        my_set.insert(elem);
    }

    for (const auto &elem: elems_to_add) {
        my_unordered_set.insert(elem);
    }

    
    // Perform search into container.
    
    int hits = 0;
    const auto elems_to_search = random_sequence(1000, 2 * size);
    for (const auto &elem: elems_to_search) {
        auto it = find(my_vec_push.begin(), my_vec_push.end(), elem);
        if (it != my_vec_push.end()) {
            hits++;
        }        
    }

    hits=0;
    
    for (const auto &elem: elems_to_search) {
        auto it = find(my_list_push.begin(), my_list_push.end(), elem);
        if (it != my_list_push.end()) {
            hits++;
        }        
    }

    hits=0;
    
    for (const auto &elem: elems_to_search) {
        auto it = find(my_set.begin(), my_set.end(), elem);
        if (it != my_set.end()) {
            hits++;
        }        
    }

    hits=0;
    
    for (const auto &elem: elems_to_search) {
        auto it = find(my_unordered_set.begin(), my_unordered_set.end(), elem);
        if (it != my_unordered_set.end()) {
            hits++;
        }        
    }
    

}
