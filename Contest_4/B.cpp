#include <iostream>

struct AVLTree {
  struct Node {
    long long key;
    int height;
    Node* left;
    Node* right;
    explicit Node(long long k)
        : key(k), height(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  AVLTree() : root(nullptr) {}

  ~AVLTree() { Clear(root); }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  static int Height(Node* node) { return (node != nullptr) ? node->height : 0; }
  static int Balance(Node* node) {
    return (node != nullptr) ? Height(node->left) - Height(node->right) : 0;
  }

  static Node* RotateRight(Node* gamma) {
    Node* alpha = gamma->left;
    Node* bheta = alpha->right;

    alpha->right = gamma;
    gamma->left = bheta;

    gamma->height = std::max(Height(gamma->left), Height(gamma->right)) + 1;
    alpha->height = std::max(Height(alpha->left), Height(alpha->right)) + 1;

    return alpha;
  }

  static Node* RotateLeft(Node* alpha) {
    Node* bheta = alpha->right;
    Node* gamma = bheta->left;

    bheta->left = alpha;
    alpha->right = gamma;
    alpha->height = std::max(Height(alpha->left), Height(alpha->right)) + 1;
    bheta->height = std::max(Height(bheta->left), Height(bheta->right)) + 1;
    return bheta;
  }

  Node* Insert(Node* node, long long key) {
    if (node == nullptr) {
      return new Node(key);
    }

    if (key < node->key) {
      node->left = Insert(node->left, key);
    } else if (key > node->key) {
      node->right = Insert(node->right, key);
    } else {
      return node;
    }
    node->height = std::max(Height(node->left), Height(node->right)) + 1;

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

  void Insert(long long key) { root = Insert(root, key); }

  static long long LowerBound(Node* node, const long long cKey) {
    long long res = -1;
    while (node != nullptr) {
      if (node->key >= cKey) {
        res = node->key;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return res;
  }
  long long LowerBound(long long key) const { return LowerBound(root, key); }
};

void Solution(AVLTree& tree, int q) {
  const int cMod = 1000000000;
  long long y = 0;
  char last_operation = ' ';
  for (int i = 0; i != q; i++) {
    char type;
    long long x;
    std::cin >> type >> x;
    if (type == '+') {
      if (last_operation == '?') {
        tree.Insert((x + y) % cMod);
      } else {
        tree.Insert(x);
      }
      last_operation = '+';
      y = x;
    } else if (type == '?') {
      y = tree.LowerBound(x);
      last_operation = '?';
      std::cout << y << "\n";
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int q;
  std::cin >> q;
  AVLTree tree;
  Solution(tree, q);
}
