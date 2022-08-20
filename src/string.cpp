#include "string.hpp"

const std::string& operator||(const std::string& left, const std::string& right)
{
    if(left.empty()) return right;
    return left;
}

std::string uva::string::tolower(const std::string& __str)
{
    std::string str;
    str.reserve(__str.size());

    for(const char& c : __str) {
        if(isalpha(c)) {
            str.push_back(std::tolower(c));
        } else {
            str.push_back(c);
        }
    }

    return str;
}

std::string uva::string::prefix_sufix(const std::string& str, const std::string& prefix, const std::string& sufix)
{
    std::stringstream ss;

    if(prefix.size()) {
        ss << prefix;
    }

    ss << str;

    if(sufix.size()) {
        ss << sufix;
    }

    return ss.str();
}