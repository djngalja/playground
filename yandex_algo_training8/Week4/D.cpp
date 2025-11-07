#include <fstream>
#include <vector>
#include <cmath>

int main() {
   std::ifstream file("input.txt");
   int n{};
   file >> n;

   std::vector<long> a(n + 1);
   std::vector<long> pref_sum(n + 1);
   for (int i = 1; i <= n; ++i) {
      file >> a[i];
      pref_sum[i] = pref_sum[i - 1] + a[i];
   }

   int l{1};
   int r{n};
   long min_diff = std::abs(a[l] - a[r]);

   int right{n};
   for (int left = 1; left < right; ++left) {
      long diff = std::abs(pref_sum[left] - (pref_sum[n] - pref_sum[right - 1]));
      if (diff < min_diff) {
         min_diff = diff;
         r = right;
         l = left;
      }
      while (right - left > 1) {
         long diff_prev = std::abs(pref_sum[left] - (pref_sum[n] - pref_sum[right - 2]));
         if (diff_prev <= diff) {
            --right;
            diff = diff_prev;
            if (diff < min_diff) {
               min_diff = diff;
               r = right;
               l = left;
            }
         } else {
            break;
         }
      }
   }

   std::ofstream out("output.txt");
   out << min_diff << ' ' << l << ' ' << r;
   
   return 0;
}
