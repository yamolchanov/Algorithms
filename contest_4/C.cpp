#include <algorithm>
#include <iostream>
#include <string>

struct AVLTree {
  struct Node {
    std::string key;
    std::string value;
    int height;
    Node* left;
    Node* right;

    explicit Node(std::string k, std::string v)
        : key(std::move(k)),
          value(std::move(v)),
          height(1),
          left(nullptr),
          right(nullptr) {}
  };

  Node* root;

  AVLTree() : root(nullptr) {}

  ~AVLTree() { Clear(root); }

  void Clear(Node* node) {
    if (node != nullptr) {
      Clear(node->left);
      Clear(node->right);
      delete node;
    }
  }

  static int Height(Node* node) { return node != nullptr ? node->height : 0; }

  static int Balance(Node* node) {
    return node != nullptr ? Height(node->left) - Height(node->right) : 0;
  }

  static Node* RotateRight(Node* y) {
    Node* x = y->left;
    Node* t = x->right;

    x->right = y;
    y->left = t;

    y->height = std::max(Height(y->left), Height(y->right)) + 1;
    x->height = std::max(Height(x->left), Height(x->right)) + 1;

    return x;
  }

  static Node* RotateLeft(Node* x) {
    Node* y = x->right;
    Node* t = y->left;

    y->left = x;
    x->right = t;

    x->height = std::max(Height(x->left), Height(x->right)) + 1;
    y->height = std::max(Height(y->left), Height(y->right)) + 1;

    return y;
  }

  Node* Insert(Node* node, const std::string& key, const std::string& value) {
    if (node == nullptr) {
      return new Node(key, value);
    }

    if (key < node->key) {
      node->left = Insert(node->left, key, value);
    } else if (key > node->key) {
      node->right = Insert(node->right, key, value);
    } else {
      return node;
    }

    node->height = 1 + std::max(Height(node->left), Height(node->right));
    int balance = Balance(node);

    if (balance > 1 && key < node->left->key) {
      return RotateRight(node);
    }
    if (balance < -1 && key > node->right->key) {
      return RotateLeft(node);
    }
    if (balance > 1 && key > node->left->key) {
      node->left = RotateLeft(node->left);
      return RotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
      node->right = RotateRight(node->right);
      return RotateLeft(node);
    }

    return node;
  }

  void Insert(const std::string& key, const std::string& value) {
    root = Insert(root, key, value);
  }

  std::string Find(Node* node, const std::string& key) const {
    if (node == nullptr) {
      return "nihya_net";
    }

    if (key == node->key) {
      return node->value;
    }
    if (key < node->key) {
      return Find(node->left, key);
    }
    return Find(node->right, key);
  }

  std::string Find(const std::string& key) const { return Find(root, key); }
};

void Solution(AVLTree& password_tree, AVLTree& login_tree) {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string login;
    std::string password;
    std::cin >> login >> password;
    password_tree.Insert(password, login);
    login_tree.Insert(login, password);
  }

  int q;
  std::cin >> q;
  for (int i = 0; i != q; ++i) {
    std::string query;
    std::cin >> query;
    std::string result = login_tree.Find(query);
    if (result != "nihya_net") {
      std::cout << result << '\n';
    } else {
      std::cout << password_tree.Find(query) << '\n';
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  AVLTree pass;
  AVLTree login;
  Solution(pass, login);
  // it was very painful to debug
}
