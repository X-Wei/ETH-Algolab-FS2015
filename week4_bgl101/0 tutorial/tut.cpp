#include <climits>
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/tuple/tuple.hpp> // tuples::ignore

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,
                        no_property,
                        property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; // Iterator
typedef property_map<Graph, edge_weight_t>::type WeightMap; // Map edge -> weight.

void testcase(){
    int V, E, t;
    cin >> V >> E >> t;
    Graph G(V);
    WeightMap wm = get(edge_weight, G);
    // 1. build graph (Gt)
    for(int i=0; i<E; i++){
        int u,v,c;
        cin >> u >> v >> c;
        Edge e; //// Each edge: <src> <tgt> <cost>
        tie(e, tuples::ignore) = add_edge(v, u, G); // swap u and v --> create G_T
        wm[e] = c;
    } // for i = 0 to E 
    // 2. compute SCCs
    vector<int> scc(V); // Store index of the vertices’ strong component (ie. one partition of all vertices)
    int nscc = strong_components(G,
                                make_iterator_property_map(scc.begin(),
                                get(vertex_index, G))); // nscc = nb of scc in Gt
    // 3. count the number of maximal SCCs
    vector<int> is_max(nscc, 1);
    EdgeIt ebeg, eend;
    for (tie(ebeg, eend) = edges(G); ebeg != eend; ++ebeg) {// go through all edges
        // ebeg is an iterator, *ebeg is a descriptor.
        int u = source(*ebeg, G), v = target(*ebeg, G);
        if (scc[u] != scc[v]) // if the edge u-->v is not in the same SCC ==> SCC of u has outgoing edge ==> is not maxmal component
            is_max[scc[u]] = 0;
    } // iterate through all edges 
    int max_count = count(is_max.begin(), is_max.end(), true); // count the number of 1s in `is_max`
    if(max_count!=1){ 
        cout << "NO" << endl;
        return;
    }
    // 4. compute shortest path u-t
    vector<int> dist(V);
    vector<int> pred(V);
    dijkstra_shortest_paths(G, t,
                    predecessor_map(make_iterator_property_map(
                                    pred.begin(), 
                                    get(vertex_index, G))).distance_map(
                                        make_iterator_property_map(dist.begin(),get(vertex_index, G)))
                            );
    // now `dist` contains shortest dist from any vertex to `t`
    int res = INT_MAX;
    for(int u=0; u<V; u++){ // go through all vertices
        if(is_max[scc[u]])
            res = min(res, dist[u]);
    }
    cout << res << endl;
} // testcase()

int main(){
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--) testcase();
}
