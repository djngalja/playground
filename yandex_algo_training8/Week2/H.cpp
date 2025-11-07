#include <iostream>
#include <vector>

bool is_prime(int num) {
   if (num <= 1) { return false;}
   bool flag{true};

   for (int i = 2; i * i <= num; ++i) {
      if (num % i == 0) {
         flag = 0;
         break;
      }
   }

   return flag;
}

int game(int N) {
   std::vector<int> table(N + 1);

   for (int i = 1; i <= 3; ++i) {
      table[i] = 1;
   }

   for (int i = 4; i <= N; ++i) {
      for (int j = 1; j <= 3; ++j) {
         int remain = i - j;
         if ((!is_prime(remain)) && (table[remain] == 0)) {
            table[i] = 1;
            break;
         }
      }
   }

   return table[N] ? 1 : 2;
}

int main() {
   int N{};
   std::cin >> N;
   
   std::cout << game(N);

   return 0;
}
