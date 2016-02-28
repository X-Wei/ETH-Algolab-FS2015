#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdio>

using namespace std;

const int MAXH=11000;

int w, w2;
int n,m;
int a,b;
int s,t;
int dis[110][110];
int father[MAXH];
int d1[MAXH];
int d2[MAXH];
int next1[MAXH];
int beg[MAXH];
int edge[MAXH];
int next2[MAXH];
int beg2[MAXH];
int edge2[MAXH];

struct node
{
    int num;
    int value;
    node() {}
    node(int x, int y) {
        num=x;value=y;
    }
    bool operator<(const node x) const {
        return (value>x.value) || (value==x.value && num>x.num);
    }
};

void add_edge(int a, int b) {
    w++; edge[w]=b; next1[w]=beg[a]; beg[a]=w;
    w2++; edge2[w2]=a; next2[w2]=beg2[b]; beg2[b]=w2;
}

void search1() {
    int t1,t2;
    node tt;
    priority_queue<node> q;

    memset(d1,-1,sizeof(d1));
    memset(father,-1,sizeof(father));
    d1[s]=0;
    father[s]=s;
    while(!q.empty()) q.pop();
    q.push(node(s,0));
    while(!q.empty()) {
        tt=q.top();
        q.pop();
        t1=tt.num;
        for(int i=beg[t1];i!=-1;i=next1[i]) {
            if(d1[edge[i]]==-1 || d1[t1]+ 1 < d1[edge[i]]) {
                d1[edge[i]]=d1[t1]+1;
                father[edge[i]]=t1;
                q.push(node(edge[i],d1[edge[i]]));
            }
        }
    }
}

void search2() {
    int t1,t2;
    node tt;
    priority_queue<node> q;

    memset(d2,-1,sizeof(d2));
    d2[t]=0;
    while(!q.empty()) q.pop();
    q.push(node(t,0));
    while(!q.empty()) {
        tt=q.top();
        q.pop();
        t1=tt.num;
        for(int i=beg2[t1];i!=-1;i=next2[i]) {
            if(d2[edge2[i]]==-1 || d2[t1]+ 1 < d2[edge2[i]]) {
                d2[edge2[i]]=d2[t1]+1;
                q.push(node(edge2[i],d2[edge2[i]]));
            }
        }
    }
}

void testcase() {
    int now, k;
    int ans;

    cin >> n >> m;
    cin >> s >> t;
    memset(dis,0,sizeof(dis));
    memset(beg,-1,sizeof(beg));
    memset(next1,-1,sizeof(next1));
    memset(edge,-1,sizeof(edge));
    memset(beg2,-1,sizeof(beg2));
    memset(next2,-1,sizeof(next2));
    memset(edge2,-1,sizeof(edge2));
    w=w2=0;
    for(int i=0;i<m;i++) {
        cin >> a >>b;
        add_edge(a,b);
        dis[a][b]=1;
    }
    search1();
    search2();
    if(d1[t]>=0) {
        k=t;
        while(s!=t) {
            now=father[k];
            dis[now][k]=0;
            if(now==s) break;
            k=now;
        }
        ans = 200000000;
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                if(dis[i][j] && d1[i]!=-1 && d2[j]!=-1 && d1[i]+d2[j]+1<ans){
                    ans=d1[i]+d2[j]+1;
                }
            }
        }
        if(ans==200000000 ) cout << "no\n"; else cout << ans << endl;
    }
    else {
        cout << "no" << endl;
    }
}

int main() {
    int T;

    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        testcase();
    }
    return 0;
}

