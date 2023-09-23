#include <vector>
#include <set>
using namespace std;

bool has_duplicates_quick(const std::vector<int> &data) {
    set<int> my_set(data.begin(),data.end());
    if (my_set.size()==data.size()){
        return false;

    }
    return true;
}

std::vector<int> get_duplicates_quick(const std::vector<int> &data) {
    std::vector<int> result;
    set<int> my_set;
    for(const auto & elem: data){
        if (my_set.find(elem)!=my_set.end()){//elem есть в set
            result.push_back(elem);
            }
        my_set.insert(elem);
    }
    return result;
}
