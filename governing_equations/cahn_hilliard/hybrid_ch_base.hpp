#pragma once

#include "hybrid_ch_parameters.hpp"
#include "governing_equations/time_integrable_rhs.hpp"


class HybridCHBase : public TimeIntegrableRHS {
 public:
  HybridCHBase(const HybridCHParameters& params)
      : params_(params)
  {
  }

  int_t nEquations() const override { return 1; }

  std::vector<std::string> equationNames() const override { return {{"c"}}; }

 protected:

  const HybridCHParameters& params() const { return params_; }

 private:
  const HybridCHParameters params_;
};
