#include <vector>
#include <iostream>
#include <cassert>
#include <set>
#include <random>


using namespace std;

// preps

class Activity {
public:
    Activity() = default;
    Activity(int start, int finish) : start(start), finish(finish) {}

    bool operator<(const Activity &a) const;
    bool operator==(const Activity &a) const;

public:
    int start{0};
    int finish{0};
};

bool Activity::operator<(const Activity &a) const {
    return (finish < a.finish || (finish == a.finish && start > a.start));
}

bool Activity::operator==(const Activity &a) const {
    return (start == a.start && finish == a.finish);
}

void print(vector<Activity> activities) {
    for (int i = 0; i < activities.size(); i++) {
        cout << activities[i].start << " " << activities[i].finish << endl;
    }
}



//greedy


int partition(vector<Activity> &activities, int start, int end) {
    Activity pivot = activities[end];

    int pIndex = start;
    for (int i = start; i < end; i++) {
        if (activities[i] < pivot || activities[i] == pivot) {
            swap(activities[i], activities[pIndex]);
            pIndex++;
        }
    }
    swap(activities[pIndex], activities[end]);
    return pIndex;
}

void quicksort(vector<Activity> &activities, int start, int end) {
    if (start >= end) {
        return;
    }

    int pivot = partition(activities, start, end);

    quicksort(activities, start, pivot - 1);

    quicksort(activities, pivot + 1, end);
}

vector<Activity> get_max_activities(const vector<Activity> &activities) {
    vector<Activity> sortedActivities = activities; // Создаем копию, чтобы не изменять оригинальный вектор
    quicksort(sortedActivities, 0, sortedActivities.size() - 1);
    vector<Activity> result = {};

    for (int i = 0; i < sortedActivities.size();) {
        result.push_back(sortedActivities[i]);
        int next = -1;
        for (int j = i + 1; j < sortedActivities.size(); j++) {
            if (sortedActivities[j].start >= sortedActivities[i].finish) {
                next = j;
                break;
            }
        }
        if (next == -1) {
            return result;
        } else {
            i = next;
        }
    }
}



// Convert vector of activities to set for equality comparison.
set<Activity> to_set(const vector<Activity> &acts) {
    return set<Activity>(acts.begin(), acts.end());
}

void test_empty() {
    assert(to_set(get_max_activities({})) == to_set({}));
}

void test_one_activity() {
    assert(to_set(get_max_activities({{2, 3}})) == to_set({{2, 3}}));
}

void test_two_compatibles() {
    assert(to_set(get_max_activities({{3, 4}, {2, 3}})) == to_set({{2, 3}, {3, 4}}));
}

void test_two_overlaps() {
    const auto answer = to_set(get_max_activities({{2, 5}, {3, 4}}));
    assert(answer == to_set({{2, 5}}) || answer == to_set({{3, 4}}));
}

void test_two_incompatibles() {
    const auto answer = to_set(get_max_activities({{3, 6}, {2, 5}}));
    assert(answer == to_set({{2, 5}}) || answer == to_set({{3, 6}}));
}

void test_three_activities() {
    const auto answer = to_set(get_max_activities({{2, 6}, {1, 4}, {5, 8}}));
    assert(answer == to_set({{1, 4}, {5, 8}}));
}

void test_four_activities() {
    const auto answer = to_set(get_max_activities({{2, 6}, {1, 4}, {7, 10}, {5, 8}}));
    assert(answer == to_set({{1, 4}, {5, 8}}) || answer == to_set({{2, 6}, {7, 10}}));
}

void test_five_activities() {
    const auto answer = to_set(get_max_activities({{2, 6}, {1, 4}, {7, 10}, {5, 8}, {9, 12}}));
    assert(answer == to_set({{1, 4}, {5, 8}, {9, 12}}));
}

void test_big_one() {
    const auto answer = to_set(get_max_activities({{3, 5}, {1, 4}, {5, 7}, {0, 6},
                                                   {3, 9}, {5, 9}, {6, 11}, {4, 10},
                                                   {8, 12}, {2, 14}, {12, 16}}));
    assert(answer == to_set({{1, 4}, {5, 7}, {8, 12}, {12, 16}}) ||
           answer == to_set({{3, 5}, {5, 7}, {8, 12}, {12, 16}}));
}

void test() {
    test_empty();
    test_one_activity();
    test_two_compatibles();
    test_two_overlaps();
    test_two_incompatibles();
    test_three_activities();
    test_four_activities();
    test_five_activities();
    test_big_one();

    cout << "All tests passed!" << endl;

    return ;
}


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
    get_max_activities(activities);
    auto t2=steady_clock::now();
    cout <<"for size="<< size << " get_max_activities :" <<duration<double>(t2 - t1).count()<<endl;


    



}