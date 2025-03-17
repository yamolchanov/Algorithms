#include <cmath>
#include <iostream>
#include <vector>

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  --n;
  if (n == 0) {
    std::cout << 0;
  } else if (k == 0) {
    std::cout << -1;
  } else if (k >= n) {
    std::cout << static_cast<int>(std::log2(n)) + 1;
  } else {
    int zov = 0;
    std::vector<int> dp(k + 1, 0);
    while (dp[k] < n) {
      zov++;
      for (int i = k; i > 0; --i) {
        dp[i] += dp[i - 1] + 1;
      }
    }
    std::cout << zov;
  }
}
