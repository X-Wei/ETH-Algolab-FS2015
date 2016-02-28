#include <climits>
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, // directed graph
                        no_property,//color_property<>, // no_property, 
                        property<edge_weight_t, int> // edge-weighted graph
                        > Graph; 
typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; // Iterator
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, edge_weight_t>::type WeightMap; // Map edge -> weight.

#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,(int)N-1)

void oddroute(){
    int n,m; cin >> n >> m;
    Graph G(4*n); WeightMap wm = get(edge_weight, G);
    /* each vertex v in original graph --> 4 vertices in G v_oo, v_ee, v_oe, v_eo
     * v_oo (v) --> shortest path from s_ee to v take odd nb of edges, and have odd weight
     * v_oe (v+n)--> shortest path from s_ee to v take odd nb of edges, and have even weight
     * ...
     * */
    int oo[n], oe[n], eo[n], ee[n];
    rep(i,n) {oo[i]=i; oe[i]=i+n; eo[i]=i+2*n; ee[i]=i+3*n;}
    int s,t; cin >> s >> t;
    Edge e;
    rep(_,m){
        int u,v,w; cin >> u >> v >> w;
        if(w%2==1){// odd weight  u_oe --> v_eo
            tie(e, tuples::ignore) = add_edge(oo[u], ee[v], G); wm[e] = w;// u_oo --> v_ee
            tie(e, tuples::ignore) = add_edge(oe[u], eo[v], G); wm[e] = w;// u_oe --> v_eo
            tie(e, tuples::ignore) = add_edge(eo[u], oe[v], G); wm[e] = w;// ...
            tie(e, tuples::ignore) = add_edge(ee[u], oo[v], G); wm[e] = w;
        }else{// even weight
            tie(e, tuples::ignore) = add_edge(oo[u], eo[v], G); wm[e] = w;// u_oo --> v_eo
            tie(e, tuples::ignore) = add_edge(oe[u], ee[v], G); wm[e] = w;// u_oe --> v_ee
            tie(e, tuples::ignore) = add_edge(eo[u], oo[v], G); wm[e] = w;// ...
            tie(e, tuples::ignore) = add_edge(ee[u], oe[v], G); wm[e] = w;
        }
    }// add edges
    int V=num_vertices(G);
    vector<int> dist(V), pred(V);
    dijkstra_shortest_paths(
            G, ee[s], // dijkstra: from source=s_ee to target=t_oo
            predecessor_map( make_iterator_property_map(pred.begin(), get(vertex_index, G)) ).
                    distance_map( make_iterator_property_map(dist.begin(),get(vertex_index, G)) ) );
    if(dist[oo[t]]<INT_MAX) cout<<dist[oo[t]]<< endl;
    else cout << "no" << endl;
}

int main(){
    int t; cin >>t;
    rep(i,t) oddroute();
    return 0;
}
