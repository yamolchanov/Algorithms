#include <algorithm>
#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<int, int>>& a, int l, int r) {
  int m = (l + r) / 2;

  std::vector<std::pair<int, int>> temp(r - l);
  int i = l;
  int j = m;
  while (i < m && j < r) {
    if (a[i] > a[j]) {
      temp[i - l + j - m] = a[j];
      j++;
    } else {
      temp[i - l + j - m] = a[i];
      i++;
    }
  }
  while (i < m) {
    temp[i - l + j - m] = a[i];
    i++;
  }
  while (j < r) {
    temp[i - l + j - m] = a[j];
    j++;
  }
  for (int k = 0; k < r - l; k++) {
    a[k + l] = temp[k];
  }
}

void MergeSort(std::vector<std::pair<int, int>>& a, int l, int r) {
  if ((r - l) <= 1) {
    return;
  }
  int mid = (r + l) / 2;
  MergeSort(a, l, mid);
  MergeSort(a, mid, r);
  Merge(a, l, r);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> axis(n);
  for (auto& element : axis) {
    std::cin >> element.first >> element.second;
  }
  MergeSort(axis, 0, n);
  std::pair<int, int> current = axis[0];
  int ans = 1;
  std::string output;
  for (auto& e : axis) {
    if (current.second >= e.first) {
      current.second = std::max(current.second, e.second);
    } else {
      output += "\n" + std::to_string(current.first) + " " +
                std::to_string(current.second);
      current = e;
      ans++;
    }
  }
  output += "\n" + std::to_string(current.first) + " " +
            std::to_string(current.second);
  std::cout << ans << output;
}
