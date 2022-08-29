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

std::string uva::string::split_on_upper(const std::string& s, char separator)
{
    std::vector<size_t> splits;

    for (size_t i = 1; i < s.size()-1; i++)
    {
        if (isupper(s[i]) && !isupper(s[i + 1]) || isupper(s[i]) && !isupper(s[i - 1]))
        {
            splits.push_back(i);
        }
    }

    std::string output;

    size_t lastSplit = 0;
    for (const size_t& split : splits)
    {
        output.append(s.substr(lastSplit, split - lastSplit) + separator);
        lastSplit = split;
    }

    output.append(s.substr(lastSplit));

    for (char& c : output)
    {
        if (isalpha(c)) {
            c = std::tolower((int)c);
        }
    }

    return output;
}

std::string uva::string::to_snake_case(const std::string& s)
{
    return uva::string::split_on_upper(s, '_');
}

std::string uva::string::replace(const std::string& _str, const char& find, const char& replace)
{
    std::string str;
    str.reserve(_str.size());

    for(const char &c : _str)
    {
        if(c == find)
        {
            str.push_back(replace);
        } else 
        {
            str.push_back(c);
        }
    }

    return str;
}