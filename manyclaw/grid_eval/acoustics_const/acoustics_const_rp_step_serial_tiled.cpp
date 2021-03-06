#include "acoustics_const_rp_step_serial_tiled.h"
#define TILE_SIZE 512

void acoustics_const_rp_step_serial_tiled( const real* q,  const real* aux,
                                     const int nx, const  int ny,
                                     real* amdq, real* apdq, real* wave,
                                     real* wave_speeds)
{
  int col, row, idx_left, idx_center, idx_up, idx_out_x, idx_out_y;
  const int num_ghost = acoustics_const_rp_grid_params.num_ghost;
  const int num_eqn = acoustics_const_rp_grid_params.num_eqn;
  const int num_waves = acoustics_const_rp_grid_params.num_waves;
  int row_tile, col_tile;

  for(row_tile=0; row_tile < ny/TILE_SIZE; ++row_tile){
    for(col_tile=0; col_tile < nx/TILE_SIZE; ++col_tile){
      for(row = row_tile * TILE_SIZE + num_ghost; row <= (row_tile+1)*TILE_SIZE + num_ghost; ++row) {
        for(col = col_tile * TILE_SIZE + num_ghost; col <= (col_tile+1)*TILE_SIZE + num_ghost; ++col) {
          idx_left = col + row*(nx + 2*num_ghost) - 1;
          idx_center = idx_left + 1;
          idx_out_x = (col - num_ghost) + (row - num_ghost) * (nx + 1);
          acoustics_const_rp(q + idx_left*num_eqn, q + idx_center*num_eqn,
                       aux, aux, &acoustics_const_rp_aux_global,
                       amdq + idx_out_x*num_eqn, apdq + idx_out_x*num_eqn,
                       wave + num_waves*num_eqn*idx_out_x, wave_speeds + num_waves*idx_out_x);
          idx_up = col + (row - 1)*(nx + 2*num_ghost);
          idx_out_y = (col - num_ghost) + (row - num_ghost) * (nx + 1) + (nx + 1)*(ny + 1);
          acoustics_const_rp(q + idx_up*num_eqn, q + idx_center*num_eqn,
                       aux, aux, &acoustics_const_rp_aux_global,
                       amdq + idx_out_y*num_eqn, apdq + idx_out_y*num_eqn,
                       wave + num_waves*num_eqn*idx_out_y, wave_speeds + num_waves*idx_out_y);
        }
      }
    }
  }
}

