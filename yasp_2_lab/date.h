#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

class Date {
private:
    unsigned short day;
    unsigned short month;
    unsigned short year;

    // Проверка, является ли год високосным
    bool is_leap_year(unsigned short year) const;
    bool is_valid_date(unsigned short day, unsigned short month, unsigned short year) const;
    unsigned short days_in_current_month() const;


public:
    bool is_initialized;
    Date(unsigned short d = 1, unsigned short m = 1, unsigned short y = 2000);
    Date(const std::string& date_str);
    Date(std::chrono::year year, std::chrono::month month, std::chrono::day day);

    friend std::istream& operator>>(std::istream& in, Date& date);
    friend std::ostream& operator<<(std::ostream& out, const Date& date);

    Date operator+(int days) const;
    Date operator-(int days) const;

    auto operator<=>(const Date& other) const = default;

    unsigned short get_day() const noexcept { return day; }
    unsigned short get_month() const noexcept { return month; }
    unsigned short get_year() const noexcept { return year; }

    void set_day(unsigned short d) { if (is_valid_date(d, month, year)) day = d; }
    void set_month(unsigned short m) { if (is_valid_date(day, m, year)) month = m; }
    void set_year(unsigned short y) { if (is_valid_date(day, month, y)) year = y; }

    // Метод для проверки инициализации даты
    bool is_initialized_check() const noexcept { return is_initialized; }

    // Метод для вычисления количества дней между датами
    int days_between(const Date& other) const;

    void add_days(int days);
    void subtract_days(int days);

    bool is_leap_year() const { return is_leap_year(year); }

    void save_to_file(const std::string& filename) const;

    std::string read_file_to_string(const std::string& filename);
};