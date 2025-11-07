#include <iostream>
#include <vector>
#include <cmath>

long dfs(int node, const std::vector<std::vector<int>>& adj, const std::vector<long>& vals, long& res) {
   long sum{};
   for (int child : adj[node]) {
      sum += dfs(child, adj, vals, res);
   }
   res += std::abs(vals[node] + sum);
   return -vals[node];
}

int main() {
   int n{};
   std::cin >> n;

   std::vector<std::vector<int>> adj(n);
   for (int i = 1; i < n; ++i) {
      int num;
      std::cin >> num;
      adj[num].push_back(i);
   }

   std::vector<long> vals(n);
   for (int i = 0; i < n; ++i) {
      std::cin >> vals[i];
   }

   long res{};
   dfs(0, adj, vals, res);
   std::cout << res;

   return 0;
}
