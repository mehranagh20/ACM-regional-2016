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

vector<pair<double, int>> elec;
int need;
vvd memo;

double sol(int id, int total) {
    if(id == elec.size())
        if(total >= need) return 1;
        else return 0;
    double &ans = memo[id][total];
    if(ans != inf) return ans;
    ans = 0;
    ans = elec[id].first * sol(id + 1, total + elec[id].second);
    ans += (1 - elec[id].first) * sol(id + 1, total);
    return ans;


}

int main() {
    ios::sync_with_stdio(0);
    int n;
    while(cin >> n && n) {
        elec.clear(); elec.resize(n);
        need = 0;
        for(int i = 0; i < n; i++){
            cin >> elec[i].first >> elec[i].second;
            need += elec[i].second;
        }
        memo.clear();
        memo.resize(n + 1, vd(need + 10, inf));
        need /= 2; need++;
        cout << fixed << setprecision(4) << sol(0, 0) << endl;

    }

    return 0;
}
