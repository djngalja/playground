#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Time { int in; int out; };

int dfs(int node, int time_in, const std::vector<std::vector<int>>& adj, std::unordered_map<int, Time>& data) {
   ++time_in;
   data[node].in = time_in;
   int time_out{time_in};
   for (int child : adj[node]) {
      time_out =  dfs(child, time_out, adj, data);
   }
   data[node].out = time_out;
   return time_out;
}

int main() {
   std::ifstream file("input.txt");
   int n{};
   file >> n;

   std::vector<std::vector<int>> adj(n + 1);
   for (int i = 1; i <= n; ++i) {
      int num;
      file >> num;
      adj[num].push_back(i);
   }

   std::unordered_map<int, Time> data;
   int root = adj[0][0];
   dfs(root, -1, adj, data);

   int m{};
   file >> m;

   std::ofstream out("output.txt");
   for (int i = 0; i < m; ++i) {
      int a{};
      int b{};
      file >> a >> b;
      if (data[b].in > data[a].in && data[b].out <= data[a].out) {
         out << 1;
      } else {
         out << 0;
      }
      out << '\n';
   }

   return 0;
}
