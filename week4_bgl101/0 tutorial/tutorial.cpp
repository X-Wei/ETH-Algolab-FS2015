#include <climits>
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

void testcase();

int main() {
	ios_base::sync_with_stdio(false);
	int T;	// First input line: Number of testcases.
	cin >> T;
	while (T--) testcase();
}

void testcase() {
	int V, E, t;	// 1st line: <ver_no> <edg_no> <tgt>
	cin >> V >> E >> t;
	Graph G(V);
	WeightMap wm = get(edge_weight, G);
	for (int i = 0; i < E; ++i) {
		int u, v, c;
		Edge e;			// Each edge: <src> <tgt> <cost>
		cin >> u >> v >> c;	// Swap u, v and instead of G
		tie(e, tuples::ignore) = add_edge(v, u, G); // create G_T!
		wm[e] = c;
	}

	// Store index of the vertices' strong component
	vector<int> scc(V);
	int nscc = strong_components(G,
			make_iterator_property_map(scc.begin(),
				get(vertex_index, G)));

	// Find universal strong component (if any)
	// Why does this approach work? Exercise.
	vector<int> is_max(nscc, 1);
	EdgeIt ebeg, eend;
	// Iterate over all edges.
	for (tie(ebeg, eend) = edges(G); ebeg != eend; ++ebeg) {
		// ebeg is an iterator, *ebeg is a descriptor.
		int u = source(*ebeg, G), v = target(*ebeg, G);
		if (scc[u] != scc[v])	is_max[scc[u]] = 0;
	}
	int max_count = count(is_max.begin(), is_max.end(), true);
	if (max_count != 1) {
		cout << "NO" << endl;
		return;
	}

	// Compute shortes t-u path in G_T
	vector<int> dist(V);
	vector<int> pred(V);
	dijkstra_shortest_paths(G, t,
		predecessor_map(make_iterator_property_map(pred.begin(),
			get(vertex_index, G))).
    		distance_map(make_iterator_property_map(dist.begin(),
			get(vertex_index, G))));
	int res = INT_MAX;
	for (int u = 0; u < V; ++u)
		// Minimum of distances to 'maximal' universal vertices
		if (is_max[scc[u]])
			res = min(res, dist[u]);
	cout << res << endl;
}
