#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int calc_len(int node, int target, const std::unordered_map<int, std::vector<int>>& adj, 
   std::vector<int>& visited) {
   visited[node] = 1;
   if (node == target) {
      return 0;
   }
   for (int child : adj.at(node)) {
      if (visited[child] == 0) {
         int len = calc_len(child, target, adj, visited);
         if (len != -1) { return len + 1; }
      }
   }
   return -1;
}

int main() {
   int n{};
   std::cin >> n;
   std::unordered_map<int, std::vector<int>> adj;
   for (int i = 0; i < n - 1; ++i) {
      int a{};
      int b{};
      std::cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
   }

   std::vector<int> leaves;
   for (const auto& node : adj) {
      if (node.second.size() == 1) {
         leaves.push_back(node.first);
      }
   }

   int min_len{n - 1};
   while (!leaves.empty()) {
      int leaf = leaves.back();
      leaves.pop_back();
      for (int lf : leaves) {
         std::vector<int> visited(n + 1);
         int len = calc_len(leaf, lf, adj, visited);
         if (len == -1) { continue; }
         min_len = std::min(min_len, len);
         if (min_len == 2) { break; }
      }
   }
   
   std::cout << min_len;

   return 0;
}
