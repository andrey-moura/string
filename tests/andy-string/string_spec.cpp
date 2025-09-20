#include "andy/string.hpp"
#include "andy/tests.hpp"

describe of("andy::string", []() {
    describe("::to_lower", []() {
        it("converts uppercase letters to lowercase", []() {
            expect(andy::string::to_lower("ABCDEF")).to<eq>("abcdef");
        });
        it("leaves lowercase letters unchanged", []() {
            expect(andy::string::to_lower("abcdef")).to<eq>("abcdef");
        });
        it("leaves digits unchanged", []() {
            expect(andy::string::to_lower("123456")).to<eq>("123456");
        });
        it("leaves special characters unchanged", []() {
            expect(andy::string::to_lower("!@#$%^&*()")).to<eq>("!@#$%^&*()");
        });
        it("handles empty strings", []() {
            expect(andy::string::to_lower("")).to<eq>("");
        });
    });
    describe("::to_snake_case", []() {
        it("converts camelCase to snake_case", []() {
            expect(andy::string::to_snake_case("camelCaseString")).to<eq>("camel_case_string");
        });
        it("converts PascalCase to snake_case", []() {
            expect(andy::string::to_snake_case("PascalCaseString")).to<eq>("pascal_case_string");
        });
        it("converts kebab-case to snake_case", []() {
            expect(andy::string::to_snake_case("kebab-case-string")).to<eq>("kebab_case_string");
        });
        it("handles strings with no case changes", []() {
            expect(andy::string::to_snake_case("simple_string")).to<eq>("simple_string");
        });
        it("handles empty strings", []() {
            expect(andy::string::to_snake_case("")).to<eq>("");
        });
    });
});
