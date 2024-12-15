#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct SparseTable {
  const int cLg = 18;
  std::vector<std::vector<std::pair<int, int>>> table;

  static std::pair<int, int> FindMinPair(const std::pair<int, int>& first,
                                         const std::pair<int, int>& second,
                                         const std::vector<int>& array) {
    int indices[] = {first.first, first.second, second.first, second.second};
    int min1_index = -1;
    int min2_index = -1;
    for (int i = 0; i < 4; ++i) {
      int idx = indices[i];
      if (idx == -1) {
        continue;
      }
      if (min1_index == -1 || array[idx] < array[min1_index]) {
        min2_index = min1_index;
        min1_index = idx;
      } else if ((min2_index == -1 || array[idx] < array[min2_index]) &&
                 idx != min1_index) {
        min2_index = idx;
      }
    }
    return {min1_index, min2_index};
  }

  SparseTable(const int cN, const std::vector<int>& array) {
    table.resize(cN, std::vector<std::pair<int, int>>(cLg));
    for (int i = 0; i < cN; ++i) {
      table[i][0] = {i, -1};
    }
    for (int j = 1; j < cLg; ++j) {
      for (int i = 0; i + (1 << j) <= cN; ++i) {
        std::pair<int, int> left = table[i][j - 1];
        std::pair<int, int> right = table[i + (1 << (j - 1))][j - 1];
        table[i][j] = FindMinPair(left, right, array);
      }
    }
  }

  std::pair<int, int> Answer(const int cL, const int cR,
                             const std::vector<int>& array) const {
    int j = static_cast<int>(std::log2(cR - cL + 1));
    std::pair<int, int> left = table[cL][j];
    std::pair<int, int> right = table[cR - (1 << j) + 1][j];
    return FindMinPair(left, right, array);
  }
};

int main() {
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> array(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  SparseTable st(n, array);

  for (int i = 0; i < q; ++i) {
    int l;
    int r;
    std::cin >> l >> r;
    --l;
    --r;
    std::pair<int, int> result = st.Answer(l, r, array);
    std::cout << array[result.second] << "\n";
  }
}

