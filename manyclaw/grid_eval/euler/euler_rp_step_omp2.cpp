#include "euler_rp_step_omp2.h"

void euler_rp_step_omp2( const real* q,  const real* aux,
                            const int nx, const  int ny,
                            real* amdq, real* apdq, real* wave,
                            real* wave_speeds)
{
  int col, row, idx_left, idx_center, idx_up, idx_out_x, idx_out_y;
  const int num_ghost = euler_rp_grid_params.num_ghost;
  const int num_eqn = euler_rp_grid_params.num_eqn;
  const int num_waves = euler_rp_grid_params.num_waves;
  //  printf("Before loop\n");

#pragma omp parallel shared(q, aux, amdq, apdq, wave, wave_speeds) private(col, row, idx_left, idx_center, idx_up, idx_out_x, idx_out_y)
  {
    #pragma omp for schedule(runtime) nowait
  for(int idx= 0; idx < (nx+1)*(ny+1); ++idx){
    row = idx / (ny+1) + num_ghost;
    col = idx % (ny+1) + num_ghost;
    idx_left = col + row*(nx + 2*num_ghost) - 1;
    idx_up = col + (row - 1)*(nx + 2*num_ghost);
    idx_center = idx_left + 1;
    idx_out_x = (col - num_ghost) + (row - num_ghost) * (nx + 1);
    idx_out_y = idx_out_x + ((nx + 1)*(ny + 1));

    euler_rp(q + idx_left*num_eqn, q + idx_center*num_eqn,
             aux, aux, &euler_rp_aux_global,
             amdq + idx_out_x*num_eqn, apdq + idx_out_x*num_eqn,
             wave + num_waves*num_eqn*idx_out_x, wave_speeds + num_waves*idx_out_x);
    euler_rp(q + idx_up*num_eqn, q + idx_center*num_eqn,
             aux, aux, &euler_rp_aux_global,
             amdq + idx_out_y*num_eqn, apdq + idx_out_y*num_eqn,
             wave + num_waves*num_eqn*idx_out_y, wave_speeds + num_waves*idx_out_y);
  }
  }
}
