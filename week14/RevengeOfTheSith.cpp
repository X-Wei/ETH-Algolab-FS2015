// binary search for largest possible k: in each step use the last n-k points
// to build a delauney triangualtion, dfs the size of the largest connected
// component of the triangulation, if this is larger than k, then the current
// k is acceptable.

#include <vector>
#include <iostream>
using namespace std;

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
//#include <CGAL/Triangulation_face_base_with_info_2.h>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
using namespace boost;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Finite_faces_iterator FaceIt;
typedef Triangulation::Finite_vertices_iterator VertexIt;
typedef Triangulation::Vertex_circulator VertexCir;
typedef Triangulation::Vertex_handle VertexH;

int n;
long long r;
int component[30000];
pair< K::Point_2, int > p[30001];

// find the size of the largest component in the triangualtion
int dfs(Triangulation & t, VertexH it){
	int num = 1;
	VertexCir cir = t.incident_vertices(it);
	do {
		if(!t.is_infinite(cir)){
			if(CGAL::squared_distance(cir->point(), it->point()) <= r){
				if(component[cir->info()] == -1){
					component[cir->info()] = component[it->info()];
					num += dfs(t, cir);
				}
			}
		}
	} while(++cir != t.incident_vertices(it));
	return num;
}

int main(){
	int T;
	cin >> T;
	while(T --){
		cin >> n >> r;
		r = r*r;
		int x, y;
		for(int i=0; i<n; ++i){
			cin >> x >> y;
			p[i] = make_pair(K::Point_2(x, y), i);
		}
		
		if(r == 0){
			cout << 1 << endl;
			continue;
		}
		
		int left = 1;
		int right = n/2;
		while(left != right){
			int mid = (right+1+left)/2;
			Triangulation t;
			t.insert(p+mid, p+n);
			
			for(int i=mid; i<n; ++i){
				component[i] = -1;
			}
			int label = 0;
			int maxcomp = 1;
			VertexIt vb, ve = t.finite_vertices_end();
			for(vb=t.finite_vertices_begin(); vb!=ve; ++vb){
				if(component[vb->info()] == -1){
					component[vb->info()] = label++;
					int num = dfs(t, vb);
					if(num > maxcomp){
						maxcomp = num;
					}
				}
			}
			if(maxcomp >= mid) left = mid;
			else right = mid-1;
		}
		
		cout << left << endl;
	}
	return 0;
}
