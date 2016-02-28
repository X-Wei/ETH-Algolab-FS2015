#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/tuple/tuple.hpp> // tuples::ignore
#include <boost/graph/biconnected_components.hpp>
using namespace std;
using namespace boost;

// Directed graph with int weights on edges.
typedef    adjacency_list<vecS, vecS, undirectedS,
                no_property,
                property<edge_weight_t, int> >	Graph;
typedef    graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef    graph_traits<Graph>::vertex_descriptor Vertex;
typedef    graph_traits<Graph>::edge_iterator	EdgeIt;	// Iterator
typedef    graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef    property_map<Graph, edge_weight_t>::type	WeightMap; // Map edge -> weight.

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void important_bridges(){
    int n,m; cin >> n >> m;
    Graph G(n);
    WeightMap wm = get(edge_weight, G); 
    rep(j,m){
        int u,v; cin >> u >> v;
        add_edge(u-1, v-1, G); 
    }
    int ncomp = biconnected_components(G, wm); 
    std::set<pair<int,int> > res; // vector to store result as pair<u,v> (u<v)
    
    EdgeIt ei, ei_end;
    vector<int> count(ncomp,0);// see each component has how many edges
    for (tie(ei, ei_end) = edges(G); ei != ei_end; ++ei)
        count[wm[*ei]]++;
    for (tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
        if(count[wm[*ei]]==1){
            int u=source(*ei,G), v=target(*ei,G);
            pair<int,int> bridge = (u<v ? make_pair(u,v) : make_pair(v,u));
             res.insert(bridge);
        }
    }// go over all edges and see the size of each bi-component
    cout << res.size() << endl; // res is already sorted !
    // output result
    for(set<pair<int,int> >::iterator it=res.begin(); it!=res.end(); ++it) 
        cout << it->first+1 << " " << it->second+1 << endl;
} // important_bridges()

int main(){
    int t; cin >> t;
    rep(i,t) 
        important_bridges();
    return 0;
}
