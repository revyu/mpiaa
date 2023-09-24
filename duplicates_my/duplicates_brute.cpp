
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool has_duplicates_brute(const std::vector<int> &data) {
    for (int i=0;i<data.size()-1;i++){
        for (int j=i+1;j<data.size();j++ ){
            if (data[i]==data[j]){return true;}
        }
    }
    return false;
}

vector<int> get_duplicates_brute(const std::vector<int> &data) {
    std::vector<int> result;
    for (int i=0;i<data.size()-1;i++){
        for (int j=i+1;j<data.size();j++ ){
            if (data[i]==data[j]){
                if (find(result.begin(),result.end(),data[i])==result.end()){result.push_back(data[i]);}
            
                }
        }
    }
    
    return result;
}
