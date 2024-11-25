#include <iostream>
#include <stack>
#include <string>
#include <vector>

struct Deque {
  std::stack<std::pair<int, int>> left;
  std::stack<std::pair<int, int>> right;
  void Push(int x) {
    if (left.empty()) {
      left.push({x, x});
    } else {
      int minimal = std::min(x, left.top().second);
      left.push({x, minimal});
    }
    std::cout << "ok"
              << "\n";
  }

  void Dequeue() {
    if (right.empty()) {
      while (!left.empty()) {
        int element = left.top().first;
        left.pop();
        int minimal =
            right.empty() ? element : std::min(element, right.top().second);
        right.push({element, minimal});
      }
    }
    if (left.empty() && right.empty()) {
      std::cout << "error"
                << "\n";
    } else {
      int result = right.top().first;
      right.pop();
      std::cout << result << "\n";
    }
  }

  void Front() {
    if (right.empty() && left.empty()) {
      std::cout << "error"
                << "\n";
    } else if (right.empty()) {
      while (!left.empty()) {
        int element = left.top().first;
        left.pop();
        int minimal =
            right.empty() ? element : std::min(element, right.top().second);
        right.push({element, minimal});
      }
      std::cout << right.top().first << "\n";
    } else {
      std::cout << right.top().first << "\n";
    }
  }

  void Clear() {
    while (!left.empty()) {
      left.pop();
    }
    while (!right.empty()) {
      right.pop();
    }
    std::cout << "ok"
              << "\n";
  }

  void Minimum() {
    if (left.empty() && right.empty()) {
      std::cout << "error"
                << "\n";
    } else if (left.empty()) {
      std::cout << right.top().second << "\n";
    } else if (right.empty()) {
      std::cout << left.top().second << "\n";
    } else {
      std::cout << std::min(left.top().second, right.top().second) << "\n";
    }
  }

  void Size() const {
    auto size = left.size() + right.size();
    std::cout << size;
  }
};

int main() {
  int n;
  std::cin >> n;
  std::string k;
  Deque deck;
  for (int i = 0; i < n; i++) {
    std::cin >> k;
    if (k == "enqueue") {
      int x;
      std::cin >> x;
      deck.Push(x);
    } else if (k == "dequeue") {
      deck.Dequeue();
    } else if (k == "front") {
      deck.Front();
    } else if (k == "size") {
      deck.Size();
    } else if (k == "clear") {
      deck.Clear();
    } else if (k == "min") {
      deck.Minimum();
    }
  }
}
