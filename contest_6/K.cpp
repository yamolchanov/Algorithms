#include <iostream>
#include <vector>

void Logic(int n, std::vector<int>& indexs, int& length, std::vector<int>& last,
           std::vector<int>& a) {
  for (int i = 0; i < n; i++) {
    int low = 1;
    int high = length;
    while (low <= high) {
      int mid = (low + high) / 2;
      if (a[indexs[mid]] >= a[i]) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    int pos = low;
    last[i] = indexs[pos - 1];
    indexs[pos] = i;
    length = std::max(pos, length);
  }
  std::cout << length << "\n";
}

void Table(int length, std::vector<int>& result, int k,
           std::vector<int>& last) {
  for (int i = length - 1; i >= 0; --i) {
    result[i] = k + 1;
    k = last[k];
  }
  for (int i = 0; i < length; i++) {
    std::cout << result[i] << " ";
  }
}

int main() {
  int n;
  int length = 0;
  std::cin >> n;
  std::vector<int> a(n);
  std::vector last(n, -1);
  std::vector indexs(n + 1, -1);
  for (int i = 0; i != n; ++i) {
    std::cin >> a[i];
  }
  Logic(n, indexs, length, last, a);
  std::vector<int> result(length);
  Table(length, result, indexs[length], last);
}

