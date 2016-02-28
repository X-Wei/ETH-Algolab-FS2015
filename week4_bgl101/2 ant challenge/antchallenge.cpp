#include <climits>
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
//~ #include <boost/graph/strong_components.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/tuple/tuple.hpp> // tuples::ignore

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, 
                    undirectedS,
                    no_property,
                    property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; // Iterator
typedef property_map<Graph, edge_weight_t>::type WeightMap; // Map edge -> weight.

typedef map<Edge, int> WeightMapping;
typedef associative_property_map<WeightMapping> EdgeMap;

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

void antchallenge(){
    int t,e,s,a,b;
    cin >> t >> e >> s >> a >> b;
    Graph graphs[s];
    WeightMap wms[s];
    rep(i,s){
        graphs[i] = Graph(t);
        wms[i] = get(edge_weight, graphs[i]); 
    }
    // 1. build s graphs
    rep(_,e){
        int u,v,c;
        cin >> u >> v;
        rep(i,s){
            cin >> c;
            Edge e; 
            tie(e, tuples::ignore) = add_edge(u, v, graphs[i]); 
            wms[i][e] = c;
        }
    }
    int hives[s];
    rep(i,s) // read hives
        cin >> hives[i];
    int res = INT_MAX;
    rep(i,s){// for each species calculate its best time
        Graph Gi = graphs[i];
        // 2.1 first build the ant's private network: which is just a shortest-path spanning tree (Dijkstra from hive[i])
        /*vector<int> dist(t);
        vector<int> pred(t);
        dijkstra_shortest_paths(Gi, hives[i],// do a Dijkstra from hive[i] to get the `pred` mapping (ie. the spnning tree)
                    predecessor_map(make_iterator_property_map(
                                    pred.begin(), 
                                    get(vertex_index, Gi))).distance_map(
                                        make_iterator_property_map(dist.begin(),get(vertex_index, Gi)))
                            );*/
        
        /*vector<Edge> mst; // edge vector to store mst
        kruskal_minimum_spanning_tree(Gi, back_inserter(mst));*/
        
        vector<int> p(t); // predecessor vector
        prim_minimum_spanning_tree(Gi, &p[0], 
            root_vertex(hives[i])
                //.weight_map(EdgeMap(wms[i]))
        );
                            
        // 2.2 build a new G: contains only edges from spnning tree of Gi
        Graph G(t);
        WeightMap wm = get(edge_weight, G); 
        /*EdgeIt ebeg, eend;
        cout <<"Spanning tree "<<i<<endl;
        for (tie(ebeg, eend) = edges(Gi); ebeg != eend; ++ebeg) {// go through all edges of Gi: select only spnning tree edges
            int u = source(*ebeg, Gi), v = target(*ebeg, Gi);
            if (u==pred[v] || v==pred[u]){ // if this edge is in the spanning tree
                Edge e; 
                tie(e, tuples::ignore) = add_edge(u, v, G); 
                wm[e] = wms[i][*ebeg];
                cout<<u<<"-"<<v<<", ";
            }
        }
        cout <<"nb edges in G: "<< num_edges(G)<<endl;*/
        
        /*vector<Edge>::iterator ebeg, eend = mst.end();
        for (ebeg = mst.begin(); ebeg != eend; ++ebeg) {
            Edge e; 
            int u = source(*ebeg, Gi), v = target(*ebeg, Gi);
            tie(e, tuples::ignore) = add_edge(u, v, G); 
            wm[e] = wms[i][*ebeg];
        }*/
        
        EdgeIt ebeg, eend;
        for (tie(ebeg, eend) = edges(Gi); ebeg != eend; ++ebeg) {// go through all edges of Gi: select only spnning tree edges
            int u = source(*ebeg, Gi), v = target(*ebeg, Gi);
            if (u==p[v] || v==p[u]){ // if this edge is in the spanning tree
                Edge e; 
                tie(e, tuples::ignore) = add_edge(u, v, G); 
                wm[e] = wms[i][*ebeg];
            }
        }
        
        // 2.3 compute the shortest path from private network for species i: Dijkstra on spanning tree
        vector<int> dist(t);
        vector<int> pred(t);
        dijkstra_shortest_paths(G, a,
                predecessor_map(make_iterator_property_map(
                pred.begin(), 
                get(vertex_index, G))).distance_map(
                    make_iterator_property_map(dist.begin(),get(vertex_index, G)) )
            );
        res = min(res, dist[b]);
    }
    cout << res << endl;
}

int main(){
    int t;
    cin >> t;
    rep(_,t) 
        antchallenge();
}
