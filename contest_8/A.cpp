#include <iostream>
#include <set>
#include <vector>

const long long cNot = 2009000999;

class Graph {
public:
  Graph(int vertexc) : vertex_count_(vertexc), adj_(vertexc) {}

  void AddEdge(int from, int to, int weight) {
    adj_[from].emplace_back(to, weight);
    adj_[to].emplace_back(from, weight);
  }

  std::vector<int> Dijkstra(int source) {
    std::vector<int> distance(vertex_count_, cNot);
    std::set<std::pair<int, int>> quue;
    distance[source] = 0;
    for (int i = 0; i < vertex_count_; ++i) {
      quue.insert({distance[i], i});
    }

    while (!quue.empty()) {
      int current = quue.begin()->second;
      quue.erase(quue.begin());

      for (auto& [neighbor, weight] : adj_[current]) {
        if (weight != -1 && distance[current] + weight < distance[neighbor]) {
          quue.erase({distance[neighbor], neighbor});
          distance[neighbor] = distance[current] + weight;
          quue.insert({distance[neighbor], neighbor});
        }
      }
    }
    return distance;
  }

private:
  int vertex_count_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test;
  std::cin >> test;

  while (test > 0) {
    int vertex;
    int edge;
    std::cin >> vertex >> edge;
    Graph graph(vertex);
    for (int i = 0; i < edge; ++i) {
      int from;
      int to;
      int weight;
      std::cin >> from >> to >> weight;
      graph.AddEdge(from, to, weight);
    }
    int cvertex;
    std::cin >> cvertex;
    std::vector<int> distances = graph.Dijkstra(cvertex);
    for (int distance : distances) {
      std::cout << distance << " ";
    }
    std::cout << "\n";
    test--;
  }
}