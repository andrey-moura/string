#include "andy/string.hpp"

std::string andy::string::to_lower(std::string __str)
{
    for(char& c : __str) {
        if(c >= 'A' && c <= 'Z') {
            c =  c - 'A' + 'a';            
        }
    }

    return __str;
}

std::string andy::string::to_upper(std::string __str)
{
    for(char& c : __str) {
        if(c >= 'a' && c <= 'z') {
            c =  c - 'a' + 'A';            
        }
    }

    return __str;
}

std::string andy::string::to_snake_case(const std::string& s)
{
    std::string output;
    output.reserve(s.size() + s.size() / 4); // Reserve some extra space
    for(const char& c : s) {
        if(c == '-') {
            output += '_';
        } else if(c >= 'A' && c <= 'Z') {
            if(!output.empty() && output.back() != '_') {
                output += '_';
            }
            output += c - 'A' + 'a';
        } else {
            output += c;
        }
    }
    return output;
}