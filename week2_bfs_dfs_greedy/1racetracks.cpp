#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

struct BFSNode {
	int x;
	int y;
	int vx;
	int vy;
	int steps;
};

int main() {
	int N, X, Y, x1, x2, y1, y2, P;
	cin >> N;
	rep(_,N)
	{
		cin >> X >> Y >> x1 >> y1 >> x2 >> y2;
		BFSNode start;
		start.x = x1;
		start.y = y1;
		start.vx = 0;
		start.vy = 0;
		start.steps = 0;
		// grid read
		bool obs[X][Y], visited[X][Y][7][7];// a node is uniquely defined by 4 numbers: x,y,vx,vy
		rep(i,X)
			rep(j,Y)
			{
				obs[i][j] = false;
				rep(vx,7)
					rep(vy,7)
						visited[i][j][vx][vy] = false;
			}
		cin >> P;
		rep(ii,P)
		{ // add obstacles
			int xx1, xx2, yy1, yy2;
			cin >> xx1 >> yy1 >> xx2 >> yy2;
			forloop(i,xx1,xx2)
				forloop(j,yy1,yy2)
					obs[i][j] = true;
		}
		//now do BFS
		queue<BFSNode> q;
		q.push(start);
		visited[start.x][start.y][0+3][0+3] = true;
		int best = -1;
		while (!q.empty()) {
			BFSNode nd = q.front();
			q.pop();
			if (nd.x == x2 && nd.y == y2) { //if arrived ==> over
				best = nd.steps;
				break;
			}
			//add new nodes to queue
			forloop(dvx,-1,1)
				forloop(dvy,-1,1)
				{
					BFSNode next;
					next.vx = nd.vx + dvx;
					next.vy = nd.vy + dvy;
					next.x = nd.x + next.vx;
					next.y = nd.y + next.vy;
					next.steps = nd.steps + 1;
					if (next.vx == 0 && next.vy == 0)
						continue;
					if (next.x >= 0 && next.x < X && next.y >= 0 && next.y < Y
							&& next.vx >= -3 && next.vx <= 3 && next.vy >= -3
							&& next.vy <= 3 && !obs[next.x][next.y]
							&& !visited[next.x][next.y][next.vx+3][next.vy+3]) {
						q.push(next); // add if is valid
						visited[next.x][next.y][next.vx+3][next.vy+3] = true;
					}
				} //add new nodes to queue finished
		}
		//end of BFS
		if (best >= 0)
			cout << "Optimal solution takes " << best << " hops." << endl;
		else
			cout << "No solution." << endl;
	}
	return 0;
} //main