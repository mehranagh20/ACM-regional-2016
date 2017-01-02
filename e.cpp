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

int main() {
    ios::sync_with_stdio(0);
    int a, b;
    while(cin >> a >> b && (a != -1 || b != -1)) {
        vi fe(101, 0), se(101, 0), fo(101, 0), so(101, 0);
        int ff = 0, ss = 0;
        for(int i = 0; i < a; i++) {
            int tmp; cin >> tmp;
            if(tmp % 2) fo[tmp]++;
            else fe[tmp] = 1;
        }
        for(int i = 0; i < b; i++) {
            int tmp; cin >> tmp;
            if(tmp % 2) so[tmp]++;
            else se[tmp] = 1;
        }
        int firstOddNums = 0, secondOddNums = 0;
        for(auto &e : fo) if(e) firstOddNums++;
        for(auto &e : so) if(e) secondOddNums++;
        if(firstOddNums != secondOddNums) cout << "N\n";
        else {
            bool pos = true;
            for(int i = 0; i <= 100; i++) if(fo[i] != so[i]) pos = false;
            if(!pos) cout << "N\n";
            else {
                for(int i = 0; i <= 100; i += 2) if(fe[i]) {
                    if(se[i]) continue;
                    else if(so[(i - 2) / 2]) continue;
                    else pos = false;
                    break;
                }
                if(pos == false) cout << "N\n";
                else {
                    for(int i = 0; i <= 100; i += 2) if(se[i]) {
                        if(fe[i]) continue;
                        else if(fo[(i - 2) / 2]) continue;
                        else pos = false;
                        break;
                    }
                    if(pos) cout << "Y\n";
                    else cout << "N\n";
                }
            }
        }
    }

    return 0;
}
