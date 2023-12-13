#pragma once

#include "program_options/program_options.hpp"

class HybridCHParameters {
 public:
  double m() const { return m_; }
  double initialMin() const { return initial_value_min_; }
  double initialMax() const { return initial_value_max_; }
  std::string filename_nn() const { return filename_nn_; }

 private:
  const double m_                 = Options::get().ch_m(); // used for generating random ICs about the m value
  const double initial_value_min_ = -0.005;
  const double initial_value_max_ = 0.005;
  const std::string filename_nn_  = Options::get().hybrid_nn_filename();
};