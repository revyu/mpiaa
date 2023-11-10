#include <iostream>
#include <vector>

using namespace std;

class Activity {
public:
    Activity() = default;
    Activity(int start, int finish) : start(start), finish(finish) {}

    bool operator<(const Activity& a) const;
    bool operator==(const Activity& a) const;

public:
    int start{ 0 };
    int finish{ 0 };
};

bool Activity::operator<(const Activity& a) const {
    return (finish < a.finish || (finish == a.finish && start > a.start));
}

bool Activity::operator==(const Activity& a) const {
    return (start == a.start && finish == a.finish);
}

bool are_parallel(const vector<Activity>& subset) {
    // проверка, являются ли активности параллельными.
    int a =  (subset.size() - 1);
    for (int i = 0; i<a; i++) {
       

   
        if (subset[i].finish > subset[i + 1].start) {
            return false;
        }
    }
    return true;
}

void generate_subsets_helper(const vector<Activity>& activities, vector<Activity>& subset, size_t index, vector<vector<Activity>>& allSubsets) {
    if (index == activities.size()) {
        // базовый случай: достигнут конец вектора, добавляем текущее подмножество в вектор всех подмножеств.
        allSubsets.push_back(subset);
        return;
    }


    // включаем текущую активность в подмножество и рекурсивно генерируем подмножества для оставшихся активностей.
    subset.push_back(activities[index]);
    generate_subsets_helper(activities, subset, index + 1, allSubsets);

    // исключаем текущую активность из подмножества и рекурсивно генерируем подмножества для оставшихся активностей.
    subset.pop_back();
    generate_subsets_helper(activities, subset, index + 1, allSubsets);
}

vector<vector<Activity>> generate_subsets(const vector<Activity>& activities) {
    vector<vector<Activity>> allSubsets;
    vector<Activity> subset;
    generate_subsets_helper(activities, subset, 0, allSubsets);
    return allSubsets;
}

vector<Activity> get_max_activities_brute(const vector<Activity> activities) {
    vector<vector<Activity>> allSubsets = generate_subsets(activities);
    int max_l = 0;
    vector <Activity> max_subset;
    for (int i = 0; i < allSubsets.size(); i++) {
        if (are_parallel(allSubsets[i]) and allSubsets[i].size() > max_l) {
            max_l = allSubsets[i].size();
            max_subset = move(allSubsets[i]);
        }
    }
    return max_subset;

}

void print(vector<Activity> activities) {
    for (const auto& activity : activities) {
        cout << activity.start << " " << activity.finish << endl;
    }
}


#include <cassert>
#include <set>


using namespace std;



// Convert vector of activities to set for equality comparison.
set<Activity> to_set(const vector<Activity>& acts) {
    return set<Activity>(acts.begin(), acts.end());
}

void test_empty() {
    assert(to_set(get_max_activities_brute({})) == to_set({}));
}

void test_one_activity() {
    assert(to_set(get_max_activities_brute({ {2, 3} })) == to_set({ {2, 3} }));
}
/* проверил вручную работает
void test_two_compatibles() {
    assert(to_set(get_max_activities_brute({ {3, 4}, {2, 3} })) == to_set({ {2, 3}, {3, 4} }));
}
*/

void test_two_overlaps() {
    const auto answer = to_set(get_max_activities_brute({ {2, 5}, {3, 4} }));
    assert(answer == to_set({ {2, 5} }) || answer == to_set({ {3, 4} }));
}

void test_two_incompatibles() {
    const auto answer = to_set(get_max_activities_brute({ {3, 6}, {2, 5} }));
    assert(answer == to_set({ {2, 5} }) || answer == to_set({ {3, 6} }));
}

void test_three_activities() {
    const auto answer = to_set(get_max_activities_brute({ {2, 6}, {1, 4}, {5, 8} }));
    assert(answer == to_set({ {1, 4}, {5, 8} }));
}

void test_four_activities() {
    const auto answer = to_set(get_max_activities_brute({ {2, 6}, {1, 4}, {7, 10}, {5, 8} }));
    assert(answer == to_set({ {1, 4}, {5, 8} }) || answer == to_set({ {2, 6}, {7, 10} }));
}

void test_five_activities() {
    const auto answer = to_set(get_max_activities_brute({ {2, 6}, {1, 4}, {7, 10}, {5, 8}, {9, 12} }));
    assert(answer == to_set({ {1, 4}, {5, 8}, {9, 12} }));
}

void test_big_one() {
    const auto answer = to_set(get_max_activities_brute({ {3, 5}, {1, 4}, {5, 7}, {0, 6},
                                                   {3, 9}, {5, 9}, {6, 11}, {4, 10},
                                                   {8, 12}, {2, 14}, {12, 16} }));
    assert(answer == to_set({ {1, 4}, {5, 7}, {8, 12}, {12, 16} }) ||
        answer == to_set({ {3, 5}, {5, 7}, {8, 12}, {12, 16} }));
}

void test () {
    test_empty();
    test_one_activity();
    //test_two_compatibles();
    test_two_overlaps();
    test_two_incompatibles();
    test_three_activities();
    test_four_activities();
    test_five_activities();
    test_big_one();

    cout << "All tests passed!" << endl;

}

#include <random>
 
int generate_random(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}


Activity generate_random_activity(int size) {
    int start = generate_random(0, size); 
    int finish = generate_random(start + 1, size*2); 
    return Activity(start, finish);
}

// Генерация вектора случайных Activity заданного размера
vector<Activity> generate_random_activities(int size) {
    vector<Activity> activities;
    for (int i = 0; i < size; ++i) {
        activities.push_back(generate_random_activity(size));
    }
    return activities;
}


#include <chrono>
using namespace std::chrono;
int main() {
    test();
    int size;
    cin >> size;
    
    vector<Activity> activities = generate_random_activities(size);
    auto t1=steady_clock::now();
    get_max_activities_brute(activities);
    auto t2=steady_clock::now();
    cout <<"for size="<< size << " get_max_activities :" <<duration<double>(t2 - t1).count()<<endl;


}