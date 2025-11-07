#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

struct Data { 
   long s; 
   long a;

   bool operator<(const Data& other) const {
      return s < other.s;
   }
};

bool check(long e, const std::vector<Data>& data, const std::vector<long>& pref_sum_a) {
   int n = data.size() - 1;
   auto it = std::lower_bound(data.begin(), data.end(), Data{e + 1, 0});
   int cnt = it - data.begin();
   return pref_sum_a[n] - pref_sum_a[cnt - 1] <= pref_sum_a[n] / 2;
}

long calc_cost(long e, const std::vector<Data>& data, const std::vector<long>& pref_sum_a, 
   const std::vector<long>& pref_sum_sa) {
   int n = data.size() - 1;
   auto it1 = std::lower_bound(data.begin(), data.end(), Data{e, 0});
   int cnt = it1 - data.begin();
   long cost = e * pref_sum_a[cnt - 1] - pref_sum_sa[cnt - 1];
   cost += (pref_sum_sa[n] - pref_sum_sa[cnt - 1]) - (pref_sum_a[n] - pref_sum_a[cnt - 1]) * e;
   return cost;
}

int main() {
   std::ifstream file("input.txt");
   int n{};
   file >> n;

   std::vector<Data> data(n + 1);
   for (int i = 1; i <= n; ++i) {
      file >> data[i].s;
   }
   for (int i = 1; i <= n; ++i) {
      file >> data[i].a;
   }
   std::sort(data.begin(), data.end());

   std::vector<long> pref_sum_a(n + 1);
   std::vector<long> pref_sum_sa(n + 1);
   for (int i = 1; i <= n; ++i) {
      pref_sum_a[i] = pref_sum_a[i - 1] + data[i].a;
      pref_sum_sa[i] = pref_sum_sa[i - 1] + data[i].s * data[i].a;
   }

   long left = data[1].s;
   long right = data[n].s;
   long mid{};
   
   while (left < right) {
      mid = (left + right) / 2;
      if (check(mid, data, pref_sum_a)) {
         right = mid;
      } else {
         left = mid + 1;
      }
   }

   std::cout << left << ' ' << calc_cost(left, data, pref_sum_a, pref_sum_sa);
   return 0;
}
