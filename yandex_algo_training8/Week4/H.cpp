#include <iostream>
#include <vector>
#include <algorithm>

int main() {
   long n{};
   std::cin >> n;

   std::vector<long> a(n + 1);
   std::vector<long> pref_sum_a(n + 1);
   for (int i = 1; i <= n; ++i) {
      std::cin >> a[i];
      pref_sum_a[i] = pref_sum_a[i - 1] + a[i];
   }

   long res{};
   for (int j = 1; j < n; ++j) {
      long end = std::min(n, a[j] + j - 1);
      if (j < end) {
         res += pref_sum_a[end] - pref_sum_a[j];
      }
   }

   std::cout << res;
   return 0;
}
