#include <iostream>
#include <algorithm>

int main() {
   long a{};
   long b{};
   long S{};
   std::cin >> a >> b >> S;

   long left{std::max(a,b)};
   long right{S + a * b};
   long mid{};
   while (left < right) {
      mid = (left + right) / 2;
      if ((mid - b) * (mid - a) >= S) {
         right = mid;
      } else {
         left = mid + 1;
      }
   }

   long res = ((left - b) * (left - a) != S) ? -1 : left; 
   std::cout << res;

   return 0;
}
