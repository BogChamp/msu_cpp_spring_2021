#pragma once
#include <iostream>
#include <sstream>
#include <vector>

class brackets : public std::exception {};
class no_number : public std::exception {};
class wrong_number : public std::exception {};
class no_arg : public std::exception {};

template <class T>
std::string convert_to_string(T&& arg) {
    std::ostringstream stream;
    stream << arg;
    return stream.str();
}

template <class... Args>
std::string format(const std::string& str, Args&&... arg) {
    std::string new_str = "";
    std::vector<std::string> args = {convert_to_string(arg) ...};
    bool bracket_open = false;
    std::string num = "";

    std::string::const_iterator it = str.begin();
    for(; it < str.end(); ++it) {
        if (bracket_open) {

            if (*it == '}') {

                if (num.empty())
                    throw no_number();

                size_t tmp = stoull(num);
                if (tmp >= args.size())
                    throw no_arg();

                new_str += args[tmp];
                num.clear();
                bracket_open = false;

            } else {

                if (!isdigit(*it))
                    throw wrong_number();
                num += *it;

            }
        } else {

            if (*it == '{')
                bracket_open = true;
            else if (*it == '}')
                throw brackets();
            else
                new_str += *it;

        }
    }

    if (bracket_open)
        throw brackets();
    return new_str;
}
