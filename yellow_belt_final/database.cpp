#include "database.h"

void Database::Add(const Date &date, const string &event) {
  auto it = data_checker[date].insert(event);
  if (it.second) {
    ordered_data[date].push_back(event);
  }
}

void Database::Print(ostream &os) const {
  for (const auto& [date, events] : ordered_data) {
    for (const auto& event : events) {
      os << date << ' ' << event << endl;
    }
  }
}

Database::Event Database::Last(const Date &date) const {
  auto upper = ordered_data.upper_bound(date);

  if (upper == ordered_data.begin()) {
    throw invalid_argument("Can't find last event.\n");
  } else {
    auto [date_, events_] = *prev(upper);
    return {date_, events_.back()};
  }
}

ostream& operator<<(ostream& os, const Database::Event& event) {
  os << event.first << ' ' << event.second;
  return os;
}

