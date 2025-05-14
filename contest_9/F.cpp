#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int cInf = 10000001;
const int cMaxn = 105;

struct Edge {
  int to;
  int capacity;
  int flow;
  int reverse;
  int index;
  Edge(int t, int cap, int f, int rev_idx, int orig_idx)
      : to(t), capacity(cap), flow(f), reverse(rev_idx), index(orig_idx) {}
};

std::vector<Edge> graph[cMaxn];
int parent_vertex[cMaxn];
int parent_edge_index[cMaxn];
bool visited[cMaxn];

void AddEdge(int u, int v, int capacity, int index) {
  graph[u].emplace_back(v, capacity, 0, (int)graph[v].size(), index);
  graph[v].emplace_back(u, capacity, 0, (int)graph[u].size(), index);
  graph[u].back().reverse = graph[v].size() - 1;
  graph[v].back().reverse = graph[u].size() - 1;
}

bool BFS(int s, int t, int n) {
  for (int i = 0; i <= n; ++i) {
    visited[i] = false;
    parent_vertex[i] = -1;
    parent_edge_index[i] = -1;
  }
  std::queue<int> q;
  q.push(s);
  visited[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u == t) {
      return true;
    }
    for (size_t i = 0; i < graph[u].size(); ++i) {
      Edge& e = graph[u][i];
      int v = e.to;

      if (!visited[v] && e.capacity - e.flow > 0) {
        visited[v] = true;
        parent_vertex[v] = u;
        parent_edge_index[v] = i;
        q.push(v);
      }
    }
  }
  return false;
}

long long MaxFlow(int s, int t, int n) {
  long long total_flow = 0;
  while (BFS(s, t, n)) {
    int path_flow = cInf;
    for (int v = t; v != s; v = parent_vertex[v]) {
      int u = parent_vertex[v];
      int edge_idx = parent_edge_index[v];
      path_flow = std::min(
          path_flow, graph[u][edge_idx].capacity - graph[u][edge_idx].flow);
    }
    for (int v = t; v != s; v = parent_vertex[v]) {
      int u = parent_vertex[v];
      int edge_idx = parent_edge_index[v];
      graph[u][edge_idx].flow += path_flow;
      int reverse_edge_idx = graph[u][edge_idx].reverse;
      graph[v][reverse_edge_idx].flow -= path_flow;
    }
    total_flow += path_flow;
  }
  return total_flow;
}

void Find(int s, int n) {
  for (int i = 0; i <= n; ++i) {
    visited[i] = false;
  }
  std::queue<int> q;
  q.push(s);
  visited[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (const auto& edge : graph[u]) {
      if (!visited[edge.to] && edge.capacity - edge.flow > 0) {
        visited[edge.to] = true;
        q.push(edge.to);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    AddEdge(u, v, c, i + 1);
  }
  int source = 1;
  int sink = n;
  long long min_cut_capacity = MaxFlow(source, sink, n);
  Find(source, n);
  std::vector<int> cut_edge_indices;
  for (int u = 1; u <= n; ++u) {
    if (visited[u]) {
      for (const auto& edge : graph[u]) {
        if (!visited[edge.to]) {
          cut_edge_indices.push_back(edge.index);
        }
      }
    }
  }
  std::sort(cut_edge_indices.begin(), cut_edge_indices.end());

  std::cout << cut_edge_indices.size() << " " << min_cut_capacity << "\n";
  for (size_t i = 0; i < cut_edge_indices.size(); ++i) {
    if (i > 0) {
      std::cout << " ";
    }
    std::cout << cut_edge_indices[i];
  }
  std::cout << "\n";
}
