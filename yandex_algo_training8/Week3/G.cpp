#include <iostream>
#include <vector>
#include <algorithm>

int main() {
   int n{};
   std::cin >> n;
   std::vector<long> a(n);
   for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
   }

   int m{};
   std::cin >> m;
   std::vector<long> b(m);
   for (int i = 0; i < m; ++i) {
      std::cin >> b[i];
   }

   std::vector<long> a_copy(a);
   std::sort(a_copy.begin(), a_copy.end());
   std::vector<long> b_copy(b);
   std::sort(b_copy.begin(), b_copy.end());

   std::vector<long> pre_sum_a(n);
   pre_sum_a[0] = a_copy[0];
   for (int i = 1; i < n; ++i) {
      pre_sum_a[i] = pre_sum_a[i - 1] + a_copy[i];
   }

   std::vector<long> pre_sum_b(m);
   pre_sum_b[0] = b_copy[0];
   for (int i = 1; i < m; ++i) {
      pre_sum_b[i] = pre_sum_b[i - 1] + b_copy[i];
   }

   long res{};

   for (int i = 0; i < n; ++i) { 
      auto it = std::upper_bound(b_copy.begin(), b_copy.end(), a[i]); 
      long cnt = it - b_copy.begin();
      long pre_b = cnt ? pre_sum_b[cnt - 1] : 0;
      long diff = a[i] * cnt - 2 * pre_b + pre_sum_b[m - 1] - a[i] * (m - cnt);
      res += (i + 1) * diff;
   }

   for (int i = 0; i < m; ++i) {
      auto it = std::upper_bound(a_copy.begin(), a_copy.end(), b[i]);
      long cnt = it - a_copy.begin();
      long pre_a = cnt ? pre_sum_a[cnt - 1] : 0;
      long diff = b[i] * cnt - 2 * pre_a + pre_sum_a[n - 1] - b[i] * (n - cnt);
      res -= (i + 1) * diff;
   }

   std::cout << res;

   return 0;
}
