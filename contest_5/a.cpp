#include <iostream>
#include <vector>

struct HashTable {
  const int cSize = 1046527;
  std::vector<std::vector<int>> a;
  HashTable() : a(cSize) {}
  int Find(const int cX) {
    const int cKey = cX % cSize;
    int array = static_cast<int>(a[cKey].size());
    for (int i = 0; i != array; i++) {
      if (a[cKey][i] == cX) {
        return i;
      }
    }
    return -1;
  }
  void Insert(const int cX) {
    if (Find(cX) == -1) {
      const int cKey = cX % cSize;
      a[cKey].push_back(cX);
    }
  }

  void Erase(const int cX) {
    int index = Find(cX);
    if (index != -1) {
      int xkey = cX % cSize;
      int array = a[xkey].size() - 1;
      a[xkey][index] = a[xkey][array];
      a[xkey].pop_back();
    }
  }
  void FindUser(const int cX) {
    if (Find(cX) == -1) {
      std::cout << "NO"
                << "\n";
    } else {
      std::cout << "YES"
                << "\n";
    }
  }
};

int main() {
  int q;
  std::cin >> q;
  HashTable hash;
  while (q-- != 0) {
    std::string cmd;
    std::cin >> cmd;
    int x;
    std::cin >> x;
    if (cmd == "+") {
      hash.Insert(x);
    } else if (cmd == "-") {
      hash.Erase(x);
    } else {
      hash.FindUser(x);
    }
  }
}
