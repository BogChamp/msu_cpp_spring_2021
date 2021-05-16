#include "parser.h"

void Parser::parse(const std::string& str) {
    size_t i = 0;
    char letter = str[i];
    std::string word = "";

    if (start != nullptr)
        start();

    while (letter != '\0') {
        letter = str[i];
        switch (letter) {
            case ' ':
            case '\t':
            case '\n':
            case '\0':
                if (word.length() < 1)
                    break;
                if (is_number(word)) {
                    if (dig_call != nullptr)
                        dig_call(stoull(word));
                } else { if (str_call != nullptr) str_call(word);}

                word = "";
                break;
            default:
                word += letter;
                break;
        }
        ++i;
    }

    if (end != nullptr)
        end();
}

void Parser::set_digit_callback(digit_callback func) {
    dig_call = func;
}

void Parser::set_str_callback(str_callback func) {
    str_call = func;
}

void Parser::set_start_callback(callback func) {
    start = func;
}

void Parser::set_end_callback(callback func) {
    end = func;
}

bool Parser::is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    if (!s.empty() && it == s.end()) {
        return (("18446744073709551615" >= s) || (s.length() < 20));
    } else {
        return false;
    }
}
