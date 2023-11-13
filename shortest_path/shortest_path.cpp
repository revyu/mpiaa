#include "shortest_path.h"

using namespace std;

vector <int> build_path(vector <int> parent,int start,int end){

}

int get_min_dist(Graph &graph,vector<double> distances){

}

void shortest_path(const Graph &graph, int start, int end) {
    // Return shortest path in the graph from start vertex to end vertex as array of vertices.
    // First item in the result should be start vertex, last - end vertex.
    // Return empty array if there is no path.

    // Your implementation here.



    vector<double> distances(graph.get_vertices().size());
    vector<int> parent={};
    int min_dist=INFINITY;
    int min_vertex=start;
    for (int i=0;i<graph.get_vertices().size();i++){
        distances[i]=INFINITY;
    }
    distances[start]=0;
    
    vector<int> Q=graph.get_vertices();

    while(Q.size()!=0){
        for (int i =0;i<distances.size();i++){
            if (distances[i]<min_dist){
                min_vertex=i;
                min_dist=distances[i];
            }
        }
        if (min_vertex==end){build_path(parent,start,end);}
        vector<int> adjacent_vertices=get_adjacent_vertices(min_vertex);
        for (const auto vertex:adjacent_vertices){
            if (distances[vertex]>distances[min_vertex]+edge_weight(min_vertex)){
                distances[vertex]=distances[min_vertex]+edge_weight(min_vertex);
                parent[vertex]=min_vertex;

            }
        }

    }



    
}
