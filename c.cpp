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

typedef struct { int a, b, c, score; } vote;

bool comp(pair<int, vote> a, pair<int, vote> b) {
  vote v1 = a.second, v2 = b.second;
  if (v1.score > v2.score)
    return true;
  if (v1.score == v2.score && (v1.a > v2.a || (v1.a == v2.a && v1.b > v2.b) ||
                               (v1.a == v2.a && v1.b == v2.b && v1.c > v2.c)))
    return true;
  return false;
}

int main() {
  ios::sync_with_stdio(0);
  int n;
  while (cin >> n && n) {
    map<int, vote> mp;
    for (int i = 0; i < n; i++) {
      int k;
      cin >> k;
      for (int i = 0; i < k; i++) {
        int id;
        cin >> id;
        if (mp.find(id) == mp.end()) {
          vote v;
          v.a = v.b = v.c = v.score = 0;
          mp.insert(pair<int, vote>(id, v));
        }
        if (i == 0)
          mp[id].a++, mp[id].score += 3;
        else if (i == 1)
          mp[id].b++, mp[id].score += 2;
        else
          mp[id].c++, mp[id].score++;
      }
    }
    vector<pair<int, vote>> all;
    for (auto it = mp.begin(); it != mp.end(); it++) {
      all.push_back(pair<int, vote>(it->first, it->second));
    }
    sort(all.begin(), all.end(), comp);
    cout << all[0].first;
    for (int i = 1; i < all.size(); i++)
      if (all[i].second.score == all[0].second.score &&
          all[i].second.b == all[0].second.b &&
          all[i].second.a == all[0].second.a &&
          all[i].second.c == all[0].second.c)
        cout << " " << all[i].first;
    cout << endl;
  }

  return 0;
}
