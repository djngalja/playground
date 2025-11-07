#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

enum class Type {
   Arrive_to_1,
   Arrive_to_2,
   Depart_from_1,
   Depart_from_2
};

struct Event {
   int time; 
   Type type;

   bool operator<(const Event& other) const {
      if (time != other.time) {
         return time < other.time;
      } else {
         if ((type == Type::Arrive_to_1 || type == Type::Arrive_to_2) 
         && (other.type == Type::Depart_from_1 || other.type == Type::Depart_from_2)) { 
            return true;
         } else {
            return false;
         }
      }
   }
};

int main() {
   std::ifstream file("input.txt");
   int N{};
   file >> N;

   std::vector<Event> events;
   for (int i = 0; i < N; ++i) {
      std::string temp;
      file >> temp;
      Event event1{0, Type::Depart_from_1};
      Event event2{0, Type::Arrive_to_2};
      event1.time = std::stoi(temp.substr(0, 2)) * 60 + std::stoi(temp.substr(3, 2));
      event2.time = std::stoi(temp.substr(6, 2)) * 60 + std::stoi(temp.substr(9, 2));
      events.push_back(event1);
      events.push_back(event2);
   }

   int M{};
   file >> M;

   for (int i = 0; i < M; ++i) {
      std::string temp;
      file >> temp;
      Event event1{0, Type::Depart_from_2};
      Event event2{0, Type::Arrive_to_1};
      event1.time = std::stoi(temp.substr(0, 2)) * 60 + std::stoi(temp.substr(3, 2));
      event2.time = std::stoi(temp.substr(6, 2)) * 60 + std::stoi(temp.substr(9, 2));
      events.push_back(event1);
      events.push_back(event2);
   }

   std::sort(events.begin(), events.end());

   int ttl_bus{};
   int bus1{};
   int bus2{};
   int sz = events.size();
   for (int i = 0; i < sz; ++i) {
      if (events[i].type == Type::Arrive_to_1) {
         ++bus1;
      } else if (events[i].type == Type::Arrive_to_2) {
         ++bus2;
      } else if (events[i].type == Type::Depart_from_1) {
         if (bus1) { --bus1; } 
         else { ++ttl_bus; }
      } else {
         if (bus2) { --bus2; } 
         else { ++ttl_bus; }
      }
   }

   std::cout << ttl_bus;
   
   return 0;
}
