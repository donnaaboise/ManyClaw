#ifndef ADVECTION_RP_H
#define ADVECTION_RP_H

#include "../../many_claw.h"

struct advection_rp_aux_global_t
{
  real u;
};

static const advection_rp_aux_global_t advection_rp_aux_global = {1.0};
static const rp_grid_params advection_rp_grid_params = {2, 1, 0, 1};

// Constanst coefficient Riemann problem
inline
void advection_rp(const real* q_left, const real* q_right,
                  const real* aux_left, const real* aux_right,
                  const advection_rp_aux_global_t* aux_global,
                  real* amdq, real* apdq, real* wave, real* s)
{
    // Wave and speed
    wave[0] = q_right[0] - q_left[0];
    s[0] = aux_global->u;

    // This could also be implemented as an if statement or statically
    // based on the sign of s[0] (a.k.a. u)
    amdq[0] = std::min(0.0,s[0] * wave[0]);
    apdq[0] = std::max(0.0,s[0] * wave[0]);

}
#endif // ADVECTION_RP_H