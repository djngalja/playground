#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

long dfs(int node, int parent, const std::vector<long>& a, 
   const std::vector<std::vector<int>>& adj,
   std::vector<long>& sum, std::vector<long>& max_child) {
   long val{a[node]};
   long max{};
   for (int child : adj[node]) {
      if (child == parent) { continue; }
      long child_val = dfs(child, node, a, adj, sum, max_child);
      max = std::max(max, child_val);
      val += child_val;
   }
   sum[node] = val;
   max_child[node] = max;
   return val;
}

int main() {
   int n{};
   std::cin >> n;
   std::vector<long> a(n + 1);
   for (int i = 1; i <= n; ++i) {
      std::cin >> a[i];
   }
   std::vector<std::vector<int>> adj(n + 1);
   for (int i = 0; i < n - 1; ++i) {
      int v{};
      int u{};
      std::cin >> v >> u;
      adj[v].push_back(u);
      adj[u].push_back(v);
   }

   std::vector<long> sum(n + 1);
   std::vector<long> max_child(n + 1);
   dfs(1, 0, a, adj, sum, max_child);
   
   int res{};
   long min_max_queue{std::numeric_limits<long>::max()};
   for (int i = 1; i <= n; ++i) {
      long max_queue = std::max({a[i], max_child[i], sum[1] - sum[i]});
      if (min_max_queue > max_queue) {
         min_max_queue = max_queue;
         res = i;
      }
   }

   std::cout << res;

   return 0;
}
