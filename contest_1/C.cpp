#include <cstdint>
#include <iostream>
#include <vector>

const int cMD = 64;

int ExtractBit(uint64_t v, int p) { return ((v >> p) & 1); }

std::vector<uint64_t> SortLSD(std::vector<uint64_t>& numbers, int n,
                              int digit) {
  int count[2] = {0, 0};
  for (uint64_t& v : numbers) {
    ++count[ExtractBit(v, digit)];
  }
  count[1] += count[0];
  std::vector<uint64_t> sorted(n);
  for (int i = n - 1; i >= 0; i--) {
    sorted[--count[ExtractBit(numbers[i], digit)]] = numbers[i];
  }
  return sorted;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<uint64_t> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < cMD; i++) {
    a = SortLSD(a, n, i);
  }
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << " ";
  }
}
