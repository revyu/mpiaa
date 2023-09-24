#include "duplicates.h"

using namespace std;

bool has_duplicates(const std::vector<int> &data) {
    for (int i=0;i<data.size();i++){
        for (int j=i;j<data.size();j++ ){
            if (data[i]==data[j]){return true;}
        }
    }
    return false;
}

vector<int> get_duplicates(const std::vector<int> &data) {
    std::vector<int> result;
    for (int i=0;i<data.size();i++){
        for (int j=i;j<data.size();j++ ){
            if (data[i]==data[j]){result.push_back(data[i]);}
        }
    }
    
    return result;
}
