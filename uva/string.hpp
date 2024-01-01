#pragma once

#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <functional>
#include <map>
#include <format.hpp>
#include <chrono>

const std::string& operator||(const std::string& left, const std::string& right);

namespace uva
{
    namespace string
    {
        template <auto left, auto right, typename = void>
        struct function_is_same : std::false_type {};

        template <auto left, auto right>
        struct function_is_same<left, right, std::enable_if_t<left == right>> : std::true_type {};

        template<typename T>
        struct has_const_iterator
        {
        private:
            typedef char                      yes;
            typedef struct { char array[2]; } no;

            template<typename C> static yes test(typename C::const_iterator*);
            template<typename C> static no  test(...);
        public:
            static const bool value = sizeof(test<T>(0)) == sizeof(yes);
            typedef T type;
        };

        template <typename T>
        struct has_begin_end
        {
            template<typename C> static char (&f(typename std::enable_if<
            std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::begin)),
            typename C::const_iterator(C::*)() const>::value, void>::type*))[1];

            template<typename C> static char (&f(...))[2];

            template<typename C> static char (&g(typename std::enable_if<
            std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::end)),
            typename C::const_iterator(C::*)() const>::value, void>::type*))[1];

            template<typename C> static char (&g(...))[2];

            static bool const beg_value = sizeof(f<T>(0)) == 1;
            static bool const end_value = sizeof(g<T>(0)) == 1;
        };

        template<typename T> 
        struct is_container : std::integral_constant<bool, has_const_iterator<T>::value && has_begin_end<T>::beg_value && has_begin_end<T>::end_value> 
        { };

        template <typename T, typename = int>
        struct is_reservable : std::false_type { };

        template <typename T>
        struct is_reservable <T, decltype(&T::reserve, 0)> : std::true_type { };

        template <typename>
        struct is_pair : std::false_type { };

        template <typename k, typename v>
        struct is_pair<std::pair<k, v>> : std::true_type { };

        template <typename>
        struct is_map : std::false_type { };

        template <typename k, typename v>
        struct is_map<std::map<k, v>> : std::true_type { };

        template<typename T>
        struct is_pointer { static const bool value = false; };

        template<typename T>
        struct is_pointer<T*> { static const bool value = true; };

        template<typename C, typename V>
        void add_to_container(C& container, V&& value) {
            if constexpr(is_map<C>::value)
            {  
                container.insert(std::forward<V>(value));
            } else
            {
                container.push_back(std::forward<V>(value));
            }
        }

        template<typename T>
        struct rebinder;

        template<template<typename...> typename T, typename... Args>
        struct rebinder<T<Args...>> {
            template<typename... Us>
            using rebind = T<Us...>;
        };

        template<typename T, typename... Us>
        using rebound = rebinder<T>::template rebind<Us...>;

        std::string tolower(const std::string& __str);
        std::string toupper(const std::string& __str);

        template<typename T>
        std::string join(const std::vector<T>& array, const std::string_view& separator = "")
        {
            if(array.empty()) {
                return "";
            }

            std::string ss;
            ss.reserve(array.size()*20);

            for(int index = 0; index < array.size()-1; ++index)
            {
                ss.append(std::format("{}", array[index]));
                ss.append(separator);
            }

            if(!array.empty())
            {
                ss.append(std::format("{}", array.back()));
            }

            return ss;
        }

        template<typename T>
        std::string join(const std::vector<T>& array, const char& separator = '\0')
        {
            return join(array, std::string_view(&separator, 1));
        }

        template<typename T>
        std::string join(const std::vector<T>& array, const char* separator = '\0')
        {
            return join(array, std::string_view(separator));
        }
        // template<typename key, typename value>
        // void join_append_iterator(std::string& str, const std::map<typename key, typename value>::iterator& it)
        // {
        //     if constexpr(std::is_same<std::string, key>::value)
        //     {
        //         str.append(std::format("'{}': {}", it->first, it->second));
        //     }
        //     else 
        //     {
        //         str.append(std::format("{}: {}", it->first, it->second));
        //     }
        // }
        // template<typename key, typename value>
        // std::string join(const std::map<typename key, typename value>& map, const std::string_view& separator = "")
        // {
        //     if(map.empty()) {
        //         return "";
        //     }

        //     std::string ss;
        //     ss.reserve(map.size()*50);

        //     for(auto it = map.begin(); it < map.end()-1; ++it)
        //     {
        //         join_append_iterator(ss, it);
        //         ss.append(separator);
        //     }

        //     if(!map.empty())
        //     {
        //         join_append_iterator(ss, map.end()-1);
        //     }

        //     return ss;
        // }

        template <class map, typename function>
        auto join(const map& m, function f)
        {
            std::vector<decltype(f(typename map::value_type()))> values;

            for(const typename map::value_type& val : m)
            {
                values.push_back(std::move(f(val)));
            }

            return values;
        }

        template<typename map>
        std::pair<std::vector<typename map::key_type>, std::vector<typename map::mapped_type>> split(const map& __map)
        {
            std::vector<typename map::key_type> keys;
            std::vector<typename map::mapped_type> values;

            for(auto& pair : __map)
            {
                keys.push_back(pair.first);
                values.push_back(pair.second);
            }

            return std::make_pair(keys, values);
        }
        
        template<class container>
        container select(const container& values, std::function<bool(const typename container::value_type&)> f)
        {
            container results;

            for(const auto& val : values) {
                if(f(val)) {
                    add_to_container(results, val);
                }
            }
            return results;
        }

        template<typename container, typename function>
        auto map(const container& values, function f)
        {
            using out_container = rebound<container, decltype(f(values[0]))>;
            out_container out_values;

            if constexpr (is_reservable<out_container>::value)
            {
                out_values.reserve(values.size());
            }

            for(const auto& value : values)
            {
                out_values.push_back(std::move(f(value)));
            }

            return out_values;
        }

        std::string prefix_sufix(const std::string& str, const std::string& prefix, const std::string& sufix);

        std::string split_on_upper(const std::string& s, char separator = '-');

        std::string to_snake_case(const std::string& s);

        std::string replace(const std::string& str, const char& find, const char& replace);

        std::vector<std::string_view> tokenize(std::string_view str);

        /**
         *  @brief  Removes duplicated values in @a __vector.
         *  @param __vector The vector containing duplicated (or not) values
         *  @return  A new vector by removing duplicate values.
        */
        template<typename T>
        std::vector<T> uniq(const std::vector<T>& __vector)
        {
            std::vector<T> results;
            results.reserve(__vector.size());

            for(const auto& value : __vector) {
                if(std::find(results.begin(), results.end(), value) == results.end())
                {
                    results.push_back(value);
                }
            }

            return results;
        }
        /**
         *  @brief Converts the starting letters of all words of @a __string to it's uppercase representation.
         *  @param  __string The string to be capitalized.
         *  @return A capitalized copy of @a __string.
         */
        std::string capitalize(const std::string& __string);
        /**
         *  @brief Check if a string ends with one of the @a __suffixes
         *  @param  __string To be checked.
         *  @param  __suffixes To be searched.
         *  @return True if @a __string ends_with one of the @a __suffixes, false otherwise.
         */
        bool ends_with(const std::string& __string, const std::vector<std::string>& __suffixes);
        /**
         *  @brief Check if character is a vowel.
         *  @param  __c To be checked.
         *  @return True if @a __c is vowel, false otherwise.
         */
        bool isvowel(const char& __c);
        /**
         *  @brief Check if character is a consonant.
         *  @param  __c To be checked.
         *  @return True if @a __c is consonant, false otherwise.
         */
        bool isconsonant(const char& __c);
        /**
         *  @brief Converts an (english) word to it's plural. It covers almost every english rule.
         *  @param  __string To be pluralized.
         *  @return A pluralized copy of @a __string.
         */
        std::string pluralize(std::string __string);

        template<typename duration>
        std::string format_duration(const duration& __duration, const char* repre)
        {
            return std::format("{}{}", __duration.count(), repre);
        }

        template<typename to_cast, typename duration>
        bool format_duration_if_can(const duration& __duration, std::string& output, int max, const char* repre)
        {
            to_cast casted_duration = std::chrono::duration_cast<to_cast>(__duration);

            //There is 1000 nanoseconds in one microsecond
            auto count = casted_duration.count();
            if(count < max)
            {
                output = format_duration(casted_duration, repre);
                return true;
            }

            return false;
        }

        template<typename duration_type>
        std::string pretty_format_duration(duration_type duration)
        {
            std::string output;
            if(format_duration_if_can<std::chrono::nanoseconds, duration_type>(duration, output, 1000, "ns"))
            {
                return output;
            }

            if(format_duration_if_can<std::chrono::microseconds, duration_type>(duration, output, 1000, "μs"))
            {
                return output;
            }

            if(format_duration_if_can<std::chrono::milliseconds, duration_type>(duration, output, 1000, "ms"))
            {
                return output;
            }

            if(format_duration_if_can<std::chrono::duration<float, std::ratio<1>>, duration_type>(duration, output, 60, "s"))
            {
                return output;
            }

            if(format_duration_if_can<std::chrono::duration<float, std::ratio<60>>, duration_type>(duration, output, 60, "m"))
            {
                return output;
            }

            return format_duration(duration, "h");
        }

        template<typename char_type>
        std::basic_string<char_type> unescape(const std::basic_string_view<char_type>& __str)
        {
            std::string output;
            output.reserve(__str.size());

            const char* start = __str.data();
            const char* it    = start;

            const char* end   = __str.data() + __str.size();

            bool escaping = false;

            while(it < end) {
                if(escaping) {
                    switch (*it)
                    {
                    case '\\':
                    case '"':
                    case '\'':
                        output.push_back(*it);
                        break;
                    default:
                        throw std::runtime_error("cannot escape.");
                        break;
                    }

                    escaping = false;
                } else if(*it == '\\')
                {
                    escaping = true;
                } else {
                    output.push_back(*it);
                }

                ++it;
            }
            
            return output;
        }
    };
};