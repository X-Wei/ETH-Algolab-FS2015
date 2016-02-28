#include <climits>
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
//~ #include <boost/graph/strong_components.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/tuple/tuple.hpp> // tuples::ignore

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        no_property,
                        property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; // Iterator
typedef property_map<Graph, edge_weight_t>::type WeightMap; // Map edge -> weight.

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

void graphs(){
    int n,m,u,v,c;
    cin >> n >> m;
    Graph G(n);
    WeightMap wm = get(edge_weight, G); // associate wm with G --> so that G is edge-weighted
    // 1. build graph
    rep(_,m){
        cin >> u >> v >> c;
        Edge e; 
        tie(e, tuples::ignore) = add_edge(u, v, G); 
        wm[e] = c;
    }
    // 2. compute MST
    vector<Edge> mst; // edge vector to store mst
    kruskal_minimum_spanning_tree(G, back_inserter(mst));
    vector<Edge>::iterator ebeg, eend = mst.end();
    int mst_weight = 0;
    for (ebeg = mst.begin(); ebeg != eend; ++ebeg) {
        mst_weight += wm[*ebeg];
    }
    // 3. compute distance
    vector<int> dist(n);
    vector<int> pred(n);
    dijkstra_shortest_paths(G, 0,
        predecessor_map(make_iterator_property_map(
            pred.begin(), 
            get(vertex_index, G))).distance_map(
                make_iterator_property_map(dist.begin(),get(vertex_index, G)))
        );
    // now `dist` contains shortest dist from any vertex to `t`
    int max_d = INT_MIN;
    rep(u,n) // go through all vertices
        max_d = max(max_d, dist[u]);
    cout << mst_weight << " " << max_d << endl;
}

int main(){
    int t;
    cin >> t;
    rep(_,t) 
        graphs();
}
