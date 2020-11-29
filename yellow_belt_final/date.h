#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>

class Date {
public:
  Date() {}
  Date(int new_year, int new_month, int new_day);
  explicit Date(const std::string& date);
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }
private:
  int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);

std::istream& operator>>(std::istream& is, Date& d);

std::ostream& operator<<(std::ostream& os, const Date& d);

Date ParseDate(std::istream& is);