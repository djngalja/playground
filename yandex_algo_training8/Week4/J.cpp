#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <map>

struct Car {
   double x;
   double y;
   double vx;
   double vy;
};

enum class Type { Wall, Finish, Collision };

struct Event {
   double t;
   int id;
   Type type;
   std::vector<int> collisions{};

   bool operator<(const Event& other) const {
      if (t != other.t) {
         return t < other.t;
      } else {
         if (type == Type::Wall && 
            (other.type == Type::Finish || other.type == Type::Collision)) {
            return true;
         } 
         if (type == Type::Collision && other.type == Type::Finish) {
            return true;
         }
         return false;
      }
   }
};

Event hit_wall(const Car& car, int car_id, int W, int L) {
   Event wall{0.0, car_id, Type::Wall};
   if (car.vy > 0) {
      wall.t = (W - car.y) / car.vy;
   } else if (car.vy < 0) {
      wall.t = -car.y / car.vy; 
   } else { // car.vy == 0
      if (car.y == 0 || car.y == W) {
         wall.t = 0;
      } else {
         wall.t = -1;
      }
   }
   if (car.x + wall.t * car.vx > L) {
      wall.t = -1;
   }  
   return wall;
}

Event finish(const Car& car, int car_id, int L) {
   Event finish{0.0, car_id, Type::Finish};
   if (car.vx < 0) {
      finish.t = -1;
   } else if (car.vx == 0) {
      if (car.x == L) {
         finish.t = 0;
      } else {
         finish.t = -1;
      }
   } else {
      finish.t = (L - car.x) / car.vx;
   }
   return finish;
}


int main() {
   int N{};
   double L{};
   double W{};
   std::ifstream file("input.txt");
   file >> N >> L >> W;
   std::vector<Car> cars(N);
   for (int i = 0; i < N; ++i) {
      file >> cars[i].x >> cars[i].y >> cars[i].vx >> cars[i].vy;
   }

   std::vector<Event> events;
   for (int i = 0; i < N; ++i) {
      Event wall = hit_wall(cars[i], i, W, L);
      if (wall.t != -1) {
         events.push_back(wall);
      }
      Event fin = finish(cars[i], i, L);
      if (fin.t != -1) {
         events.push_back(fin);
      }

      std::map<double, std::vector<int>> data;
      for (int j = i + 1; j < N; ++j) {
         double t{};
         if (cars[i].vx == cars[j].vx && cars[i].vy == cars[j].vy) { continue; }
         if (cars[i].vx == cars[j].vx && cars[i].x == cars[j].x) {
            t = (cars[i].y - cars[j].y) / (cars[j].vy - cars[i].vy);
            if (t > 0) {
               data[t].push_back(j);
            }
         } else if (cars[i].vy == cars[j].vy && cars[i].y == cars[j].y) {
            t = (cars[i].x - cars[j].x) / (cars[j].vx - cars[i].vx);
            if (t > 0) {
               data[t].push_back(j);
            }    
         } else {
            if (cars[i].vx == cars[j].vx || cars[i].vy == cars[j].vy) { continue; }
            t = (cars[i].x - cars[j].x) / (cars[j].vx - cars[i].vx);
            if (t > 0 && t == (cars[i].y - cars[j].y) / (cars[j].vy - cars[i].vy)) {
               data[t].push_back(j);
            }
         }
      }

      for (const auto& pair : data) {
         events.push_back(Event{pair.first, i, Type::Collision, pair.second});
      }
   }

   std::sort(events.begin(), events.end());
   std::unordered_set<int> not_active;
   std::vector<int> res;
   double win_time{-1};

   int sz = events.size();
   for (int i = 0; i < sz; ++i) {
      if (events[i].type == Type::Wall) {
         not_active.insert(events[i].id);
      } else if (events[i].type == Type::Finish) {
         if (not_active.find(events[i].id) == not_active.end()) {
            if (win_time == -1) { 
               win_time = events[i].t;
               res.push_back(events[i].id);
            } else if (win_time == events[i].t) {
               res.push_back(events[i].id);
            } else {
               break;
            }  
         }
      } else { // Type::Collision
         if (not_active.find(events[i].id) != not_active.end()) {
            continue;
         }

         bool is_collision{};
         for (int col_id : events[i].collisions) {
            if (not_active.find(col_id) == not_active.end()) {
               is_collision = true;
               break;
            }
         }
         if(!is_collision) { continue; }

         not_active.insert(events[i].id);
         for (int col_id : events[i].collisions) {
            not_active.insert(col_id);
         }
      }
   }

   std::sort(res.begin(), res.end());
   int cnt = res.size();
   std::ofstream out("output.txt");
   out << cnt << '\n';
   if (cnt > 0) {
      for (int i : res) {
         out << i + 1 << ' ';
      }
   }
   return 0;
}
