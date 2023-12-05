#include "hybrid_ch_2d.hpp"

#include <random>


HybridCH2DFD::HybridCH2DFD(Discretization2DCart& geom, const HybridCHParameters& params)
    : HybridCHBase(params), geom_(geom)
{
  rhs_ = geom_.createRealArray();
  nn_  = torch::jit::load( params_.filename_nn );
}


