// E. Финикийские сообщения (лето 2025)

#include <iostream>
#include <string>
#include <vector>
#include <map>

bool get_msg(const std::string&, const std::map<std::string, std::string>&, std::vector<std::string>&);
std::string encode_word(const std::string&);
std::string decode_msg(const std::string&, const std::vector<std::string>&);
void test(const std::string&, const std::vector<std::string>&);




int main() {
    test("7788266888674499977774442227777", {"WORLD", "QUANTUM", "HELLO", "PHYSICS", "PHYS"});
    test("443355555566696667775553", {"WORLD", "QUANTUM", "HELLO"});
    test("778826688867449997777444222777777882668886744999777744422277777788266888674499977774442227777",
        {"WORLD", "QUANTUM", "HELLO", "PHYSICS", "PHYS"});
    test("443355555566696667775553", {"WORLD", "QUANTUM", "HELLO", "PHYSICS", "PHYS", "HELL", "YELLOW", "LOW", "SICS", "WORD"});

    // No output expected
    test("7788266888674499977774442227777", {});
    test("", {"WORLD", "QUANTUM", "HELLO", "PHYSICS", "PHYS"});
    test("7788266888674499977774442227777", {"WORLD", "QUANTUM", "HELLO", "PHYS"}); // Message cannot be decoded

    return 0;
}




void test(const std::string& s, const std::vector<std::string>& dictionary) {
    std::cout << decode_msg(s, dictionary) << '\n';
}


std::string decode_msg(const std::string& s, const std::vector<std::string>& dictionary) {
    std::string msg;
    if (s.empty() || dictionary.empty()) {
        return msg;
    }
    // Update the dictionary so that it also includes encoded versions of the words
    std::map<std::string, std::string> new_dictionary;
    for (const auto& word : dictionary) {
        new_dictionary[word] = encode_word(word);
    }
    std::vector<std::string> words_found;
    if (get_msg(s, new_dictionary, words_found)) {
        for (const auto& str : words_found) { msg += str + ' '; }
        msg.pop_back();
    }
    return msg;
}


std::string encode_word(const std::string& word) {
    std::map<char, std::string> dict = {
        {'2', "ABC"}, {'3', "DEF"}, {'4', "GHI"},
        {'5', "JKL"}, {'6', "MNO"}, {'7', "PQRS"},
        {'8', "TUV"}, {'9', "WXYZ"}
    };
    // Update the dictionary so that letters are keys now
    std::map<char, char> new_dict;
    for (const auto& p : dict) {
        for (char letter : p.second) {
            new_dict[letter] = p.first;
        }
    }
    // Encode a given word
    std::string result;
    for (char c : word) {
        char digit = new_dict[c];
        // According to the task, the position of letter is the number of times it should be repeated in a secret message
        auto pos = dict[digit].find(c);
        for (std::size_t i = 0; i <= pos; ++i) {
            result += digit;
        }
    }
    return result;
}


bool get_msg(const std::string& s, const std::map<std::string, std::string>& new_dictionary,
    std::vector<std::string>& result) {
    if (s.empty()) { return true; }
    for (const auto& word : new_dictionary) {
        if (s.find(word.second) != 0) { continue; }
        if (get_msg(s.substr(word.second.size()), new_dictionary, result)) {
            result.insert(result.begin(), word.first);
            return true;
        }
    }
    return false;
}
