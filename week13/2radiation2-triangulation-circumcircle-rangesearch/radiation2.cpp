/* 
 * Algorithm Lab
 * Daniel Yu
 * Exercise 12 - Radiation 2
 */

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/range_search_delaunay_2.h>
#include <CGAL/enum.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef K::Point_2 P;
typedef K::Circle_2 C;

void testcase()
{
    int h,c;cin >> h >> c;// Read h and c
    // Read the healthy cells
    vector<P> cellList;
    for (int i=0; i<h; i++){
        P cell; cin >> cell;
        cellList.push_back(cell); }
    // Build the Delaunay Graph
    Triangulation th;
    th.insert(cellList.begin(), cellList.end());
    // Read the cancer cells
    vector<P> cancerList;
    for (int i=0; i<c; i++){
        P cancer; cin >> cancer;
        cancerList.push_back(cancer);  }
    // Build the Delaunay Graph
    Triangulation tc;
    tc.insert(cancerList.begin(), cancerList.end());
    // Index all the Faces
    int index = 0;
    for (Face_iterator f = th.finite_faces_begin(); f != th.finite_faces_end(); ++f) {
        f -> info() = index;
        index++;
    }
    // Build all the circles for each face
    vector<C> circleList(index);
    for (Face_iterator f = th.finite_faces_begin(); f != th.finite_faces_end(); ++f) {
        C circle(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
        circleList[f->info()] = circle;
    }
    // Foreach circumCircle do a range search
    int maximum = 0;
    vector<vector<P> > facePointList(index);
    for (Face_iterator f = th.finite_faces_begin(); f != th.finite_faces_end(); ++f) {
        C circle = circleList[f->info()];
        // Range search
        vector<Vertex_handle> outputList;
        CGAL::range_search(tc, circle, back_inserter(outputList)); 
        // Test for each vertex, if it is not on the circle edge
        vector<P> pointList;
        for (int i=0; i<outputList.size(); i++){
            P &current_point = outputList[i] -> point();
            if (!circle.has_on_boundary(current_point)) {
                pointList.push_back(current_point);
            }
        }
        // save the pointList
        sort(pointList.begin(), pointList.end());
        facePointList[f->info()] = pointList;
        // Update the maximum
        int size = pointList.size();
        maximum = max(maximum, size);
    }

    for (int s=0; s<facePointList.size(); s++){
        for (int t=0; t<facePointList[s].size(); t++){
            cout << facePointList[s][t] << ", ";
        }
        cout << endl;
    }
    // Foreach face, generate all the candidate Circle
    vector<C> candidateCircleList;
    for (Face_iterator f = th.finite_faces_begin(); f != th.finite_faces_end(); ++f) {
        int current_face = f -> info();
        // loop for each edge
        for (int k=0; k<3; k++){
            if (th.is_infinite(f->neighbor(k))){
                continue;  }
            int neighbor_face = f->neighbor(k) -> info();
            P p1 = f->vertex(k+1%3) -> point();
            P p2 = f->vertex(k+2%3) -> point();
            // Calculate the difference point set
            vector<P> diff(facePointList[current_face].size());
            vector<P>::iterator it;
            it = set_difference(facePointList[current_face].cbegin(), facePointList[current_face].cend(),
                            facePointList[neighbor_face].cbegin(), facePointList[neighbor_face].cend(), 
                            diff.begin());
            diff.resize(it-diff.begin());
            // For each of these point, create a candidate circle
            for (int j=0; j<diff.size(); j++){
                P current_point = diff[j];
                C candidate_circle (p1, p2, current_point);
                candidateCircleList.push_back(candidate_circle);
            }
        }
    }
    // Do a range search foreach candidate Circle
    for (int i=0; i<candidateCircleList.size(); i++){
        C circle = candidateCircleList[i];
        // Range search
        vector<Vertex_handle> outputList;
        cout << "Start rangeSearch" << endl;
        CGAL::range_search(tc, circle, inserter(outputList, outputList.begin())); 
        cout << "rangeSearch end" << endl;
        // Test for each vertex, if it is on the circle edge
        vector<P> pointList;
        for (int j=0; j<outputList.size(); j++){
            P &current_point = outputList[j] -> point();
            if (!circle.has_on_boundary(current_point)) {
                pointList.push_back(current_point);
            }
        }
        // Update the maximum
        int size =  pointList.size();
        maximum = max(maximum, size);
    }
    cout << maximum << endl;
}

int main (void) {
    // Optimization
    std::ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--)
        testcase();
    
    return 0;
}
