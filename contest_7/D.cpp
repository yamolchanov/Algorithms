#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Graph {
public:
    int n;
    std::vector<std::vector<int>> e;
    std::vector<std::vector<int>> er;

    Graph(int n, int m) : n(n), e(n), er(n) {
        for (int i = 0; i < m; ++i) {
            int a;
            int b;
            std::cin >> a >> b;
            --a;
            --b;
            AddEdge(a, b);
        }
    }

    void AddEdge(int a, int b) {
        e[a].push_back(b);
        er[b].push_back(a);
    }
};

class Shell {
public:
    std::vector<std::string> was;
    std::vector<int> order;
    std::vector<int> comp;
    std::vector<int> ans;

    Shell(int n) : was(n, "white"), ans(n, 0) {}

    void ResetWas() { std::ranges::fill(was, "white"); }
    void ClearComp() { comp.clear(); }

    void Solve(const Graph& g) {
        int cnt = 0;

        for (int i = 0; i < g.n; ++i) {
            if (was[i] == "white") {
                DFS1(i, g);
            }
        }

        ResetWas();
        std::ranges::reverse(order);

        for (int v : order) {
            if (was[v] == "white") {
                DFS2(v, g, cnt);
                ++cnt;
                ClearComp();
            }
        }

        std::cout << cnt << "\n";
        for (int x : ans) {
            std::cout << x + 1 << " ";
        }
        std::cout << "\n";
    }

private:
    void DFS1(int v, const Graph& g) {
        was[v] = "grey";
        for (int u : g.e[v]) {
            if (was[u] == "white") {
                DFS1(u, g);
            }
        }
        was[v] = "black";
        order.push_back(v);
    }

    void DFS2(int v, const Graph& g, int cnt) {
        was[v] = "grey";
        comp.push_back(v);
        ans[v] = cnt;
        for (int u : g.er[v]) {
            if (was[u] == "white") {
                DFS2(u, g, cnt);
            }
        }
        was[v] = "black";
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int m;
    std::cin >> n >> m;

    Graph g(n, m);
    Shell shell(n);
    shell.Solve(g);
}