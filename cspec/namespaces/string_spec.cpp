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

std::vector<std::pair<std::string, std::string>> words_plurals =
{
    { "car", 	  "cars" },
    { "house", 	  "houses" },
    { "book", 	  "books" },
    { "bird", 	  "birds" },
    { "pencil",   "pencils" },
    { "kiss", 	  "kisses" },
    { "wish", 	  "wishes" },
    { "match", 	  "matches" },
    { "fox", 	  "foxes" },
    { "quiz", 	  "quizzes" },
    { "boy", 	  "boys" },
    { "holiday",  "holidays" },
    { "key", 	  "keys" },
    { "guy", 	  "guys" },
    { "party", 	  "parties" },
    { "lady", 	  "ladies" },
    { "story", 	  "stories" },
    { "nanny", 	  "nannies" },
    { "city", 	  "cities" },
    { "life", 	  "lives" },
    { "leaf", 	  "leaves" },
    { "thief", 	  "thieves" },
    { "wife", 	  "wives" },
    { "tomato",   "tomatoes" },
    { "potato",   "potatoes" },
    { "echo", 	  "echoes" },
    { "hero", 	  "heroes" },
    { "man", 	  "men" },
    { "woman", 	  "women" },
    { "child", 	  "children" },
    { "foot", 	  "feet" },
    { "tooth", 	  "teeth" },
    { "goose", 	  "geese" },
    { "mouse", 	  "mice" },
    { "fish", 	  "fish" },
    { "sheep", 	  "sheep" },
    { "deer", 	  "deer" },
    { "moose", 	  "moose" },
    { "aircraft", "aircraft" },
    { "roof",     "roofs" },
    { "cliff",    "cliffs" },
    { "chief",    "chiefs" },
    { "belief",   "beliefs" },
    { "chef",     "chefs" },
    { "piano",    "pianos" },
    { "halo",     "halos" },
    { "photo",    "photos" },
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

cspec_describe("uva::string",

    describe("join",
        it("should join roman with their numerals",[](){
            auto joined_roman_numerals = uva::string::join(romanNumeralsMap, [](const auto& number_roman) {
                return std::format("{}={}", number_roman.first, number_roman.second);
            });

            expect(joined_roman_numerals).to eq(std::vector<std::string>{"1=I", "2=II", "3=III", "4=IV", "5=V",
                                                                              "6=VI", "7=VII", "8=VIII", "9=IX", "10=X" });
        })

        it("should join integers separated by comma",[](){
            std::vector<int> firstTenNumbers = uva::faker::sequence::from_to(0, 10);

            auto joined_numbers = uva::string::join(firstTenNumbers, ',');

            expect(joined_numbers).to eq(std::string("0,1,2,3,4,5,6,7,8,9"));
        })
    )

    describe("select",
        it("should only include strings who starts with a", [](){
            std::vector<std::string> only_starts_with_a_names = uva::string::select(person_names, [](const std::string& str) {
                return str.starts_with('A');
            });

            expect(only_starts_with_a_names).to eq(std::vector<std::string>({"Adams"}));
        })
    )

    describe("map",
        it("should map integers to strings", [](){
            std::vector<int> firstTenNumbers = uva::faker::sequence::from_to(0, 10);

            auto vec = uva::string::map(firstTenNumbers, [](const int& i) {
                return std::to_string(i);
            });

            expect(vec).to eq(std::vector<std::string>({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }));
        })
    )

    describe("tokenize",
        it("should tokenize string by spaces", [](){
            std::string_view sentence = R"~~~(Some text. It should be splited, and match the expected result.
                                     All spaces  , tabs, new lines should be ignored.)~~~";

            std::vector<const char*> results({ "Some", "text.", "It", "should", "be", "splited,", "and",
                                               "match", "the", "expected", "result.", "All", "spaces",
                                               ",", "tabs,", "new", "lines", "should", "be", "ignored." });

            auto tokenized = uva::string::tokenize(sentence);

            expect(tokenized).to eq(results);
        })
    )

    describe("capitalize",
        context("with 1 word string",
            it("should capitalize correctly string", [](){
                std::string str = uva::string::capitalize("foo");

                expect(str).to eq("Foo");
            })
        )

        context("with 2 word string",
            it("should capitalize correctly string", [](){
                std::string str = uva::string::capitalize("foo bar");

                expect(str).to eq("Foo Bar");
            })

            it("should capitalize correctly string with one workd already capitalized", [](){
                std::string str = uva::string::capitalize("Some text");

                expect(str).to eq("Some Text");
            })
        )
    )

    describe("pluralize",
        it("should pluralize correctly", [](){
            for(const std::pair<std::string, std::string>& word_plural : words_plurals) {
                expect(uva::string::pluralize(word_plural.first)).to eq(word_plural.second);
            }
        })
    )
);