


#include "shortest_path.h"

using namespace std;
int main() {
    Graph g {{0, 1, 2.5}, {0, 2, 3.0}};
    vector <int> myvec=my_shortest_path(g,1,2);
    for (const auto elem: myvec){
        cout<<elem<<" ";
    }
    cout<<"kal";
}
