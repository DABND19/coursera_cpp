#include "node.h"

using namespace std;

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
  switch (operation_) {
    case LogicalOperation::Or:
      return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    case LogicalOperation::And:
      return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    default:
      throw out_of_range("Problems with evaluating of logical operation node.\n");
  }
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
  switch (cmp_) {
    case Comparison::Less:
      return date < value_;
    case Comparison::LessOrEqual:
      return date <= value_;
    case Comparison::Greater:
      return date > value_;
    case Comparison::GreaterOrEqual:
      return date >= value_;
    case Comparison::Equal:
      return date == value_;
    case Comparison::NotEqual:
      return date != value_;
    default:
      throw out_of_range("Problems with evaluating of date comparison node.\n");
  }
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
  switch (cmp_) {
    case Comparison::Less:
      return event < value_;
    case Comparison::LessOrEqual:
      return event <= value_;
    case Comparison::Greater:
      return event > value_;
    case Comparison::GreaterOrEqual:
      return event >= value_;
    case Comparison::Equal:
      return event == value_;
    case Comparison::NotEqual:
      return event != value_;
    default:
      throw out_of_range("Problems with evaluating of event comparison node.\n");
  }
}