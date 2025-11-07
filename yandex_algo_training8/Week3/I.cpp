#include <fstream>
#include <string>
#include <stack>
#include <map>
#include <cctype>
#include <algorithm>
#include <vector>

struct Node {
   char data;
   Node *left;
   Node *right;

   int operator_col;
   int width;

   Node(char val) : data(val), left(nullptr), right(nullptr) {}
   ~Node(){
      delete left;
      delete right;
   }
};

struct Size {int h; int w; };

Size get_size(Node *node) {
   if (!node->left || !node->right) { return Size{1, 1}; } 
   Size left = get_size(node->left);
   Size right = get_size(node->right);
   int h = std::max(left.h, right.h) + 2;
   int w = left.w + right.w + 5;
   return Size{h, w};
}

void get_data(Node *node, int col, const std::vector<std::vector<char>>& canvas) {
   if (!node->left || !node->right) { 
      return; 
   }
   int w_left = get_size(node->left).w;
   int w_right = get_size(node->right).w;
   node->operator_col = col + w_left + 2;
   node->left->width = w_left;
   node->right->width = w_right;
   get_data(node->left, col, canvas);
   get_data(node->right, col + w_left + 5, canvas);
}

void draw(Node *node, int row, int col, std::vector<std::vector<char>>& canvas) {
   if (!node->left || !node->right) {
      canvas[row][col] = node->data;
      return;
   }

   int op_col = node->operator_col;
   canvas[row][op_col] = node->data;
   canvas[row][op_col - 1] = '[';
   canvas[row][op_col + 1] = ']';

   int op_left = node->left->operator_col;
   if (!op_left) { 
      op_left = col;
   }
   for (int i = op_left + 1; i < op_col - 1; ++i) {
      canvas[row][i] = '-';
   }
   canvas[row][op_left] = '.';
   canvas[row + 1][op_left] = '|';

   int right_shift = col + node->left->width + 5;
   int op_right = node->right->operator_col; 
   if (!op_right) {
      op_right = right_shift;
   }

   for (int i = op_col + 2; i < op_right; ++i) {
      canvas[row][i] = '-';
   } 

   canvas[row][op_right] = '.';
   canvas[row + 1][op_right] = '|';

   draw(node->left, row + 2, col, canvas);
   draw(node->right, row + 2, right_shift, canvas);
} 

std::map<char, int> pr {
   {')', 0},
   {'+', 1},
   {'-', 1},
   {'*', 2},
   {'/', 2},
   {'^', 3}
};


int main() {
   std::ifstream file("input.txt");
   std::string str;
   file >> str;
   str = "(" + str + ")";

   std::stack<Node *> nodes;
   std::stack<char> chars;
   for (char ch : str) {
      if (ch == '(') {
         chars.push(ch);

      } else if (std::isalpha(ch)) {
         Node *new_node = new Node(ch);
         nodes.push(new_node);

      } else if (pr[ch] > 0) {
         while (!chars.empty() && chars.top() != '('
         && ((ch != '^' && pr[chars.top()] >= pr[ch])
         || (ch == '^' && pr[chars.top()] > pr[ch]))) {

            Node *new_node = new Node(chars.top());
            chars.pop();

            new_node->right = nodes.top();
            nodes.pop();
            new_node->left = nodes.top();
            nodes.pop();
            
            nodes.push(new_node);
         }
         chars.push(ch);

      } else if (ch == ')') {
         while (!chars.empty() && chars.top() != '(') {
            Node *new_node = new Node(chars.top());
            chars.pop();
            new_node->right = nodes.top();
            nodes.pop();
            new_node->left = nodes.top();
            nodes.pop();
            nodes.push(new_node);
         }
         chars.pop();
      }
   }
   Node *root = nodes.top();
   Size ttl_sz = get_size(root);
   root->width = ttl_sz.w;
   std::vector<std::vector<char>> canvas(ttl_sz.h, std::vector<char>(ttl_sz.w, ' '));
   get_data(root, 0, canvas);

   draw(root, 0, 0, canvas);

   std::ofstream out("output.txt");
   for (const auto& line : canvas) {
      for (char ch : line) {
         out << ch;
      }
      out << '\n';
   }

   delete root;
   return 0;
}
