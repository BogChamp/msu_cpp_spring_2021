#ifndef MSU_CPP_SPRING_2021_02_PARSER_H_
#define MSU_CPP_SPRING_2021_02_PARSER_H_

#include <iostream>
#include <functional>

using digit_callback = std::function<void(uint64_t)>;
using str_callback = std::function<void(std::string)>;
using callback = std::function<void()>;

class Parser {
    digit_callback dig_call = nullptr;  // колбэк при нахождении числа
    str_callback str_call = nullptr;  // колбэк при нахождении строки
    callback start = nullptr;  // колбэк перед началом парсинга
    callback end = nullptr;  // колбэк после парсинга
 public:
        void parse(const std::string& str);
        // установка колбэка для чисел
        void set_digit_callback(digit_callback func);
        // установка колбэка для строк
        void set_str_callback(str_callback func);
        // установка колбэка перед парсингом
        void set_start_callback(callback func);
        // установка колбэка после парсинга
        void set_end_callback(callback func);
        // проверка, является ли токен числом
        bool is_number(const std::string& s);
};

#endif  // MSU_CPP_SPRING_2021_02_PARSER_H_
