#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
   std::ifstream file("input.txt");
   int n{};
   int m{};
   long k{};
   file >> n >> m >> k;

   std::vector<long> a(n + 1);
   std::vector<long> pref_sum(n + 1);
   for (int i = 1; i <= n; ++i) {
      file >> a[i];
      pref_sum[i] = pref_sum[i - 1] + a[i];
   }

   long unhappy{};
   
   std::vector<int> diff(n + 2);
   for (int i = 0; i < m; ++i) {
      int begin{};
      int end{};
      file >> begin >> end;
      ++diff[begin];
      --diff[end + 1];
      unhappy += pref_sum[end] - pref_sum[begin - 1];
   }

   std::vector<int> num_routes(n + 1);
   for (int i = 1; i <= n; ++i) {
      num_routes[i] = num_routes[i - 1] + diff[i];
   }

   std::priority_queue<std::pair<int, int>> pq;
   for (int i = 1; i <= n; ++i) {
      pq.push(std::make_pair(num_routes[i], i));
   }

   while (!pq.empty() && (k > 0) && (unhappy > 0)) {
      auto temp = pq.top();
      pq.pop();
      long remove = std::min(k, a[temp.second]);
      k -= remove;
      unhappy -= remove * temp.first;
   } 

   std::cout << std::max(0l, unhappy);

   return 0;
}
