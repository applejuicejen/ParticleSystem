#include "Grid.h"

Grid::Grid()
{

}

void Grid::Initialize(float _size, int _divisions)
{
  Cell c;
  ngl::Real cell_size = _size/_divisions;
  for(int i = 0; i < _divisions; i ++)
  {
    for(int j = 0; j < _divisions; j++)
    {
      for(int k = 0; k < _divisions; k++)
      {
        c.setPosition(ngl::Vec3((k*cell_size)+cell_size*0.5,
                                (j*cell_size)+cell_size*0.5,
                                (i*cell_size)+cell_size*0.5));
        c.setForce(ngl::Vec3(100,0,0));
        c.setSize(cell_size);
        m_cells.push_back(c);
      }
    }
  }
}

void Grid::Draw()
{
  //std::cout<<"num of cells"<<m_cells.size()<<std::endl;
  for(int i = 0; i < m_cells.size(); i++)
  {
    m_cells[i].Draw();
  }
}
