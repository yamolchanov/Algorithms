#include <iostream>
#include <vector>

struct HashTable {
  const int cSize = 1046527;
  std::vector<std::vector<std::pair<int, int>>> a;
  HashTable() : a(cSize) {}
  int Find(const int cX) const {
    const int cKey = cX % cSize;
    int array = static_cast<int>(a[cKey].size());
    for (int i = 0; i != array; i++) {
      if (a[cKey][i].first == cX) {
        return i;
      }
    }
    return -1;
  }
  void Insert(const int cX) {
    int index = Find(cX);
    const int cKey = cX % cSize;
    if (index == -1) {
      a[cKey].emplace_back(cX, 1);
    } else {
      a[cKey][index].second++;
    }
  }

  bool Query(const int cX) {
    int index = Find(cX);
    if (index != -1 && a[cX % cSize][index].second > 0) {
      a[cX % cSize][index].second--;
      return true;
    }
    return false;
  }
};

int main() {
  HashTable hash;
  std::vector<int> result;
  int n;
  std::cin >> n;
  for (int i = 0; i != n; i++) {
    int a;
    std::cin >> a;
    hash.Insert(a);
  }
  int m;
  std::cin >> m;
  for (int i = 0; i != m; i++) {
    int x;
    std::cin >> x;
    if (hash.Query(x)) {
      result.push_back(x);
    };
  }
  const int cK = result.size();
  std::cout << cK << "\n";
  for (int i = 0; i != cK; i++) {
    std::cout << result[i] << " ";
  }
}
