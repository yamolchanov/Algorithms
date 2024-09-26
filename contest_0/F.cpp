#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  int m;
  int l;
  std::cin >> n >> m >> l;
  std::vector<std::vector<int>> a(n, std::vector<int>(l, 0));
  std::vector<std::vector<int>> b(m, std::vector<int>(l, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < l; j++) {
      std::cin >> a[i][j];
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < l; j++) {
      std::cin >> b[i][j];
    }
  }
  int q;
  std::cin >> q;
  const int cLim = 100000000;
  for (int w = 0; w < q; w++) {
    int i;
    int j;
    std::cin >> i >> j;
    i--;
    j--;
    int answer = 0;
    int maxim = cLim;
    int left = 0;
    int right = l - 1;
    int mid;
    while (left <= right) {
      mid = (left + right) / 2;
      if (std::max(a[i][mid], b[j][mid]) < maxim) {
        maxim = std::max(a[i][mid], b[j][mid]);
        answer = mid + 1;
      }
      if (a[i][mid] < b[j][mid]) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    std::cout << answer << "\n";
  }
}
