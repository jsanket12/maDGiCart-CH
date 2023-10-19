#pragma once

#include "program_options/program_options.hpp"

class HybridCHParameters {
 public:
  double initialMin() const { return initial_value_min_; }
  double initialMax() const { return initial_value_max_; }

 private:
  const double initial_value_min_ = -0.005;
  const double initial_value_max_ = 0.005;
};