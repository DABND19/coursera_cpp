#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include "date.h"

using namespace std;

class Database {
public:
  using Event = pair<Date, string>;
  void Add(const Date& date, const string& event);
  void Print(ostream& os) const;

  template<typename Function>
  int RemoveIf(Function predicate) {
    int removed_count = 0;

    auto current = ordered_data.begin();
    while (current != ordered_data.end()) {
      auto sep = stable_partition(current->second.begin(),
                                  current->second.end(),
                                  [predicate, current](const string& event) {
        return !predicate(current->first, event);
      });

      int current_removed = current->second.end() - sep;
      removed_count += current_removed;

      if (sep == current->second.begin()) {
        data_checker.erase(current->first);
        current = ordered_data.erase(current);
      } else {
        if (sep != current->second.end()) {
          while (current_removed != 0) {
            data_checker[current->first].erase(current->second.back());
            current->second.pop_back();
            current_removed--;
          }
        }
        current++;
      }
    }

    return removed_count;
  }

  template<typename Function>
  vector<Event> FindIf(Function predicate) const {
    vector<Event> result;

    for (const auto& [date, events] : ordered_data) {
      for (const auto& event : events) {
        if (predicate(date, event)) {
          result.push_back({date, event});
        }
      }
    }

    return result;
  }

  Event Last(const Date& date) const;
private:
  map<Date, vector<string>> ordered_data;
  map<Date, set<string>> data_checker;
};

ostream& operator<<(ostream& os, const Database::Event& event);