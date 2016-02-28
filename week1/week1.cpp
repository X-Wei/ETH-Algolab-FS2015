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

int main1() {
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

void evenPairs() {
    int n, t;
    cin >> n;
    int nEven = 0, nOdd = 0, ret = 0, sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> t;
        sum += t;
        if (sum % 2 == 0) {
            nEven++;
            ret += nEven;
        } else {
            ret += nOdd;
            nOdd++;
        }
    }

    cout << ret;
}

void buildSum() {
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> m;
        float s = 0, t;
        for (int j = 0; j < m; j++) {
            cin >> t;
            s += t;
        }
        cout << s << endl;
    }
}

void evenMatrices() {
    int t, n;
    cin >> t;
    for (int k = 0; k < t; k++) {
        cin >> n;
        // I should have used x[n+1][n+1] !...
        int E[n + 1][n + 1], O[n + 1][n + 1], S[n + 1][n + 1], ret = 0;
        // def: Eij = nb of even values for squares at col[i,j] (i<=j) from row 1 to current row
        // def: Sij = sum of the square at col [i,j] from row 1 to current row
        for (int i = 0; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                E[i][j] = 0;
                O[i][j] = 0;
                S[i][j] = 0;
            }		//initialize arrays
        for (int i = 1; i <= n; i++) {
            int linS[n + 1], tmp = 0;
            linS[0] = 0;
            for (int j = 1; j <= n; j++) {
                cin >> tmp;
                linS[j] = linS[j - 1] + tmp;
            } // the i-th row is read
            for (int i2 = 1; i2 <= n; i2++) //find all pairs [i2,j2] (i2<=j2) in i-th row
                for (int j2 = i2; j2 <= n; j2++) {
                    S[i2][j2] += (linS[j2] - linS[i2 - 1]);
                    if (S[i2][j2] % 2 == 0) {
                        E[i2][j2]++;
                        ret += E[i2][j2];
                    } else {
                        ret += O[i2][j2];
                        O[i2][j2]++;
                    }
                }
        } //for i
        cout << ret << endl;
    }
}

void shelves() {
    int N, l, m, n;
    cin >> N;
    forloop(_,1,N)
    {
        cin >> l >> m >> n; // m <= n <= l
        int nbLong = l / n, nbShort = (l % n) / m;
        int mingap = (l % n) % m;
        for (int i = 1; i <= (l / n) && (i * n) % m != 0 && mingap > 0; i++) {
            int nbl = l / n - i, nbs = (l - n * nbl) / m;
            int gap = (l - n * nbl) % m;
            if (gap < mingap) {
                mingap = gap;
                nbLong = nbl;
                nbShort = nbs;
            }
        }
        cout << nbShort << ' ' << nbLong << ' ' << mingap << endl;
    }
}

void dominoes() {
    std::ios_base::sync_with_stdio(false);
    int N, n;
    cin >> N;
    for (int k = 0; k < N; k++) {
        cin >> n;
        int tmp, max = 1, res = n;
        bool flag = false; //flag indicating whether the res is found
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            if (max <= i && !flag) {
                res = i;
                flag = true;
            }
            if (i + tmp > max)
                max = i + tmp;
        }
        cout << res << endl;
    }
}

set<int> set_diff(set<int> s1, set<int> s2) {
    set<int> tmp;
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
            inserter(tmp, tmp.end()));
    return tmp;
}

void falsecoin() {
    std::ios_base::sync_with_stdio(false);
    int N, n, k;

    cin >> N;
    rep(_,N)
    {
        bool flag = false;
        cin >> n >> k; // n coins and k weighings
        set<int> bigger, smaller, all; //bigger, smaller contains all numbers that could be abnormal
        forloop(i,1,n)
        {
            bigger.insert(i);
            smaller.insert(i);
            all.insert(i);
        }
        rep(_2,k)
        {
            int pi;
            cin >> pi;

            int l, r;
            if (flag) {
                rep(j,pi*2+1)
                    cin >> l;
                continue;
            }
            set<int> left, right;
            set<int> used;
            rep(j,pi)
            {
                cin >> l;
                left.insert(l);
                used.insert(l);
            }
            rep(j,pi)
            {
                cin >> r;
                right.insert(r);
                used.insert(r);
            }
            char res;
            cin >> res;

            if (res == '=') { //equal
                smaller = set_diff(smaller, used);
                bigger = set_diff(bigger, used);
            } else { //not equal
                set<int> notused = set_diff(all, used);
                smaller = set_diff(smaller, notused);
                bigger = set_diff(bigger, notused);
                if (res == '>') {
                    smaller = set_diff(smaller, left);
                    bigger = set_diff(bigger, right);
                } else {
                    smaller = set_diff(smaller, right);
                    bigger = set_diff(bigger, left);
                }
            }
            if (smaller.size() + bigger.size() == 1)
                flag = true;
        } //rep(_2,k)
          //**outputting results**
        if (smaller.size() + bigger.size() == 1) {
            set<int>::iterator it;
            for (it = bigger.begin(); it != bigger.end(); it++)
                cout << *it << endl;
            for (it = smaller.begin(); it != smaller.end(); it++)
                cout << *it << endl;
        } else
            cout << 0 << endl;
    } // rep(_,N) reading the weighings
}

void falsecoin1() {
    std::ios_base::sync_with_stdio(false);
    int N, n, k;

    cin >> N;
    rep(_,N)
    {
        cin >> n >> k; // n coins and k weighings
        int eq[n + 1], lt[n + 1], gt[n + 1];
        set<int> all; //bigger, smaller contains all numbers that could be abnormal
        forloop(i,1,n)
            all.insert(i);
        forloop(i,1,n)
        {
            eq[i] = 0;
            lt[i] = 0;
            gt[i] = 0;
        }
        rep(_2,k)
        {
            int pi;
            cin >> pi;

            int left[pi], right[pi];
            rep(j,pi)
                cin >> left[j];
            rep(j,pi)
                cin >> right[j];
            char res;
            cin >> res;
            if (res == '=') { //equal
                rep(j,pi)
                {
                    eq[left[j]] = 1;
                    eq[right[j]] = 1;
                }
            } else { //not equal
                rep(j,pi)
                {
                    all.erase(left[j]);
                    all.erase(right[j]);
                } //now `all` contains all numbers that are not used
                set<int>::iterator it;
                for (it = all.begin(); it != all.end(); it++)
                    eq[*it] = 1;

                if (res == '>') {
                    rep(j,pi)
                    {
                        gt[left[j]]++;
                        lt[right[j]]++;
                    }
                } else {
                    rep(j,pi)
                    {
                        lt[left[j]]++;
                        gt[right[j]]++;
                    }
                }
            }
        } //rep(_2,k)
          //**outputting results**
        int mx = -999, mxn, ret;
        forloop(i,1,n)
        {
            if (eq[i] == 0 && lt[i] * gt[i] == 0) {
                int cnt = lt[i] == 0 ? gt[i] : lt[i];
                if (mx == cnt)
                    mxn++;
                else if (mx < cnt) {
                    mx = cnt;
                    ret = i;
                    mxn = 1;
                }
            }

        }
        if (mxn > 1)
            cout << 0 << endl;
        else
            cout << ret << endl;
    } // rep(_,N) reading the weighings
}
