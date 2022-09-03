#pragma once

#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <functional>
#include <map>

const std::string& operator||(const std::string& left, const std::string& right);

namespace uva
{
    namespace string
    {
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

        template<typename T>
        std::string join(std::vector<T> array, const std::string_view& separator = "")
        {
            std::stringstream ss;

            for(int index = 0; index < array.size()-1; ++index)
            {
                ss << array[index];
                ss << separator;
            }

            if(!array.empty())
            {
                ss << array.back();
            }

            return ss.str();
        }

        template<typename T>
        std::string join(std::vector<T> array, const char& separator = '\0')
        {
            return join(array, std::string_view(&separator, 1));
        }

        template<typename T>
        std::string join(std::vector<T> array, const char* separator = '\0')
        {
            return join(array, std::string_view(separator));
        }

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
    };
};