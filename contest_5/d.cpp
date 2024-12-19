#include <cmath>
#include <iostream>
#include <vector>

struct HashTable {
  const int cSize = 1046527;
  std::vector<std::vector<std::pair<long long, int>>> a;
  std::vector<long long> keys;

  HashTable() : a(cSize) {}

  [[nodiscard]] int HashKey(long long key) const {
    return static_cast<int>((key % cSize + cSize) % cSize);
  }

  int Find(long long key) {
    int h = HashKey(key);
    for (int i = 0; i < static_cast<int>(a[h].size()); ++i) {
      if (a[h][i].first == key) {
        return i;
      }
    }
    return -1;
  }

  void Insert(long long key) {
    int h = HashKey(key);
    int idx = Find(key);
    if (idx == -1) {
      a[h].emplace_back(key, 1);
      keys.push_back(key);
    } else {
      a[h][idx].second++;
    }
  }

  int Get(long long key) {
    int h = HashKey(key);
    int idx = Find(key);
    if (idx == -1) {
      return 0;
    }
    return a[h][idx].second;
  }

  void Clear() {
    for (long long key : keys) {
      int h = HashKey(key);
      a[h].clear();
    }
    keys.clear();
  }
};

int main() {
  int n;
  int t;
  std::cin >> n >> t;
  std::vector<std::pair<int, int>> points(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> points[i].first >> points[i].second;
  }

  if (t == 2) {
    std::cout << 0 << std::endl;
    return 0;
  }

  long long result = 0;
  HashTable hash;

  for (int i = 0; i < n; ++i) {
    hash.Clear();
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      long long dx = points[i].first - points[j].first;
      long long dy = points[i].second - points[j].second;
      long long dist = (dx * dx) + (dy * dy);
      hash.Insert(dist);
    }

    for (long long key : hash.keys) {
      long long count = hash.Get(key);
      result += count * (count - 1) / 2;
    }
  }

  std::cout << result << "\n";
}
