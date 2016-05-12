#ifndef GRID_H
#define GRID_H

#include <ngl/Vec3.h>
#include <vector>
#include <iostream>
#include "Cell.h"

class Grid
{
public:
  Grid();
  void Initialize(float _size, int _divisions);
  void Update(float _timestep);
  void Reset();
  void Draw();

private:

  int m_size;


  std::vector<Cell> m_cells;
};

#endif // GRID_H

