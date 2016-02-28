#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define forloop(i,lo,hi) for(int i = (lo); i <= (hi); i++)
#define rep(i,N) forloop(i,0,N-1)

int main() {
    int N, n, m, s, t, si, ti;
    cin >> N;
    rep(_,N)
    {
        cin >> n >> m >> s >> t;
        int dist_from_s[n + 1], dist_to_t[n + 1];
        bool edge[n + 1][n + 1];
        forloop(i,1,n)
        {
            dist_from_s[i] = -1;
            dist_to_t[i] = -1;
            forloop(j,1,n)
                edge[i][j] = false;
        }
        rep(_2,m)
        {
            cin >> si >> ti;
            edge[si][ti] = 1;
        } //edges read

        // BFS 1: from s to t
        dist_from_s[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int nd = q.front();
            q.pop();
            forloop(next,1,n)
            {
                if (dist_from_s[next] == -1 && edge[nd][next]) {
                    dist_from_s[next] = dist_from_s[nd] + 1;
                    q.push(next);
                }
            } // add all outgoing edges
        } //BFS 1 over
        if (dist_from_s[t] == -1) { //if t not reachable from s
            cout << "no" << endl;
            continue;
        }
//		cout << "shortest = " << dist_from_s[t] << endl;
        // BFS 2: from t to s
        dist_to_t[t] = 0;
        queue<int> q2;
        q2.push(t);
        while (!q2.empty()) {
            int nd = q2.front();
            q2.pop();
            forloop(next,1,n)
            {
                if (dist_to_t[next] == -1 && edge[next][nd]) {
                    dist_to_t[next] = dist_to_t[nd] + 1;
                    q2.push(next);
                }
            }		// add all outgoing edges
        }		// BFS 2 over

        // loop through all edges and get the second shortest path
        int res = 99999999;
        int cnt = 0;
        forloop(i,1,n)
            forloop(j,1,n)
            {
                if (dist_from_s[i] > -1 && dist_to_t[j] > -1 && edge[i][j]) {
                    if (dist_from_s[i] + dist_to_t[j] + 1 > dist_from_s[t]
                            && res > dist_from_s[i] + dist_to_t[j] + 1)
                        res = dist_from_s[i] + dist_to_t[j] + 1;
                    if (dist_from_s[i] + dist_to_t[j] + 1 == dist_from_s[t])
                        cnt++;
                }

            }		// all edges looped
        if (cnt > dist_from_s[t])		// if exists >1 unique shortest paths
            cout << dist_from_s[t] << endl;		//res = dist1[t];
        else if (res == 99999999) {
            cout << "no" << endl;		//res = dist1[t];
        } else
            cout << res << endl;
    } //rep N
    return 0;
} //main

// ex1.
struct BFSNode {
    int x;
    int y;
    int vx;
    int vy;
    int steps;
};

void racetracks() {
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
        bool obs[X][Y], visited[X][Y][7][7]; // a node is uniquely defined by 4 numbers: x,y,vx,vy
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
        visited[start.x][start.y][0 + 3][0 + 3] = true;
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
                            && !visited[next.x][next.y][next.vx + 3][next.vy + 3]) {
                        q.push(next); // add if is valid
                        visited[next.x][next.y][next.vx + 3][next.vy + 3] =
                                true;
                    }
                } //add new nodes to queue finished
        }
        //end of BFS
        if (best >= 0)
            cout << "Optimal solution takes " << best << " hops." << endl;
        else
            cout << "No solution." << endl;
    }
}

// ex2.
struct Boat {
    int len; //length
    int pos; //position of ring
};

bool sortByPos(const Boat &lhs, const Boat &rhs) {
    return lhs.pos < rhs.pos;
}

void boat() {
    int t, N;
    cin >> t;

    rep(_,t)
    {
        cin >> N;
        vector<Boat> boats;
        rep(__,N)
        {
            Boat b;
            cin >> b.len >> b.pos;
            boats.push_back(b);
        }
        sort(boats.begin(), boats.end(), sortByPos); //sort boats by their position
        int frontier = boats[0].pos, nb = 1; //first boat is placed
        forloop(i,1,N-1)
        {
            Boat bi = boats[i];
            if (frontier > bi.pos)
                continue; // if the next boat can never fit with the current frontier: pass
            // we know that boats[i].pos is to the right of thr frontier
            if (bi.pos - bi.len >= frontier) {
                nb++;		//if the ith boat can align to left most: very good
                frontier = bi.pos;
            } else {//else, we are obliged to adjust the boat a little to right
                // if we could abondon the current boat and use a next boat?
                bool flag = false;
                int ipos = frontier + bi.len;//boat i's rear position after adjustment
                forloop(j,i+1,N-1)
                {
                    Boat bj = boats[j];
                    if (bj.pos - bj.len >= ipos)
                        break;
                    int jpos =
                            bj.pos - bj.len < frontier ?
                                    frontier + bj.len : bj.pos;	// j's rear position
                    if (ipos > jpos) {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    continue;		//if it's better use another boat after i
                nb++;		// if not, we put the boat i
                frontier += bi.len;		//frontier changed
            }
        }
        cout << nb << endl;
    }
}

// ex3.
struct Interval {
    int left;
    int right;
};

bool compInterval(const Interval &lhs, const Interval &rhs) {
    if (lhs.left != rhs.left)
        return lhs.left < rhs.left; // return the one to the left
    else
        return lhs.right > rhs.right;
} // trick: if the left edge is the same, the longest will be put first

void alien() {
    int t, n, m;
    cin >> t;
    rep(_,t)
    {
        cin >> n >> m;
        vector<Interval> aliens; // left and right position of each interval
        //0. read each alien's interval
        rep(i,n)
        {
            Interval itv;
            cin >> itv.left >> itv.right;
            if (itv.left != 0)
                aliens.push_back(itv);
        }
        sort(aliens.begin(), aliens.end(), compInterval);
        // intervals read, and sorted by left position, now do calculations
        int sz = aliens.size();
        //		forloop(i,0,sz-1)
        //			cout << aliens[i].left << ' ' << aliens[i].right << endl;
        bool flag0 = false;
        //1. see if there exist human that are not wounded by any alien
        if (sz == 0 || aliens[0].left > 1)
            flag0 = true;
        else {
            int frontier = aliens[0].right;
            forloop(i,1,sz-1)
            { // look at each interval, if they can not cover [1,m]: answer is 0
                Interval ai = aliens[i];
                if (ai.left > frontier + 1 || frontier == m)
                    break;
                else
                    frontier = frontier >= ai.right ? frontier : ai.right;
            }
            flag0 = (frontier < m); //if frontier<m: threre are 0 bragging aliens
        }
        if (flag0) // if there is a human not wounded by any alien --> 0
            cout << 0 << endl;
        else {
            // 2. count bragging aliens
            int nb = 0;
            int frontier = 0;
            // def frontier:= the right most for all intervals that start in [1, ai.left)
            for (int i = 0; i < sz;) {
                /*invariant: each time we enter this loop, we get a different `ai.left`*/
                int ll = aliens[i].left, rr = aliens[i].right;
                /* among all intervals starting at ll,
                 only this [ll, rr] COULD be a bragging alien*/
                if (rr > frontier) { //if ai=[ll, rr] is defining a new frontier
                    frontier = rr;
                    int cnt = 0; // count nb of intervals [ll, rr]
                    for (;
                            i < sz && aliens[i].right == rr
                                    && aliens[i].left == ll; i++)
                        cnt++;
                    if (cnt == 1)
                        nb++; // if we only get one [ll,rr], then it's a bragging interval
                }
                while (i < sz && aliens[i].left == ll)
                    i++; // all other aliens starting at ai.left cannot be bragging
            } //examine all aliens
            cout << nb << endl;
        } //else

    }
}
