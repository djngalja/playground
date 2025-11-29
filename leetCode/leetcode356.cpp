/* 356. Line Reflection
Given n points on a 2D plane, find if there is such a line parallel to the y-axis that reflects the given points symmetrically.
In other words, answer whether or not if there exists a line that after reflecting all points over the given line, 
the original points' set is the same as the reflected ones.
Note that there can be repeated points.

Example 1:
Input: points = [[1,1],[-1,1]]
Output: true
Explanation: We can choose the line x = 0.

Example 2:
Input: points = [[1,1],[-1,-1]]
Output: false
Explanation: We can't choose a line.

Constraints:
    n == points.length
    1 <= n <= 104
    -108 <= points[i][j] <= 108

Follow up: Could you do better than O(n2)? */

#include <iostream>
#include <vector>
#include <set>

struct Point { 
    int x; 
    int y; 
    bool operator<(const Point& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

bool reflection_line(const std::vector<std::vector<int>>& points) {
    int max_x{-109};
    int min_x{109};
    std::set<Point> dict;
    for (const auto& point : points) {
        if (point[0] > max_x) { max_x = point[0]; }
        if (point[0] < min_x) { min_x = point[0]; }
        dict.insert({point[0], point[1]});
    }
    int sum = max_x + min_x;
    for (const auto& point : points) {
        if (dict.find({sum - point[0], point[1]}) == dict.end()) { return false; }
    }
    return true;
}

int main() {
    //std::vector<std::vector<int>> points{{1,1}, {-1,-1}}; // -> false
    std::vector<std::vector<int>> points{{1,1}, {-1,1}}; // -> true
    std::cout << std::boolalpha << reflection_line(points);
    return 0;
}
