#include <iostream>
#include <vector>
#include <iomanip>

struct Word {int a; int b; };

bool is_scalable(double k, int W, int H, const std::vector<Word>& words) {
   double height{words[0].b * k};
   double ttl_width{};
   double ttl_height{height};

   for (const auto& word : words) {
      double ka = k * word.a;
      double kb = k * word.b;
      if (ka > W || kb > H) { return false; }
      if (kb != height || ttl_width + ka > W) { 
         ttl_width = ka;
         height = kb;
         ttl_height += height;
         if (ttl_height > H)  { return false; }
      } else {
         ttl_width += ka;
      }
   }
   return ttl_height <= H;
}

int main() {
   int N{};
   int W{};
   int H{};
   std::cin >> N >> W >> H;
   std::vector<Word> words(N);
   for (int i = 0; i < N; ++i) {
      std::cin >> words[i].a >> words[i].b;
   }

   const double eps =  0.0000001;
   double left{};
   double right = W + H;
   double mid{};
   while (left + eps < right) {
      mid = (left + right) / 2;
      if (!is_scalable(mid, W, H, words)) {
         right = mid;
      } else {
         left = mid;
      } 
   }

   std::cout << std::fixed << std::setprecision(7) << left;

   return 0;
}
