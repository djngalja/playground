#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

struct XY {
  int x;
  int y;

  XY operator+(const XY& pos) {
     return XY{x + pos.x, y + pos.y};
  }

  bool operator<(const XY& pos) const {
     return (x < pos.x) || (x == pos.x && y < pos.y);
  }

};

int dfs(int n, int m, const XY& xy, std::vector<std::vector<int>>& table) {
   std::vector<std::vector<int>> visited(n, std::vector<int>(m));
  std::stack<XY> st;
  st.push(xy);

  int init_val {table[xy.x][xy.y]};
  int val{};
  while (!st.empty()) {
     XY pos = st.top();
     st.pop();

     if (visited[pos.x][pos.y]) { continue; }

     for (const XY& dir : { XY{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
        XY npos = pos + dir;
        if (npos.x >= 0 && npos.x < n && npos.y >= 0 && npos.y < m
           && (!visited[npos.x][npos.y])
           && (table[npos.x][npos.y] - table[pos.x][pos.y] == 1)) {
           st.push(npos);
        }
     }
    
     visited[pos.x][pos.y] = 1;
     val = std::max(table[pos.x][pos.y], val);
  }
  return val - init_val + 1;
}


int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
 
  std::vector<std::vector<int>> table(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
     for (int j = 0; j < m; ++j) {
        std::cin >> table[i][j];
     }
  }

  int res{};

  for (int i = 0; i < n; ++i) {
     for (int j = 0; j < m; ++j) {
        res = std::max(dfs(n, m, XY{i, j}, table), res);
     }
  }

  std::cout << res;

  return 0;
}
