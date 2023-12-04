#pragma once

#include "hybrid_ch_base.hpp"
#include "hybrid_ch_parameters.hpp"
#include "data_structures/managed_array_2d.hpp"
#include "data_structures/scalar_solution_state.hpp"
#include "governing_equations/time_integrable_rhs.hpp"
#include "spatial_discretization/discretization_2d_cart.hpp"
#include <torch/script.h>


class HybridCH2DFD : public HybridCHBase {
 public:
  HybridCH2DFD(Discretization2DCart& geom, const HybridCHParameters& params);

  void evalRHSImpl(const SolutionState& flovars, double time, SolutionState& rhs) override;

  void evalJacobian(const SolutionState& flovars, double time, CSRMatrix& J) override;

  std::unique_ptr<SolutionState> createSolutionState() const override
  {
    return std::make_unique<ScalarSolutionState2D>(ManagedArrayOwner{}, "state", geom_.ni(), geom_.ni(), geom_.nhalo());
  }

  int_t dofsPerEquation() const override { return geom_.nInteriorPoints(); }

  const IndexArray& interiorIndices() const override { return geom_.interiorIndices(); }

  std::unique_ptr<CSRMatrix> createSparseMatrix() const override;
  std::vector<int> nNonZerosPerRow() const override;

 private:
  Discretization2DCart& geom_;

  std::unique_ptr<ManagedArray2D<real_wp>> rhs_;

  torch::jit::script::Module nn_; // Neural network for computing the data-driven component of PDE
};
