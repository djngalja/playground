#include <iostream>
#include <vector>
#include <algorithm>

struct XY {
   int x;
   int y;

   XY operator+(const XY& pos) const {
      return XY{x + pos.x, y + pos.y};
   }
};

void dfs(int n, int m, const XY& pos, const std::vector<std::vector<int>>& table, 
   std::vector<std::vector<int>>& visited, std::vector<std::vector<int>>& max_len) {
   visited[pos.x][pos.y] = 1;
   for (const XY& dir : { XY{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
      XY npos = pos + dir;
      if (npos.x >= 0 && npos.x < n && npos.y >= 0 && npos.y < m
      && (table[npos.x][npos.y] - table[pos.x][pos.y] == 1)) {
         if (!visited[npos.x][npos.y]) {
            dfs(n, m, npos, table, visited, max_len);
         }
         max_len[pos.x][pos.y] = std::max(max_len[pos.x][pos.y], 1 + max_len[npos.x][npos.y]);
      }
   }
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

   std::vector<std::vector<int>> visited(n, std::vector<int>(m));
   std::vector<std::vector<int>> max_len(n, std::vector<int>(m));
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         if (!visited[i][j]) {
            dfs(n, m, XY{i, j}, table, visited, max_len);
         }
      }
   }

   int res{};
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         res = std::max(res, max_len[i][j]);
      }
   }

   std::cout << res + 1;

   return 0;
}
