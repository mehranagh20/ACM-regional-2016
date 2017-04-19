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


// finding Strongly Connected Components.
// numSCC holds the number of strongly connected components
// fill AdjList with the graph before running tarjanSCC alg.

vi dfs_num, dfs_low, S, visited, nodesSccNum;
vvi scc;
int dfsNumberCounter, numSCC;
vvii AdjList, revGraph;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
    S.push_back(u); // stores u in a vector based on order of visitation
    visited[u] = 1;
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
        ii v = AdjList[u][j];
        if (dfs_num[v.first] == 0)
            tarjanSCC(v.first);
        if (visited[v.first])
            dfs_low[u] = min(dfs_low[u], dfs_low[v.first]); }
    if (dfs_low[u] == dfs_num[u]) { // if this is a root (start) of an SCC
        numSCC++;
        while (1) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
            scc[numSCC].push_back(v), nodesSccNum[v] = numSCC;
            if (u == v) break; }
    } }

void dfs(vi &vis, int i, vvii &graph) {
    vis[i] = 1;
    for(auto &e : graph[i]) if(!vis[e.first])
        dfs(vis, e.first, graph);
}

// inside int main()
// for every nodes in every strongly connected component, check to see if there are more than 1 edge
// from that node to nodes to the same SCC, if there is then if just a single one comes to this SCC then
// it cause switches in this SCC to have infinite memory(hard to explain why, think about it :)) so every node that can send info to this SCC
// counts as answer(found by dfs)
// there is a special case were two different SCC make memory of some switches infinite, i marked code that check this special case.

int main() {
    ios::sync_with_stdio(0);
    int n, m;
    while(cin >> n >> m && (n || m)) {
        AdjList.assign(n, vii()), revGraph.assign(n, vii());
        nodesSccNum.assign(n, 0);
        scc.assign(n + 10, vi());
        for(int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            a--, b--;
            AdjList[a].push_back(ii(b, 0)), revGraph[b].push_back(ii(a, 0));
        }
        dfs_num.assign(n, 0); dfs_low.assign(n, 0); visited.assign(n, 0);
        dfsNumberCounter = numSCC = 0;
        for (int i = 0; i < n; i++)
            if (dfs_num[i] == 0)
                tarjanSCC(i);
        vi availables(n, 0);
        for(auto &e : scc) {
            for(auto &ee : e) {
                int num = 0;
                for(auto &u : AdjList[ee])
                    num += (nodesSccNum[u.first] == nodesSccNum[ee]);
                if(num > 1) {
                    dfs(availables, e[0], revGraph);
                    break;
                }
                // special case, two different SCC, one cause another to have infinite memory
                else if(e.size() > 1) {
                    vi tempVis(n, 0);
                    dfs(tempVis, e[0], revGraph);
                    for(auto &otherSccs : scc) if(otherSccs.size() > 1 && otherSccs != e) // > 1 means it can hold the one for ever.
                        if(tempVis[otherSccs[0]])
                            dfs(availables, otherSccs[0], revGraph); // found a scc that can cause this scc e to have infinite memory
                                                                    // so everty node that can reach that scc can cause this scc e to have infinite memory.
                }
            }
        }
        int ans = 0;
        for(auto &e : availables) ans += e;
        cout << ans << endl;
    }
}
