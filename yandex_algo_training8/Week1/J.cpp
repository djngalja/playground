#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

struct ListView {
    std::vector<int>& vec;
    size_t begin;

    ListView(std::vector<int>& v, size_t b) : vec(v), begin{b} {}
    ListView(const ListView& lv, size_t b) : vec(lv.vec), begin{lv.begin + b - 1} {}

    void set(size_t id, int val) {
        vec[begin + id - 1] = val;
    }
    int get(size_t id) const {
        return vec[begin + id - 1];
    }
};

void get_nums(std::vector<int>& target, const std::string& src) {
    size_t pos1 = src.find("(");
    size_t pos2 = src.find(")");
    std::istringstream nums(src.substr(pos1, pos2 - pos1));
    char ch;
    int num{};
    while(nums >> ch >> num) {
        target.push_back(num);
    }
}

int get_num(const std::string& src) {
    size_t pos1 = src.find("(");
    size_t pos2 = src.find(")");
    return stoi(src.substr(pos1 + 1, pos2 - pos1 - 1));
}

std::string get_name_list(const std::string& src) {
    std::istringstream words(src);
    std::string res;
    for (int i = 0; i < 2; ++i) {
        words >> res;
    }
    return res;
}

std::string get_name(const std::string& src) {
    auto len = src.find(".");
    return src.substr(0, len);
}

std::string get_name_list2(const std::string& src) {
    std::istringstream words(src);
    std::string temp;
    for (int i = 0; i < 4; ++i) {
        words >> temp;
    }
    return get_name(temp);
}

int main() {
    int n{};
    std::cin >> n;
    std::cin.ignore();

    std::unordered_map<std::string, std::vector<int>> data;
    std::unordered_map<std::string, ListView> lists;
    std::vector<int> res;

    for (int i = 0; i < n; ++i) {
        std::string temp_str;
        getline(std::cin, temp_str);

        if (temp_str.find(" new ") != std::string::npos) {
            std::string name = get_name_list(temp_str);
            std::vector<int> temp_vec;
            get_nums(temp_vec, temp_str);
            data[name] = temp_vec;
            lists.emplace(name, ListView(data[name], 0));

        } else if (temp_str.find(".add(") != std::string::npos) {
            std::string name = get_name(temp_str);
            int num = get_num(temp_str);
            data[name].push_back(num);

        } else if (temp_str.find(".get(") != std::string::npos) {
            std::string name = get_name(temp_str);
            int num = get_num(temp_str);
            res.push_back(lists.at(name).get(num));
            
        } else if (temp_str.find(".set(") != std::string::npos) {
            std::string name = get_name(temp_str);
            std::vector<int> temp_vec;
            get_nums(temp_vec, temp_str);
            lists.at(name).set(temp_vec[0], temp_vec[1]);

        } else {
            if (!temp_str.empty()) {
                std::string name = get_name_list(temp_str);
                std::string name2 = get_name_list2(temp_str);
                std::vector<int> temp_vec;
                get_nums(temp_vec, temp_str);
                lists.emplace(name, ListView(lists.at(name2), temp_vec[0]));
            }
        }

    }
    
    for (int num : res) {
        std::cout << num << '\n';
    }

    return 0;
}
