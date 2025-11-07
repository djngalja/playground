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

int main() {
   int N{};
   std::cin >> N;
   double begin{};
   double end{};
   double weight{};
   std::vector<Interval> intervals;
   for (int i = 0; i < N; ++i) {
       std::cin >> begin >> end >> weight;
       intervals.push_back({begin, end, weight});
   }

   std::sort(intervals.begin(), intervals.end(), comp);

   for (int i = 0; i < N; ++i) {
       double add{};
       for (int j = 0; j < i; ++j) {
           if (intervals[j].e <= intervals[i].b && intervals[j].w > add) {
              add = intervals[j].w;
           }
       }
       intervals[i].w += add;
   }

   double max_weight{};
   for (const auto& i : intervals) {
       if (i.w > max_weight) {
           max_weight = i.w;
       }
   }

   std::cout << max_weight;

   return 0;
}
