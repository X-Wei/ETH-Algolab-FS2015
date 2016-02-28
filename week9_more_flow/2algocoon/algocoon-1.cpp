//
//  main.cpp
//  AlgoLab
//
//  Created by Nicolas Kick on 17.09.15.
//  Copyright © 2015 Nicolas Kick. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t, long, property<edge_residual_capacity_t, long, property<edge_reverse_t, adjacency_list_traits<vecS, vecS, directedS>::edge_descriptor>>>> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef property_map<Graph, edge_capacity_t>::type CapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseMap;

struct EdgeAdder {
    Graph &G;
    CapacityMap &capacity;
    ResidualCapacityMap &residualCapacity;
    ReverseMap &reverse;
    
    void addEdge(long from, long to, long c) {
        Edge e,revE;
        tie(e, tuples::ignore)=add_edge(from, to, G);
        tie(revE, tuples::ignore)=add_edge(to, from, G);
        capacity[e]=c;
        capacity[revE]=0;
        reverse[e]=revE;
        reverse[revE]=e;
    }
};

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    int T;
    cin>>T;
    for (int _t=0; _t<T; _t++) {
        int n,m;
        cin>>n>>m;
        Graph G(n);
        CapacityMap capacity=get(edge_capacity, G);
        ResidualCapacityMap residualCapacity=get(edge_residual_capacity, G);
        ReverseMap reverse=get(edge_reverse, G);
        EdgeAdder ea={G, capacity, residualCapacity, reverse};
        for (int i=0; i<m; i++) {
            int a,b,c;
            cin>>a>>b>>c;
            ea.addEdge(a, b, c);
        }
        long minCost=LONG_MAX;
        vector<Vertex> bestVertices;
        Vertex s=0;
        for (Vertex t=s+1; t<n; t++) {
            long cost=edmonds_karp_max_flow(G, s, t);
            vector<Vertex> vertices;
            vertices.push_back(s);
            vector<bool> visited=vector<bool>(n, false);
            visited[s]=true;
            for (int i=0; i<vertices.size(); i++) {
                Vertex &u=vertices[i];
                OutEdgeIterator eit,eend;
                for (tie(eit, eend)=out_edges(u, G); eit!=eend; eit++) {
                    Vertex v=target(*eit, G);
                    if (residualCapacity[*eit]>0 && !visited[v]) {
                        visited[v]=true;
                        vertices.push_back(v);
                    }
                }
            }
            long cost2=0;
            vector<Vertex> vertices2;
            for (Vertex u=0; u<n; u++) {
                if (!visited[u]) {
                    vertices2.push_back(u);
                    OutEdgeIterator eit,eend;
                    for (tie(eit, eend)=out_edges(u, G); eit!=eend; eit++) {
                        Vertex v=target(*eit, G);
                        if (visited[v]) {
                            cost2+=capacity[*eit];
                        }
                    }
                }
            }
            if (cost<minCost && cost<cost2) {
                minCost=cost;
                bestVertices=vertices;
            } else if (cost2<minCost) {
                minCost=cost2;
                bestVertices=vertices2;
            }
        }
        cout<<minCost<<endl<<bestVertices.size();
        for (int i=0; i<bestVertices.size(); i++) {
            cout<<" "<<bestVertices[i];
        }
        cout<<endl;
    }
    
    return 0;
}