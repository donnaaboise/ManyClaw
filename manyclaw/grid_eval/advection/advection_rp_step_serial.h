#ifndef __ADVECTION_RP_STEP_SERIAL_H
#define __ADVECTION_RP_STEP_SERIAL_H

#include "../../riemann/advection_rp.h"

void advection_rp_step_serial( const real* q,
                               const real* aux,
                               const int nx,
                               const int ny,
                               real* amdq,
                               real* apdq,
                               real* wave,
                               real* wave_speeds);
#endif // ADVECTION_RP_STEP_SERIAL_H

