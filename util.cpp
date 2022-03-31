#include <iostream>
#include <vector>
#include <sstream>
#include <string>

std::vector<std::string> split(const std::string& s, char delemiter) {
    std::vector<std::string> out{};
    std::stringstream ss {s};
    std::string item;

    while (std::getline(ss, item, delemiter)) {
        out.push_back(item);
    }
    return out;
}

bool is_prefix(const std::string& s, const std::string& of) {
    if (s.size() > of.size()) return false;
    return std::equal(s.begin(), s.end(), of.begin());
}