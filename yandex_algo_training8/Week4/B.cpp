#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main() {
   int n{};
   std::cin >> n;
   std::vector<long> b(n);
   std::vector<long> t(n);
   for (int i = 0; i < n; ++i) {
      std::cin >> b[i] >> t[i];
   }
   int m{};
   std::cin >> m;
   std::vector<long> q(m);
   for (int i = 0; i < m; ++i) {
      std::cin >> q[i];
   }

   std::vector<long> q_copy(q);
   std::sort(q_copy.begin(), q_copy.end());

   auto it = std::lower_bound(b.begin(), b.end(), q_copy[0]);
   int j = it - b.begin() - 1;

   std::unordered_map<long, long> res;
   for (int i = 0; i < m; ++i) {
      while (b[j] < q_copy[i] && j < n) {
         ++j;
      }
      res[q_copy[i]] = q_copy[i] * t[j - 1];
   }

   for (int i = 0; i < m; ++i) {
      std::cout << res[q[i]] << '\n';
   }
   return 0;
}
