//In The Name Of God
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;
typedef vector<vector<viii>> vvviii;
typedef vector<vector<iii>> vviii;
typedef set<int> si;
typedef vector<si> vsi;
typedef pair<double, double> dd;
typedef vector<dd> vdd;

#define inf 1000000000
#define eps 1e-9

// to find minimum cut, run flow, the max flow is the value of minimum cut, to find edges
// we put all reachable vertexes from source with positive weight to S components and all others to C
// all edges connecting S vertexes to C are in minimum edges vertexes set.

// Dinic network max flow algorithm, runs in O(V^2*E) time.
// efficient for graph with lots of edges.
// if verteces have capacity as well as edges, simply devide each vertex to two vertex with an edge between them
// equal to capacity of the vertex

vi dist, work;
int s, t, n; //fill s, t, n in main ---> s is start, t is destination and n is number of nodes in graph.
vvi rem, graph; //fill graph in main. graph is adjList. also fill rem where it keeps capacity of edjes in n * n space.
//it is possible to use rem to construct the path. if there was a path from i to j then rem[j][i] > 0
//if rem[j][i] = 0 before running Dinic's so it can change with questions...

bool dinic_bfs() {
    dist.clear(); dist.resize(n, -1); dist[s] = 0;
    queue<int> queue1; queue1.push(s);
    while(!queue1.empty()) {
        int u = queue1.front(); queue1.pop();
        for(auto &e : graph[u]) {
            if(dist[e] != -1 || rem[u][e] <= 0) continue;
            dist[e] = dist[u] + 1;
            queue1.push(e);
        }
    }
    return (dist[t] != -1);
}

int dinic_dfs(int u, int f) {
    if(u == t) return f;
    for(int &i = work[u]; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if(rem[u][v] <= 0) continue;
        if(dist[u] + 1 == dist[v]) {
            int df = dinic_dfs(v, min(f, rem[u][v]));
            if(df > 0) {
                rem[v][u] += df;
                rem[u][v] -= df;
                return df;
            }
        }
    }
    return 0;
}

int maxFlow() {
    int result = 0;
    while(dinic_bfs()) {
        work.clear(); work.resize(n, 0);
        while(int d = dinic_dfs(s, inf)) result += d;
    }
    return result;
}

int main()
{
    int e, d, tt;
    while(cin >> n >> e >> s >> d >> tt && (n || e || s || d || tt)) {
        t = d;
        s--, t--;
        graph.assign(n, vi());
        rem.assign(n, vi(n, 0));
        for(int i = 0; i < e; i++) {
            int a, b; cin >> a >> b;
            a--, b--;
            graph[a].push_back(b), graph[b].push_back(a), rem[a][b]++;
        }
        ll ways = maxFlow();
        ll a = tt / ways, b = tt % ways;
        ll ans = b * (a + 1) * pow(a + 1, 2) + (tt - b * (a + 1)) * (a * a);
        cout << ans << endl;
    }
    return 0;
}
