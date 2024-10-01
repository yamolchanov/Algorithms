#include <iostream>
#include <vector>

const int cLim = 1e7;

int BinarySearch(std::vector<std::vector<int> >& a,
                 std::vector<std::vector<int> >& b, int i, int j, int l) {
  int max = cLim;
  int left = 0;
  int right = l - 1;
  int mid;
  int answer = 0;
  while (left <= right) {
    mid = (left + right) / 2;
    if (std::max(a[i][mid], b[j][mid]) < max) {
      max = std::max(a[i][mid], b[j][mid]);
      answer = mid + 1;
    }
    if (a[i][mid] < b[j][mid]) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return answer;
}

int main() {
  int n;
  int m;
  int l;
  std::cin >> n >> m >> l;
  std::vector<std::vector<int> > a(n, std::vector<int>(l, 0));
  std::vector<std::vector<int> > b(m, std::vector<int>(l, 0));
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
  for (int w = 0; w < q; w++) {
    int i;
    int j;
    std::cin >> i >> j;
    i--;
    j--;
    std::cout << BinarySearch(a, b, i, j, l) << "\n";
  }
  return 0;
}
