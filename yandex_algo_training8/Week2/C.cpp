#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
   double b;
   double e;
   double w;
};

bool comp(const Interval& lhs, const Interval& rhs) {
   return lhs.e < rhs.e;
}

bool cmp(double val, const Interval& interval) {
   return val < interval.e;
}

int main() {
   int N{};
   std::cin >> N;
   std::vector<Interval> intervals(N);
   for (int i = 0; i < N; ++i) {
       std::cin >> intervals[i].b >> intervals[i].e >> intervals[i].w;
   }
   std::sort(intervals.begin(), intervals.end(), comp);

   std::vector<double> max_weight(N + 1);
   for (int i = 0; i < N; ++i) {
        auto it = std::upper_bound(intervals.begin(), intervals.begin() + i, intervals[i].b, cmp);
        double add = max_weight[it - intervals.begin()];
        intervals[i].w += add;
        max_weight[i + 1] = std::max(max_weight[i], intervals[i].w);
   }

   std::cout << max_weight[N];

   return 0;
}
