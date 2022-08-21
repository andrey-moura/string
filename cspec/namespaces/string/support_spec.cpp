#include <map>

#include <string.hpp>
#include <faker.hpp>

#include <cspec.hpp>

const std::vector<std::string> person_names =
{
    "Adams",
    "Baker",
    "Clark",
    "Davis",
    "Evans",
    "Frank",
    "Ghosh",
    "Hills",
    "Irwin",
    "Jones",
    "Klein",
    "Lopez",
    "Mason",
    "Nalty",
    "Ochoa",
    "Patel",
    "Quinn",
    "Reily",
    "Smith",
    "Trott",
    "Usman",
    "Valdo",
    "White",
    "Xiang",
    "Yakub",
    "Zafar",
};

std::map<int, std::string> romanNumeralsMap =
{
    { 1, "I" },
    { 2, "II" },
    { 3, "III" },
    { 4, "IV" },
    { 5, "V" },
    { 6, "VI" },
    { 7, "VII" },
    { 8, "VIII" },
    { 9, "IX" },
    { 10, "X" },
};

cspec_describe("uva::support",

    context("join",
        it("should join a map",[](){
            auto joined_roman_numerals = uva::string::join(romanNumeralsMap, [](const auto& number_roman) {
                return std::format("{}={}", number_roman.first, number_roman.second);
            });

            expect(joined_roman_numerals).to eq(std::vector<std::string>{"1=I", "2=II", "3=III", "4=IV", "5=V",
                                                                              "6=VI", "7=VII", "8=VIII", "9=IX", "10=X" });
        })
    )

    context("select",
        it("should only include strings who starts with a", [](){
            std::vector<std::string> only_starts_with_a_names = uva::string::select(person_names, [](const std::string& str) {
                return str.starts_with('A');
            });

            expect(only_starts_with_a_names).to eq(std::vector<std::string>({"Adams"}));
        })
    )

    context("map",
        it("should map integers to strings", [](){
            std::vector<int> firstTenNumbers = uva::faker::sequence::from_to(0, 10);

            auto vec = uva::string::map(firstTenNumbers, [](const int& i) {
                return std::to_string(i);
            });

            expect(vec).to eq(std::vector<std::string>({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }));
        })
    )
);