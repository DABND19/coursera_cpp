#include "date.h"

using namespace std;

Date::Date(int new_year, int new_month, int new_day) {
  year = new_year;
  if (new_month < 1 || new_month > 12) {
    throw out_of_range("Month value is invalid: "
                       + to_string(new_month));
  }
  month = new_month;
  if (new_day < 1 || new_day > 31) {
    throw out_of_range("Day value is invalid: "
                       + to_string(new_day));
  }
  day = new_day;
}

Date::Date(const string& date) {
  int new_year, new_month, new_day;
  bool ok = true;
  istringstream date_stream(date);

  ok = ok && (date_stream >> new_year);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  ok = ok && (date_stream >> new_month);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  ok = ok && (date_stream >> new_day);
  ok = ok && date_stream.eof();

  if (!ok) {
    throw out_of_range("Wrong date format: " + date);
  }
  *this = Date(new_year, new_month, new_day);
}

bool operator<(const Date& lhs, const Date& rhs) {
  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>(const Date& lhs, const Date& rhs) {
  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator==(const Date& lhs, const Date& rhs) {
  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date& lhs, const Date& rhs) {
  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>=(const Date& lhs, const Date& rhs) {
  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >=
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs) {
  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

istream& operator>>(istream& is, Date& d) {
  string date;
  is >> date;
  d = Date(date);
  return is;
}

ostream& operator<<(ostream& os, const Date& d) {
  os << setfill('0');
  os << setw(4) << d.GetYear() << '-';
  os << setw(2) << d.GetMonth() << '-';
  os << setw(2) << d.GetDay();
  return os;
}

Date ParseDate(istream& is) {
  Date result;
  is >> result;
  return result;
}
