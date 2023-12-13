#include "hybrid_ch_2d.hpp"

#include <random>


HybridCH2DFD::HybridCH2DFD(Discretization2DCart& geom, const HybridCHParameters& params)
    : HybridCHBase(params), geom_(geom)
{
  rhs_ = geom_.createRealArray();
  nn_  = torch::jit::load( params_.filename_nn );
}


void
HybridCH2DFD::evalRHSImpl(const SolutionState& flovars, double time, SolutionState& rhs)
{
  madg_profile();
  const ScalarSolutionState2D& state = dynamic_cast<const ScalarSolutionState2D&>(flovars);

  geom_.applyPeriodicBoundaryConditions(const_cast<ManagedArray2DNonOwning<real_wp>&>(state.c()));

  geom_.nn_2d_stencil(state.c(), *rhs_, nn_);

  {
    ScalarSolutionState2D& dstate_dt = dynamic_cast<ScalarSolutionState2D&>(rhs);
    {
      auto r = write_access(dstate_dt.c().asArray());
      maDGForAll(i, 0, r.size(), { r[i] = real_wp(0); });
    }

    auto rhs     = write_access(dstate_dt.c().asArray());
    auto idx     = read_access(geom_.interiorIndices());
    auto f_nn    = read_access(rhs_->asArray());

    const real_wp eps2 = this->eps2();


    maDGForAll(ii, 0, idx.size(), {
      const int i = idx[ii];
      rhs[i]      = f_nn[i];
    });
  }

}

std::unique_ptr<CSRMatrix> HybridCH2DFD::createSparseMatrix() const
{
  Logger::get().FatalMessage("HybridCH2DFD::createSparseMatrix() not implemented");
  return nullptr;
}

void HybridCH2DFD::evalJacobian(const SolutionState& flovars, double time, CSRMatrix& J)
{
  Logger::get().FatalMessage("HybridCH2DFD::evalJacobian() not implemented");
}


std::vector<int> HybridCH2DFD::nNonZerosPerRow() const
{
  Logger::get().FatalMessage("HybridCH2DFD::nNonZerosPerRow() not implemented");
  return {};
}