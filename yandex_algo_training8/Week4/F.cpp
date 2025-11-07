#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

enum class Type { Block, Free, Car };
struct Event {
   double t;
   Type type;
   int car_id;

   bool operator<(const Event& other) {
      if (t != other.t) {
         return t < other.t;
      } else {
         if (type == Type::Block && (other.type == Type::Free || other.type == Type::Car)) {
            return true;
         }
         if (type == Type::Car && other.type == Type::Free) {
            return true;
         }
         return false;
      }
   }
};

int main() {
   std::ifstream file("input.txt");
   int n{};
   int m{};
   double x{};
   file >> n >> m >> x;
   
   std::vector<Event> events;
   for (int i = 0; i < n; ++i) {
      double a{};
      double b{};
      double v{};
      file >> a >> b >> v;

      if (a > b) { v *= -1; }
      double ta = (x - a) / v;
      double tb = (x - b) / v;
      double t1 = std::min(ta, tb);
      double t2 = std::max(ta, tb);

      events.push_back(Event{t1, Type::Block, 0});
      events.push_back(Event{t2, Type::Free, 0});
   }

   for (int i = 0; i < m; ++i) {
      Event event{0.0, Type::Car, 0};
      file >> event.t;
      event.car_id = i;
      events.push_back(event);
   }

   std::sort(events.begin(), events.end());

   std::vector<double> res(m);
   int blocks{};
   int sz = events.size();
   std::queue<int> car_ids;

   for (int i = 0; i < sz; ++i) {
      if (events[i].type == Type::Free) {
         --blocks;
         if (!blocks) {
            while(!car_ids.empty()) {
               res[car_ids.front()] = events[i].t;
               car_ids.pop();
            }
         }
      } else if (events[i].type == Type::Car) {
         if (!blocks) {
            res[events[i].car_id] = events[i].t;
         } else {
            car_ids.push(events[i].car_id);
         }
      } else {
         ++blocks;
      }
   }

   std::ofstream out("output.txt"); 
   for (double time : res) {
      out << std::fixed << std::setprecision(6) << time << '\n';
   }

   return 0;
}
