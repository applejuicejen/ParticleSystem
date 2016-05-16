#include <math.h>
#include "Grid.h"

Grid::Grid()
{

}

void Grid::Initialize(float _size, int _divisions)
{
  Cell c;
  int count = 0;
  ngl::Real cell_size = _size/_divisions;
  for(int i = 0; i < _divisions; i ++)
  {
    for(int j = 0; j < _divisions; j++)
    {
      for(int k = 0; k < _divisions; k++)
      {
        c.Initialize(count);
        c.setPosition(ngl::Vec3((k*cell_size)+cell_size*0.5,
                                (j*cell_size)+cell_size*0.5,
                                (i*cell_size)+cell_size*0.5));
        c.setForce(ngl::Vec3(100,0,0));
        c.setSize(cell_size);
        m_cells.push_back(c);
        count++;
      }
    }
  }

  for(int i = 0; i < m_cells.size(); i++)
  {
    ngl::Vec3 pos = m_cells[i].getPosition();

    pos/=cell_size;

    int x = (int)pos.m_x;
    int y = (int)pos.m_y;
    int z = (int)pos.m_z;

    int cell_num = x + (y * _divisions) + (z * pow(_divisions, 2));
    int nbr1 = (x + 1) + (y * _divisions) + (z * pow(_divisions, 2));
    int nbr2 = (x - 1) + (y * _divisions) + (z * pow(_divisions, 2));
    int nbr3 = x + ((y+1) * _divisions) + (z * pow(_divisions, 2));
    int nbr4 = x + ((y-1) * _divisions) + (z * pow(_divisions, 2));
    int nbr5 = x + (y * _divisions) + ((z+1) * pow(_divisions, 2));
    int nbr6 = x + (y * _divisions) + ((z-1) * pow(_divisions, 2));

    if(x < 0 || y < 0 || z < 0 || x >= _divisions || y >= _divisions || z >= _divisions)
    {
      continue;
    }
    else
    {
      m_cells[i].m_neighbours.push_back(cell_num);

      if((x + 1) < _divisions)
      {
        m_cells[i].m_neighbours.push_back(nbr1);
      }
      if((x - 1) >= 0)
      {
        m_cells[i].m_neighbours.push_back(nbr2);
      }
      if((y + 1) < _divisions)
      {
        m_cells[i].m_neighbours.push_back(nbr3);
      }
      if((y - 1) >= 0)
      {
        m_cells[i].m_neighbours.push_back(nbr4);
      }
      if((z + 1) < _divisions)
      {
        m_cells[i].m_neighbours.push_back(nbr5);
      }
      if((z - 1) >= 0)
      {
        m_cells[i].m_neighbours.push_back(nbr6);
      }
    }
  }
//  for(int i = 0; i < m_cells[0].m_neighbours.size(); i++)
//  {
//    std::cout<<"neighbour "<< i <<": "<< m_cells[0].m_neighbours[i]<<std::endl;
//  }

}

void Grid::Draw()
{
  //std::cout<<"num of cells"<<m_cells.size()<<std::endl;
  for(int i = 0; i < m_cells.size(); i++)
  {
    m_cells[i].Draw();
  }
}
