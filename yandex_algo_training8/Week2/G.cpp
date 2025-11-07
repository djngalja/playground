#include <iostream>
#include <vector>

int main() {
   int N{};
   std::cin >> N;

   std::vector<int> table(N + 1);
   table[0] = 1;
   for (int i = 1; i <= N; ++i) {
      for (int j = N; j >= i; --j) {
         table[j] += table[j - i];
      }
   }

   std::cout << table[N];
   
   return 0;
}
