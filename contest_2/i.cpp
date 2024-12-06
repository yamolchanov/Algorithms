#include <deque>
#include <iostream>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::deque<int> d;
  for (int i = 0; i < n; i++) {
    std::string call;
    std::cin >> call;
    if (call == "+") {
      int element;
      std::cin >> element;
      d.push_back(element);
    } else if (call == "-") {
      std::cout << d.front() << "\n";
      d.pop_front();
    } else {
      int element;
      std::cin >> element;
      auto index = d.begin() + ((d.size() + 1) / 2);
      d.insert(index, element);
    }
  }
}

