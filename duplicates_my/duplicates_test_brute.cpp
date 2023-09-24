
#include <algorithm>
#include <cassert>
#include "duplicates_brute.cpp"
#include <vector>
#include <iostream>

template <class T>
std::vector<T> sorted(const typename std::vector<T> &data) {
    typename std::vector<T> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());
    return sorted_data;
}

void test_empty_array() {
    const std::vector<int> data = {};
    assert(!has_duplicates_brute(data));
    assert(sorted(get_duplicates_brute(data)) == std::vector<int>{});
}

void test_single_element() {
    const std::vector<int> data = {1};
    assert(!has_duplicates_brute(data));
    assert(sorted(get_duplicates_brute(data)) == std::vector<int>{});
}

void test_many_elements() {
    const std::vector<int> data = {2, 1, -4, 7};
    assert(!has_duplicates_brute(data));
    assert(sorted(get_duplicates_brute(data)) == std::vector<int>{});
}

void test_many_elements_one_duplicate() {
    const std::vector<int> data = {2, -3, 0, 2, 7, 1};
    assert(has_duplicates_brute(data));
    assert(sorted(get_duplicates_brute(data)) == std::vector<int>{2});
}

void test_many_elements_many_duplicates() {
    const std::vector<int> data = {2, -3, 0, 2, 1, -3, 4, 1, -1, 2};
    assert(has_duplicates_brute(data));
    std::vector<int> expected = {-3, 1, 2};
    assert(sorted(get_duplicates_brute(data)) == expected);
}

void test_single_duplicated_elem() {
    const std::vector<int> data = {4, 4, 4, 4};
    assert(has_duplicates_brute(data));
    assert(sorted(get_duplicates_brute(data)) == std::vector<int>{4});
}

int main() {
    test_empty_array();
    test_single_element();
    test_many_elements();
    test_many_elements_one_duplicate();
    test_many_elements_many_duplicates();
    test_single_duplicated_elem();
    std::cout << "All tests passed successfully!";
    return 0;
}