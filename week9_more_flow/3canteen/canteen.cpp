#include <iostream>
#include <cstdlib>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace boost;
using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); ++i)
#define rep(i,N) forloop(i,0,(int)N-1)

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator


struct EdgeAdder {
    EdgeAdder(Graph & G, EdgeCapacityMap &capacity, EdgeWeightMap &weight, ReverseEdgeMap &rev_edge) 
        : G(G), capacity(capacity), weight(weight), rev_edge(rev_edge) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacity[e] = c;
        weight[e] = w;
        capacity[reverseE] = 0;
        weight[reverseE] = -w;
        rev_edge[e] = reverseE; 
        rev_edge[reverseE] = e; 
    }
    Graph &G;
    EdgeCapacityMap &capacity;
    EdgeWeightMap &weight;
    ReverseEdgeMap  &rev_edge;
};

void canteen(){
    int n,vi,ei;//ai,ci,si,pi,vi,ei;
    cin >> n;
    Graph G(n);// Create Graph and Maps
    EdgeCapacityMap capacity = get(edge_capacity, G);
    EdgeWeightMap weight = get(edge_weight, G);
    ReverseEdgeMap rev_edge = get(edge_reverse, G);
    ResCapacityMap res_capacity = get(edge_residual_capacity, G);
    
    EdgeAdder ea(G, capacity, weight, rev_edge);
    Vertex _source = add_vertex(G), sink = add_vertex(G);
    int a[n],c[n],s[n],p[n];
    rep(i,n){
        cin >> a[i] >> c[i];
        //~ ea.addEdge(_source,i,ai,ci);
    }
    int sum_s=0;
    int maxp=-1;
    rep(i,n){
        cin >> s[i] >> p[i];
        //~ ea.addEdge(i,sink,si,-pi);
        sum_s += s[i];
        if(maxp<p[i]) maxp=p[i];
    } 
    // now that we get maxp--> add it to all edge costs
    rep(i,n) {
        ea.addEdge(_source,i,a[i],c[i]+maxp);
        ea.addEdge(i,sink,s[i],-p[i]+maxp);
    }
    rep(i,n-1){
        cin >> vi >> ei;
        ea.addEdge(i,i+1,vi,ei);//+maxp NO!! SHOULD NOT ADD maxp TO FREEZE EDGES!!
    }
    //~ // Option 1: Min Cost Max Flow with cycle_canceling
    //~ long flow = push_relabel_max_flow(G, _source, sink);
    //~ cout << (flow==sum_s?"possible":"impossible") << ' ' << flow << ' ';
    //~ cycle_canceling(G);
    //~ long cost = find_flow_cost(G) - 3*maxp*flow;
    //~ cout << -cost << endl;
    
    // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights
    successive_shortest_path_nonnegative_weights(G, _source, sink);
    long cost = find_flow_cost(G);
    long flow = 0;
    OutEdgeIt e, eend;// Iterate over all edges leaving the source
    for(tie(e, eend) = out_edges(vertex(_source,G), G); e != eend; ++e) 
        flow += capacity[*e] - res_capacity[*e];
    cout << (flow==sum_s?"possible":"impossible") << ' ' << flow << ' ';
    cost -= flow*2*maxp; // remove added maxp for s-i, i-t edges
    // go over edges of kind i-->i+1, substract maxp accordingly ==> NO!! SHOULD NOT ADD maxp TO FREEZE EDGES!!
    int k=0;
    rep(i,n-1){
        for(tie(e, eend) = out_edges(i, G); e != eend; ++e) 
            if (target(*e,G)==(unsigned)i+1)
                k += capacity[*e] - res_capacity[*e];
    }
    //~ cost -= k*maxp;
    cout << -cost << endl;
}

int main(){
    int t;
    cin >> t;
    rep(i,t) canteen();
    return 0;
}
