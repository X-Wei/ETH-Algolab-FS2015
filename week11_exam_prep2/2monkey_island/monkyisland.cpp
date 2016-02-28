#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore

using namespace std;
using namespace boost;

// Directed graph with int weights on edges.
typedef	adjacency_list<vecS, vecS, directedS,
		no_property,
		property<edge_weight_t, int> >	Graph;
typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator	EdgeIt;	// Iterator
// Map edge -> weight.
typedef	property_map<Graph, edge_weight_t>::type	WeightMap;

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

void monkey(){
    int m,n; cin >> n >>m;
    Graph G(n);// original graph
    rep(_,m){
        int i,j; cin >> i >> j; // i-j are 1-based!!
        add_edge(i-1, j-1, G);
    }
    int c[n];
    rep(i,n) cin >> c[i];
    // Store index of the vertices' strong component
    vector<int> scc(n);
    int nscc = strong_components(G,	make_iterator_property_map(scc.begin(),get(vertex_index, G)));
    vector<bool> is_max(nscc, true); // a "max scc" is a scc with no incoming edges!
    EdgeIt ebeg, eend;// Iterate over all edges.
    for (tie(ebeg, eend) = edges(G); ebeg != eend; ++ebeg) {// ebeg is an iterator, *ebeg is a descriptor.
        int u = source(*ebeg, G), v = target(*ebeg, G);// u-->v
        if (scc[u] != scc[v]) is_max[scc[v]] = false;// if an SCC has incoming edges, it is not maxscc
    }
    int res=0;
    rep(i, nscc){
        if(is_max[i]==false) continue;
        int mincost=INT_MAX;
        rep(j,n) if(scc[j]==i)// if vertex j belongs to max SCC i
            mincost=min(mincost, c[j]);
        res+=mincost;
    }
    cout << res << endl;

}

int main(){
    int t; cin >> t;
    rep(i,t) monkey();
    return 0;
}
