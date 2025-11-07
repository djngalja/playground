#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <cmath>
#include <limits>
#include <iterator>

int main() {
   int n{};
   long p{}; 
   std::cin >> n >> p;
   std::unordered_map<long, int> val_ids;
   std::set<long> vals;
   for (int i = 0; i < n; ++i) {
      int num{};
      std::cin >> num;
      val_ids[num] = i;
      vals.insert(num);
   }

   double final_cmp{std::numeric_limits<double>::max()};
   long final_ci{};
   long final_cj{};
   for (long cj : vals) {
      auto it = vals.lower_bound(cj * p);
      if (it != vals.end() && *it == cj) { continue; }
      std::vector<int> options;
      if (it == vals.end()) {
         options.push_back(*vals.rbegin());
      } else if (it == vals.begin()) {
         options.push_back(*it);
      } else {
         options.push_back(*it);
         options.push_back(*std::prev(it, 1));
      }

      double cmp{std::numeric_limits<double>::max()};
      long ci{};
      for (long num : options) {
         double temp = std::abs((double)num / cj - p);
         if (temp < cmp) {
            cmp = temp;
            ci  = num;
         }
      }
      if (cmp < final_cmp) {
         final_cmp = cmp;
         final_ci = ci;
         final_cj = cj;
      }
   }

   std::cout << val_ids.at(final_ci) + 1 << ' ' << val_ids.at(final_cj) + 1;
   return 0;
}
