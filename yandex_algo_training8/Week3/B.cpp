#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

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

   std::queue<int> nodes;
   std::vector<int> src(n + 1);
   for (const auto& node : adj) {
      if (node.second.size() == 1) {
         nodes.push(node.first);
         src[node.first] = node.first;
      }
   }

   if (nodes.size() == 2) {
      std::cout << n - 1;
   } else {
      std::vector<int> distance(n + 1);
      bool res_found{};
      while (!nodes.empty() && !res_found) {
         int node = nodes.front();
         nodes.pop();
         for (int child : adj[node]) {
            if (distance[child] > 0) {
               if (src[child] != src[node]) {
                  std::cout << (distance[child] + distance[node] + 1);
                  res_found = true;
                  break;
               }
            } else {
               distance[child] = distance[node] + 1;
               src[child] = src[node];
               nodes.push(child);
            }
         }
      }
   }

   return 0;
}
