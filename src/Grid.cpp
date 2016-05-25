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
  //ngl::Real divs = _divisions*0.5;
  for(int i = 0; i < _divisions; i ++)
  {
    for(int j = 0; j < _divisions; j++)
    {
      for(int k = 0; k < _divisions; k++)
      {
        c.Initialize(count);
        c.setPosition(ngl::Vec3(((k*cell_size)+cell_size*0.5),
                                ((j*cell_size)+cell_size*0.5),
                                ((i*cell_size)+cell_size*0.5)));
        c.setCellForces(_size);
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

    if(x < 0 || y < 0 || z < 0 || x >= _divisions || y >= _divisions || z >= _divisions)
    {
      continue;
    }


    for(int n = -1; n < 2; n++)
    {
      for(int j = -1; j < 2; j++)
      {
        for(int k = -1; k < 2; k++)
        {
          int nbr = (n+x) + ((j+y) * _divisions) + ((k+z) * pow(_divisions,2));


          if(((n+x) < _divisions && (n+x) >= 0) &&
             ((j+y) < _divisions && (j+y) >= 0) &&
             ((k+z) < _divisions && (k+z) >= 0))
          {
            m_cells[i].m_neighbours.push_back(nbr);
          }
          else
          m_cells[i].m_neighbours.push_back(-1);
        }
      }
    }

    //std::cout<<"number of neighbours: "<< m_cells[0].m_neighbours.size() << std::endl;

    for(int j = 0; j < m_cells[i].m_neighbours.size(); j++)
    {
      if(m_cells[i].m_neighbours[j] == -1)
      {
        m_cells[i].m_gradients.push_back(ngl::Vec3(0,0,0));
      }
      else
      {
        m_cells[i].m_gradients.push_back(m_cells[m_cells[i].m_neighbours[j]].getGradient());
      }
    }
  }

  //std::cout<<"number of neighbours: "<< m_cells[0].m_neighbours.size()<<std::endl;
//  std::cout<<"number of gradients: "<< m_cells[0].m_gradients.size()<<std::endl;


//  for(int i = 0; i < m_cells[0].m_neighbours.size(); i++)
//  {
//    std::cout<<"neighbour: " << m_cells[0].m_neighbours[i]<<
//               " gradient: "<< m_cells[0].m_gradients[i].m_x<<
//               ", " << m_cells[0].m_gradients[i].m_y<<
//               ", " << m_cells[0].m_gradients[i].m_z<< std::endl;
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
