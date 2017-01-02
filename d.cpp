// In The Name Of God
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

// make graph of of 1 ... n
// i has an edge to j if i has to be before j, so if i
// came before j in more than k / 2 of cases then there is an edge from i to j
// skip the case that k is even and i has been before j in exactly k / 2 of cases (why? think :))
// use topological sort to create the answer.

int main() {
    ios::sync_with_stdio(0);

    int n, k, tc = 0;
    while (cin >> n >> k && (n || k)) {
        tc++;
        vi indegree(n + 10, 0), vis(n + 10, 0);
        int need = k / 2 + 1;
        vvi indices(k + 10, vi(n + 10, 0)), all(n, vi(n, 0));
        vvi graph(n + 10);
        for (int i = 0; i < k; i++)
            for (int j = 0; j < n; j++) {
                int tmp;
                cin >> tmp;
                indices[i][tmp - 1] = j;
            }
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
                for (int d = 0; d < k; d++)
                    if(indices[d][i] < indices[d][j]) all[i][j]++;
            }

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int sum = all[i][j];
//                if(sum == need) {
//                    bool found = false;
//                    for(int d = 0; d < n; d++) {
//                        if(d == j || d == i) continue;
//                        if(all[j][d] > need && all[d][i] > need) found = true;
//                    }
//                    if(found) graph[j].push_back(i), indegree[i]++;
//                    else graph[i].push_back(j), indegree[j]++;
//                }
                if(k % 2 == 0 && sum == k / 2) continue;
                if(sum >= need) graph[i].push_back(j), indegree[j]++;
                else if (sum < need) graph[j].push_back(i), indegree[i]++;
            }

        vi ts;
        std::priority_queue<int, std::vector<int>, std::greater<int>> pQueue;
        for (int i = 0; i < n; i++)
            if (!indegree[i])
                pQueue.push(i);
        while (!pQueue.empty()) {
            int top = pQueue.top();
            pQueue.pop();
            vis[top] = 1;
            ts.push_back(top);
            for (auto &e : graph[top]) {
                if (vis[e])
                    continue;
                indegree[e]--;
                if (!indegree[e])
                    pQueue.push(e);
            }
        }

        if (ts.size() != n)
            cout << "No solution\n";
        else {
            cout << ts[0] + 1;
            for (int i = 1; i < n; i++)
                cout << " " << ts[i] + 1;
            cout << endl;
        }
    }
    
    return 0;
}
