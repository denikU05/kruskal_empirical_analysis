#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

struct GraphNode{
  int a;
  int b;
  int w;
};

void vine() {
  std::string file_name = "../tests/vine/";
  int n = 2;
  for (int k = 0; k < 50; ++k) {
    std::cout << k << '\n';
    std::ofstream fout(file_name + std::to_string(k) + ".txt");
    fout << n << ' ' << n - 1 << '\n';
    for (int i = 1; i < n; ++i) {
      fout << i - 1 << ' ' << i << ' ' << i << '\n';
    }
    fout.close();
    n += 500000;
  }
}

void complete() {
  std::string file_name = "../tests/complete/";
  int n = 2;
  for (int k = 0; k < 20; ++k) {
    std::cout << k << '\n';
    std::ofstream fout(file_name + std::to_string(k) + ".txt");
    fout << n << ' ' << n * (n - 1) / 2 << '\n';
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        fout << i << ' ' << j << ' ' << 1 << '\n';
      }
    }
    fout.close();
    n += 500;
  }
}

void random() {
  std::string file_name = "../tests/random/";
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> random_w(-100, 100);
  int MAX_N = 10000;
  int MAX_M = 49995000;
  std::uniform_int_distribution<> random_n(2, MAX_N);
  std::vector<GraphNode> g(MAX_M);
  for (int k = 0; k < 100; ++k) {
    int n = random_n(gen);
    std::cout << n << '\n';
    int m = 0;
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 2; j < n; ++j) {
        int w = random_w(gen);
        if (w > 0) {
          g[m++] = { i, j, w };
        }
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      g[m++] = { i, i + 1, abs(random_w(gen)) };
    }
    std::sort(g.begin(), g.begin() + m,
              [](auto& a, auto&b) { return a.w < b.w; });
    std::ofstream fout(file_name + std::to_string(k) + ".txt");
    fout << n << ' ' << m << '\n';
    for (int i = 0; i < m; ++i) {
      fout << g[i].a << ' ' << g[i].b << ' ' << g[i].w << '\n';
    }
    fout.close();
  }
}

void special() {
  std::string file_name = "../tests/special/";
  int n = 2;
  for (int k = 0; k < 20; ++k) {
    std::cout << k << '\n';
    std::ofstream fout(file_name + std::to_string(k) + ".txt");
    fout << n << ' ' << n / 2 * (n / 2 - 1) + 1 << '\n';
    for (int i = 0; i < n / 2; ++i) {
      for (int j = i + 1; j < n / 2; ++j) {
        fout << i << ' ' << j << ' ' << 1 << '\n';
      }
    }
    for (int i = n / 2; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        fout << i << ' ' << j << ' ' << 1 << '\n';
      }
    }
    fout << n / 2 - 1 << ' ' << n / 2 << ' ' << 2 << '\n';
    fout.close();
    n += 500;
  }
}

int main() {
  vine();
  complete();
  random();
  special();
  return 0;
}
