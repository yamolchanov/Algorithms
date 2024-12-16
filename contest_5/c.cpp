#include <iostream>
#include <vector>

struct HashTable {
  const int cSize = 1046527;
  std::vector<std::vector<std::pair<long long, int>>> a;

  HashTable() : a(cSize) {}

  int SimpleHash(long long value) const { return value % cSize; }

  int Find(long long value) const {
    int key = SimpleHash(value);
    for (int i = 0; i < static_cast<int>(a[key].size()); ++i) {
      if (a[key][i].first == value) {
        return i;
      }
    }
    return -1;
  }

  void Insert(long long value) {
    int key = SimpleHash(value);
    int index = Find(value);
    if (index == -1) {
      a[key].emplace_back(value, 1);
    } else {
      a[key][index].second++;
    }
  }

  int Count(long long value) const {
    int key = SimpleHash(value);
    int index = Find(value);
    if (index != -1) {
      return a[key][index].second;
    }
    return 0;
  }
};

long long DistanceSquared(int x1, int y1, int x2, int y2) {
  long long dx = x1 - x2;
  long long dy = y1 - y2;
  return dx * dx + dy * dy;
}

int main() {
  int q;
  std::cin >> q;

  std::vector<std::pair<int, int>> points(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> points[i].first >> points[i].second;
  }

  long long total = 0;

  for (int i = 0; i < q; ++i) {
    HashTable hash;
    for (int j = 0; j < q; ++j) {
      if (i == j) {
        continue;
      }

      long long dist = DistanceSquared(points[i].first, points[i].second,
                                       points[j].first, points[j].second);
      total += hash.Count(dist);
      hash.Insert(dist);
    }
  }

  std::cout << total << '\n';
  return 0;
}
