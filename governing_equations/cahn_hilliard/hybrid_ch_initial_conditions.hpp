#pragma once

#include "governing_equations/initial_conditions.hpp"

class HybridCHParameters;

class HybridCHInitialConditions : public InitialConditions
{
 public:
  HybridCHInitialConditions(HybridCHParameters& params);
  virtual ~HybridCHInitialConditions() = default;

  void set(const TimeIntegrableRHS&, SolutionState& state) const override;

 private:
  const double m_;
  const double min_;
  const double max_;
};
