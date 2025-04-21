#include <iostream>
#include <set>
#include <vector>
const long long cNot = 2009000999;
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  int n;
  int m;
  int s;
  std::cin >> t;
  for (int z = 0; z < t; z++) {
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
      int x;
      int y;
      int w;
      std::cin >> x >> y >> w;
      g[x].push_back({y, w});
      g[y].push_back({x, w});
    }
    std::cin >> s;
    std::vector<int> d(n, cNot);
    std::vector<int> used(n, 0);
    std::set<std::pair<int, int>> q;
    d[s] = 0;
    for (int i = 0; i < n; i++) {
      q.insert({d[i], i});
    }
    for (int i = 0; i < n; i++) {
      int v = q.begin()->second;
      q.erase(q.begin());
      if (d[v] >= cNot) {
        break;
      }
      used[v] = 1;
      for (int j = 0; j < static_cast<int>(g[v].size()); j++) {
        int to = g[v][j].first;
        int len = g[v][j].second;
        if (len != -1 && d[v] + len < d[to]) {
          q.erase({d[to], to});
          d[to] = d[v] + len;
          q.insert({d[to], to});
        }
      }
    }
    for (int u : d) {
      std::cout << u << " ";
    }
  }
}
