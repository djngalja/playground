#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main() {
   std::string str;
   std::cin >> str;
   int N{};
   std::cin >> N;
   std::unordered_map<int, std::string> dict;
   for (int i = 0; i < N; ++i) {
      std::string temp;
      std::cin >> temp;
      dict.insert({i, temp});
   }

   size_t len = str.size();

   std::vector<std::vector<int>> table(len + 1);
   for (size_t i = 0; i < len; ++i) {
      if (i && table[i].empty()) {
         continue;
      }
      for (const auto& word : dict) {
         size_t wrd_len = word.second.size();
         if (word.second == str.substr(i, wrd_len)) {
            table[i + wrd_len] = table[i];
            table[i + wrd_len].push_back(word.first);
         }
      }
   }

   for (int id : table[len]) {
      std::cout << dict[id] << ' ';
   }

   return 0;
}
