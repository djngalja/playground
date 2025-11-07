#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

int main() {
   int N{};
   int K{};
   std::cin >> N >> K;

   std::vector<int> A(N);
   for (int i = 0; i < N; ++i) {
      std::cin >> A[i];
   }

   std::vector<int> sums;
   int sum{};
   for (int i = 0; i < K; ++i) {
      sum += A[i];
   }
   sums.push_back(sum);
   for (int i = K; i < N; ++i) {
      sum += A[i] - A[i - K];
      sums.push_back(sum);
   }

   std::vector<int> mins;
   std::deque<int> dq;
   for (int i = 0; i < N; ++i) {
      while (!dq.empty() && A[i] < A[dq.back()]) {
         dq.pop_back();
      }
      dq.push_back(i);
      if (dq.front() == i - K) { 
         dq.pop_front(); 
      }
      if (i >= K - 1) { mins.push_back(A[dq.front()]); }
   }

   int sz = mins.size();
   
   std::vector<int> protec;
   for (int i = 0; i < sz; ++i) {
      protec.push_back(mins[i] * sums[i]);
   }

   std::vector<long> max_protec(sz);
   std::vector<int> add(sz);
   max_protec[0] = protec[0];
   add[0] = 1;
   for (int i = 1; i < std::min(sz, K); ++i) {
      if (max_protec[i - 1] > protec[i]) {
         max_protec[i] = max_protec[i - 1];
      } else {
         max_protec[i] = protec[i];
         add[i] = 1;
      }
   }
   for (int i = K; i < sz; ++i) {
      long if_add = protec[i] + max_protec[i - K];
      if (max_protec[i - 1] > if_add) {
         max_protec[i] = max_protec[i - 1];
      } else {
         max_protec[i] = if_add;
         add[i] = 1;
      }
   }

   std::vector<int> output;
   int pos{sz - 1};
   while (pos >= 0) {
      if (add[pos]) {
         output.push_back(pos + 1);
         pos -= K;
      } else {
         --pos;
      }
   }

   int Q = output.size();  
   std::cout << Q << '\n';
   for (int i = Q - 1; i >= 0; --i) {
      std::cout << output[i] << ' ';
   }

   return 0;
}
