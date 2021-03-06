#ifndef ACOUSTICS_VAR_RP_STEP_SERIAL_H
#define ACOUSTICS_VAR_RP_STEP_SERIAL_H

#include "../../riemann/acoustics_var_rp.h"

void acoustics_var_rp_step_serial( const real* q,
                               const real* aux,
                               const int nx,
                               const int ny,
                               real* amdq,
                               real* apdq,
                               real* wave,
                               real* wave_speeds);
#endif // ACOUSTICS_VAR_RP_STEP_SERIAL_H

