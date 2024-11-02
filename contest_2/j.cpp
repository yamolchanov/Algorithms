#include <iostream>
#include <stack>
#include <string>
#include <vector>

void Push(int x, std::stack<std::pair<int, int>>& left) {
  if (left.empty()) {
    left.push({x, x});
  } else {
    int minimal = std::min(x, left.top().second);
    left.push({x, minimal});
  }
  std::cout << "ok"
            << "\n";
}

void Dequeue(std::stack<std::pair<int, int>>& left,
             std::stack<std::pair<int, int>>& right) {
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

void Front(std::stack<std::pair<int, int>>& left,
           std::stack<std::pair<int, int>>& right) {
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

void Clear(std::stack<std::pair<int, int>>& left,
           std::stack<std::pair<int, int>>& right) {
  while (!left.empty()) {
    left.pop();
  }
  while (!right.empty()) {
    right.pop();
  }
  std::cout << "ok"
            << "\n";
}

void Minimum(std::stack<std::pair<int, int>>& left,
             std::stack<std::pair<int, int>>& right) {
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

int main() {
  int n;
  std::cin >> n;
  std::string k;
  std::stack<std::pair<int, int>> left_stack;
  std::stack<std::pair<int, int>> right_stack;
  for (int i = 0; i < n; i++) {
    std::cin >> k;
    if (k == "enqueue") {
      int x;
      std::cin >> x;
      Push(x, left_stack);
    } else if (k == "dequeue") {
      Dequeue(left_stack, right_stack);
    } else if (k == "front") {
      Front(left_stack, right_stack);
    } else if (k == "size") {
      auto size = left_stack.size() + right_stack.size();
      std::cout << size << "\n";
    } else if (k == "clear") {
      Clear(left_stack, right_stack);
    } else if (k == "min") {
      Minimum(left_stack, right_stack);
    }
  }
}
