#pragma once

#include <string>

namespace andy
{
    namespace string
    {
        /**
         *  @brief Converts all characters of @a __str to it's lowercase representation.
         *  @param  __str The string to be converted.
         *  @return @a __str in lowercase.
         */
        std::string to_lower(std::string __str);
        /**
         *  @brief Converts all characters of @a __str to it's uppercase representation.
         *  @param  __str The string to be converted.
         *  @return @a __str in uppercase.
         */
        std::string to_upper(std::string __str);
        /**
         *  @brief Converts a camelCase, PascalCase or kebab-case string to snake_case.
         *  @param  s The string to be converted.
         *  @return @a s in snake_case.
         */
        std::string to_snake_case(const std::string& s);
    };
};