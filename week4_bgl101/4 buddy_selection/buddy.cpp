#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

// Directed graph with int weights on edges.
typedef	adjacency_list<vecS, vecS, undirectedS>	Graph;
typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef	graph_traits<Graph>::vertex_descriptor	Vertex;// Vertex type
typedef graph_traits<Graph>::edge_iterator	EdgeIt;	// Iterator

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void buddy(){
    int n,c,f; cin >> n >> c >> f;
    vector<set<string> > characters(n);
    //~ set<string> characters[n]; //characters[i] gives set of characteristic
    rep(i,n){
        rep(j,c){
            string str; 
            cin >> str; 
            characters[i].insert(str);
        }
    }
    Graph G(n);// build a graph, student i and j have an edge if nb_common_characteristic.(i,j)>=f+1
    rep(i,n) rep(j,i){
        set<string> &s1=characters[i], &s2=characters[j]; // **Need to add &!! so that no need to make a copy of the set**
        set<string> s_common;
        set_intersection( s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(s_common,s_common.begin()) );
        if((int)s_common.size()>=f+1) 
            add_edge(i,j,G);
    }
    vector<Vertex> mate(n);// then try max cardinality matching
    bool success = checked_edmonds_maximum_cardinality_matching(G, &mate[0]);
    assert(success);
    int sz = matching_size(G, &mate[0]);// nb of edges in max-card-matching
    cout << (sz*2==n?"not optimal":"optimal") << endl;
} // buddy()

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    rep(i,t) buddy();
    return 0;
}
