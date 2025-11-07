#include <iostream>

int main() {
   int N{};
   std::cin >> N;
   
   int res = (N % 4 == 0) ? 2 : 1;
   std::cout << res;

   return 0;
}
