#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
   int n{};
   std::cin >> n;
   std::vector<std::vector<int>> road(n);
   for (int i = 0; i < n; ++i) {
      std::string temp;
      std::cin >> temp;
      for (char ch : temp) {
         if (ch == 'W') {
            road[i].push_back(-1);
         } else if (ch == 'C') {
            road[i].push_back(1);
         } else {
            road[i].push_back(0);
         }
      }
   }

   int res{};
   for (int i = 0; i < n; ++i) {
      if ((road[i][0] + road[i][1] + road[i][2]) == -3) {
         break;
      }
      if (i > 0) {
         for (int j = 0; j < 3; ++j) {
            if (road[i][j] != -1) {
               int max_prev{};
               if (j == 0) { 
                  max_prev = std::max(road[i - 1][0], road[i - 1][1]); 
               } else if (j == 1) {
                  max_prev = std::max({road[i - 1][0], road[i - 1][1], road[i -1][2]});
               } else {
                  max_prev = std::max(road[i - 1][1], road[i - 1][2]);
               }
               road[i][j] = (max_prev != -1) ? max_prev + road[i][j] : -1;
            }
         }
      }
      res = std::max({road[i][0], road[i][1], road[i][2], res}); 
   }

   std::cout << res;

   return 0;
}
