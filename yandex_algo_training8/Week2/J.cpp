#include <iostream>
#include <vector>
#include <algorithm>

struct Store{
   int P;
   int R;
   int Q;
   int F;
};

int main() {
   int N{};
   int L{};
   std::cin >> N >> L;

   int res{1};
   int supply{};
   std::vector<Store> stores(N);
   for (int i = 0; i < N; ++i) {
      std::cin >> stores[i].P >> stores[i].R >> stores[i].Q >> stores[i].F;
      supply += stores[i].F;
   }

   if (supply < L) { res = 0; }
   if (res) {
      std::vector<std::vector<int>> dp(N, std::vector<int>(supply + 1, 10000001));
      std::vector<std::vector<int>> ans(N, std::vector<int>(supply + 1));
      int max_sz = stores[0].F;
      for (int i = 0; i <= max_sz; ++i) {
         dp[0][i] = (i < stores[0].R) ? (i * stores[0].P) : (i * stores[0].Q);
      }

      for (int i = 1; i < N; ++i) {
         max_sz += stores[i].F;
         std::vector<int> cache_func(max_sz + 1, 10000001);
         for (int m = 0; m <= stores[i].F; ++m) {
            cache_func[m] = (m < stores[i].R) ? (m * stores[i].P) : (m * stores[i].Q);
         }
         for (int j = 0; j <= max_sz; ++j) { 
            dp[i][j] = dp[i - 1][j];
            int max_k = std::min(j, stores[i].F);
            for (int k = 0; k <= max_k; ++k) {
               int option = cache_func[k] + dp[i - 1][j - k];
               if (option < dp[i][j]) { 
                  dp[i][j] = option;
                  ans[i][j] = k;
               }
            }
         }
      }

      int ttl_price{dp[N-1][L]};
      int id{L};
      for (int i = L + 1; i < supply; ++i) {
         if (dp[N-1][i] < ttl_price) {
            ttl_price = dp[N-1][i];
            id = i;
         }
      }
      std::cout << ttl_price << '\n';

      std::vector<int> quant;
      for (int i = N - 1; i > 0; --i) {
         quant.push_back(ans[i][id]);
         id = id - ans[i][id];
      }
      quant.push_back(id);

      int sz = quant.size() - 1;
      for (int i = sz; i >= 0; --i) {
         std::cout << quant[i] << ' ';
      }

   } else {
      std:: cout << -1;
   }

   return 0;
}
