#include "date.h"

unsigned short Date::days_in_current_month() const {
    unsigned short days_in_month[] = { 31, (is_leap_year(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return days_in_month[month - 1];
}

bool Date::is_leap_year(unsigned short year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::is_valid_date(unsigned short day, unsigned short month, unsigned short year) const {
    if (month < 1 || month > 12) return false;

    unsigned short days_in_month[] = { 31, (is_leap_year(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return day >= 1 && day <= days_in_month[month - 1];
}

Date::Date(unsigned short d, unsigned short m, unsigned short y) {
    day = d;
    month = m;
    year = y;
    is_initialized = is_valid_date(day, month, year);
}

Date::Date(const std::string& date_str) {
    std::istringstream ss(date_str);
    char dot;
    ss >> day >> dot >> month >> dot >> year;
    is_initialized = is_valid_date(day, month, year);
}

Date::Date(std::chrono::year year, std::chrono::month month, std::chrono::day day) {
    this->year = static_cast<unsigned short>(int(year));
    this->month = static_cast<unsigned short>(unsigned(month));
    this->day = static_cast<unsigned short>(unsigned(day));
    is_initialized = is_valid_date(this->day, this->month, this->year);
}

std::istream& operator>>(std::istream& in, Date& date) {
    char dot1, dot2;
    in >> date.day >> dot1 >> date.month >> dot2 >> date.year;
    if (date.is_valid_date(date.day, date.month, date.year)) {
        date.is_initialized = true;
    }
    else {
        date.is_initialized = false;
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
    if (!date.is_initialized) {
        out << "Дата не установлена.";
        return out;
    }
    out << (date.day < 10 ? "0" : "") << date.day << "."
        << (date.month < 10 ? "0" : "") << date.month << "."
        << date.year;
    return out;
}

Date Date::operator+(int days) const {
    Date result = *this;
    result.add_days(days);
    return result;
}

Date Date::operator-(int days) const {
    Date result = *this;
    result.subtract_days(days);
    return result;
}

int Date::operator-(Date& other) const
{
    return (days_between(other));
}

int Date::days_between(const Date& other) const {
    if (!is_initialized || !other.is_initialized) {
        std::cerr << "Ошибка: одна из дат не инициализирована.\n";
        return 0;
    }
    Date start = *this;
    Date end = other;
    if (start > end) std::swap(start, end);
    int total_days = 0;

    while (start.get_day() != end.get_day() || start.get_month() != end.get_month() || start.get_year() != end.get_year()) {
        start.add_days(1);
        total_days++; 
    }

    return total_days;
}

void Date::add_days(int days) {
    if (!is_initialized) {
        std::cerr << "Ошибка: дата не установлена.\n";
        return;
    }

    while (days > 0) {
        unsigned short days_in_month = days_in_current_month();
        if (day + days <= days_in_month) {
            day += days;
            days = 0;
        }
        else {
            days -= (days_in_month - day + 1); 
            day = 1; 
            if (++month > 12) { 
                month = 1;
                ++year;
            }
        }
    }
}

/*bool Date::operator<(const Date& other) const {
    return (this->operator<=>(other)) == std::strong_ordering::less;
}

bool Date::operator>(const Date& other) const {
    return (this->operator<=>(other)) == std::strong_ordering::greater;
}*/

bool Date::operator==(const Date& other) const {
    return (this->operator<=>(other)) == std::strong_ordering::equal;
}

bool Date::operator!=(const Date& other) const {
    return !(this->operator==(other));
}


std::strong_ordering Date::operator<=>(const Date& other) const {
    if (year != other.year) return year <=> other.year;
    if (month != other.month) return month <=> other.month;
    return day <=> other.day;
}

void Date::subtract_days(int days) {
    if (!is_initialized) {
        std::cerr << "Ошибка: дата не установлена.\n";
        return;
    }

    while (days > 0) {
        if (day > days) {
            day -= days;
            days = 0;
        }
        else {
            days -= day;
            if (--month < 1) {
                month = 12;
                --year;
            }
            day = days_in_current_month();
        }
    }
}

void Date::save_to_file(const std::string& filename) const {
    std::ofstream outfile(filename, std::ios::app);
    if (outfile.is_open()) {
        outfile << *this << '\n';
        outfile.close();
    }
    else {
        std::cerr << "Ошибка: не удалось открыть файл для записи.\n";
    }
}

std::string Date::read_file_to_string(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл для записи.");
    }

    std::ostringstream content;
    content << file.rdbuf();
    file.close();

    return content.str();
}