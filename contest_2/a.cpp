#include <algorithm>
#include <iostream>
#include <vector>

const long long cMaxQ = 1e6 + 2;

long long n = 0;
std::vector<long long> tree(cMaxQ);
std::vector<long long> position(cMaxQ);
std::vector<long long> ind(cMaxQ);

void Swap(long long v, long long u) {
  std::swap(tree[v], tree[u]);
  std::swap(position[ind[v]], position[ind[u]]);
  std::swap(ind[v], ind[u]);
}

void SiftUp(long long v) {
  if (v == 1) {
    return;
  }
  if (tree[v / 2] > tree[v]) {
    Swap(v / 2, v);
    SiftUp(v / 2);
  }
}

void SiftDown(long long v) {
  if (v * 2 > n) {
    return;
  }
  long long u = v * 2;
  if (v * 2 + 1 <= n && tree[v * 2] > tree[v * 2 + 1]) {
    u = v * 2 + 1;
  }
  if (tree[u] < tree[v]) {
    Swap(u, v);
    SiftDown(u);
  }
}

long long GetMin() {
  if (n == 0) {
    return -1;
  }
  return tree[1];
}

void Insert(long long x, long long i) {
  n++;
  tree[n] = x;
  position[i] = n;
  ind[n] = i;
  SiftUp(n);
}

void ExtractMin() {
  if (n == 0) {
    return;
  }
  Swap(1, n);
  n--;
  SiftDown(1);
}

void DecreaseKey(long long i, long long delta) {
  long long pos = position[i];
  tree[pos] -= delta;
  SiftUp(pos);
}

int main() {
  long long q;
  std::cin >> q;

  for (long long i = 1; i <= q; i++) {
    std::string command;
    std::cin >> command;

    if (command == "insert") {
      long long x;
      std::cin >> x;
      Insert(x, i);
    } else if (command == "getMin") {
      std::cout << GetMin() << "\n";
    } else if (command == "extractMin") {
      ExtractMin();
    } else if (command == "decreaseKey") {
      long long idx;
      long long delta;
      std::cin >> idx >> delta;
      DecreaseKey(idx, delta);
    }
  }

  return 0;
}
