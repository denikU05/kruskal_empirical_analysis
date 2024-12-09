#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

struct GraphNode{
  int a;
  int b;
  int w;
};

int dsu_get(std::vector<int>& p, int v) {
  return (v == p[v]) ? v : (p[v] = dsu_get(p, p[v]));
}

void dsu_unite(std::vector<int>& p, std::vector<int>& r, int a, int b) {
  a = dsu_get(p, a);
  b = dsu_get(p, b);
  if (a != b) {
    if (r[a] < r[b]) {
      std::swap(a, b);
    }
    p[b] = a;
    if (r[a] == r[b]) {
      ++r[a];
    }
  }
}

int main() {
  std::ofstream fout("../results/special.txt");
  std::string input_file_name = "../tests/special/";
  int NUM_OF_TESTS = 20;
  for (int t = 0; t < NUM_OF_TESTS; ++t) {
    std::cout << t << '\n';
    std::ifstream fin(input_file_name + std::to_string(t) + ".txt");
    int n;
    int m;
    fin >> n >> m;
    std::vector<GraphNode> g(m);
    for (int i = 0; i < m; ++i) {
      int a;
      int b;
      int w;
      fin >> a >> b >> w;
      g[i] = {a, b, w};
    }
    fin.close();
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<int> p(n);
    std::vector<int> r(n, 0);
    for (int i = 0; i < n; ++i) {
      p[i] = i;
    }
    for (int i = 0; i < m; ++i) {
      if (dsu_get(p, g[i].a) != dsu_get(p, g[i].b)) {
        dsu_unite(p, r, g[i].a, g[i].b);
      }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    fout << n << ' ' << m << ' ' <<
            (end_time - start_time).count() << '\n';
  }
  fout.close();
  return 0;
}