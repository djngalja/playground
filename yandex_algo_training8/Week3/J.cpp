#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

bool check(const std::vector<long>& a, const std::vector<long>& b, int n, int k) {
   std::deque<int> dq;
   for (int i = 0; i <= k; ++i) {
      dq.push_back(i);
   }
   std::vector<long> b_copy(b);
   for (int i = 0; i < n; ++i) {
      int first_day = std::max(0, i - k);
      int last_day = std::min(n - 1, i + k);
      while (!dq.empty() && dq.front() < first_day) {
         dq.pop_front();
      }
      if (dq.empty() || dq.back() < last_day) {
         dq.push_back(last_day);
      }

      long candidates{a[i]};
      auto it = dq.begin();
      
      while (candidates && it != dq.end()) {
         long assign = std::min(candidates, b_copy[*it]);
         b_copy[*it] -= assign;
         candidates -= assign;
         if (!b_copy[*it]) {
            it = dq.erase(it);
         } else {
            ++it;
         }
      }
      if (candidates) { return false; }
   }
   return true;
}

int main() {
   std::ifstream file("input.txt");
   int n{};
   file >> n;

   std::vector<long> a(n);
   long ttl_a{};
   for (int i = 0; i < n; ++i) {
      file >> a[i];
      ttl_a += a[i];
   }
   std::vector<long> b(n);
   long ttl_b{};
   for (int i = 0; i < n; ++i) {
      file >> b[i];
      ttl_b += b[i];
   }

   int k{};
   if (ttl_a > ttl_b) {
      k = -1;
   } else {
      int left{};
      int right{n};
      int mid{};
      while (left < right) {
         mid = (left + right) / 2;
         if (check(a, b, n, mid)) {
            right = mid;
         } else {
            left =  mid + 1;
         }
      }
      k = left;
   }

   std::cout << k;

   return 0;
}
