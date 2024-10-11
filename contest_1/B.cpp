#include <algorithm>
#include <iostream>
#include <vector>

const int cN1 = 123;
const int cN2 = 45;
const int cN3 = 10000000 + 4321;

int GetMedian(std::vector<int>& a, int l, int r) {
  std::sort(a.begin() + l, a.begin() + r);
  return a[l + ((r - l - 1) / 2)];
}

int MedianMedians(std::vector<int>& a, int l, int r) {
  if (r - l <= 5) {
    return GetMedian(a, l, r);
  }
  std::vector<int> medians;
  for (int i = l; i < r; i += 5) {
    int bound = std::min(i + 5, r);
    int median = GetMedian(a, i, bound);
    medians.push_back(median);
  }
  return MedianMedians(medians, 0, medians.size());
}

std::pair<int, int> Partition(std::vector<int>& a, int l, int r, int pivot) {
  int lt = l;
  int gt = r;
  int i = l;

  while (i < gt) {
    if (a[i] < pivot) {
      std::swap(a[i], a[lt]);
      i++;
      lt++;
    } else if (a[i] > pivot) {
      gt--;
      std::swap(a[i], a[gt]);
    } else {
      i++;
    }
  }

  return {lt, gt};
}

int QuickSelect(std::vector<int>& a, int l, int r, int x) {
  if (r - l <= 1) {
    return l;
  }

  int pivot = MedianMedians(a, l, r);
  std::pair<int, int> p = Partition(a, l, r, pivot);

  if (x < p.first) {
    return QuickSelect(a, l, p.first, x);
  }
  if (x >= p.second) {
    return QuickSelect(a, p.second, r, x);
  }
  return p.first;
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  std::vector<int> a(n);
  std::cin >> a[0] >> a[1];
  for (int i = 2; i < n; i++) {
    a[i] = (a[i - 1] * cN1 + a[i - 2] * cN2) % cN3;
  }
  std::cout << a[QuickSelect(a, 0, n, k - 1)];
}

