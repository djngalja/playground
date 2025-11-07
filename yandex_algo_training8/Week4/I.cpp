#include <iostream>
#include <set>
#include <cmath>
#include <tuple>

struct Point {
   long x{};
   long y{};

   bool operator<(const Point& other) const {
      return std::tie(x, y) < std::tie(other.x, other.y);
   }
};

int main() {
   int n{};
   long d{};
   std::cin >> n >> d;

   std::set<Point> points;
   for (int i = 0; i < n; ++i) {
      long x{};
      long y{};
      std::cin >> x >> y;
      points.insert(Point{x, y});
   }

   std::set<Point> dist;
   long sqrt_d = std::sqrt(d);
   for (long dx = 0; dx <= sqrt_d; ++dx) {
      long dy_2 = d - dx * dx;
      long dy = std::sqrt(dy_2);
      if (dy * dy != dy_2) { continue; }
      if (dx == 0 && dy == 0) { continue; }
      if (dx != 0 && dy != 0) { 
         dist.insert(Point{dx, -dy}); 
      }
      dist.insert(Point{dx, dy}); 
   }

   long res{};
   for (const auto& di : dist) {
      for (const auto& pt : points) {
         Point new_pt{pt.x + di.x, pt.y + di.y};
         if (points.find(new_pt) != points.end()) {
            ++ res;
         }
      }
   }

   std::cout << res;

   return 0;
}
