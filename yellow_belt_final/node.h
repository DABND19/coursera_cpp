#pragma once

#include <memory>
#include "date.h"

class Node {
public:
  virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

enum struct Comparison {
  Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual
};

enum struct LogicalOperation {
  Or, And
};

class LogicalOperationNode : public Node {
  LogicalOperation operation_;
  std::shared_ptr<const Node> left_, right_;
public:
  LogicalOperationNode(LogicalOperation operation,
                       const std::shared_ptr<Node>& left,
                       const std::shared_ptr<Node>& right) :
  operation_(operation), left_(left), right_(right)
  {}
  bool Evaluate(const Date& date, const std::string& event) const override;
};

class EmptyNode : public Node {
public:
  bool Evaluate(const Date& date, const std::string& event) const override {
    return true;
  }
};

class DateComparisonNode : public Node {
  Date value_;
  Comparison cmp_;
public:
  DateComparisonNode(Comparison cmp, const Date& value) :
  value_(value), cmp_(cmp)
  {}
  bool Evaluate(const Date& date, const std::string& event) const override;
};

class EventComparisonNode : public Node {
  std::string value_;
  Comparison cmp_;
public:
  EventComparisonNode(Comparison cmp, const std::string& value) :
  value_(value), cmp_(cmp)
  {}
  bool Evaluate(const Date& date, const std::string& event) const override;
};