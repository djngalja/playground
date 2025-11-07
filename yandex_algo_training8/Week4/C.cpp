#include <fstream>
#include <vector>

int main() {
   std::ifstream file("input.txt");
   int n{};
   int x{};
   file >> n  >> x;

   int cnt{};
   std::vector<int> candidates(n);
   std::vector<int> prof_cnt(n + 1);
   for (int i = 0; i < n; ++i) {
      file >> candidates[i];
      if (candidates[i] >= x) { 
         prof_cnt[i + 1] = ++cnt;
      } else {
         prof_cnt[i + 1] = cnt;
      }
   }

   int m{};
   file >> m;

   std::vector<int> res;
   int shift{};
   int left{};
   for (int i = 0; i < m; ++i) {
      int event{};
      file >> event;
      switch (event) {
         case 1: {
            int a{};
            file >> a;
            if (a >= x) { ++cnt; }
            prof_cnt.push_back(cnt);
            candidates.push_back(a);
            break;
         }
         case 2: {
            if (candidates[shift] >= x) { ++left; }
            ++shift;
            break;
         } 
         case 3: {
            int k{};
            file >> k;
            res.push_back(prof_cnt[k + shift] - left);
            break;
         }  
      }
   }
   
   std::ofstream out("output.txt");
   for (int num : res) {
      out << num << '\n';
   }
 
   return 0;
}
