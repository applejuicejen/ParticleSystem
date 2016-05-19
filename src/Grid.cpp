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

    if(x < 0 || y < 0 || z < 0 || x >= _divisions || y >= _divisions || z >= _divisions)
    {
      continue;
    }

   /* //middle row
    int nbr0 = x + (y * _divisions) + (z * pow(_divisions, 2)); //centre centre centre
    int nbr1 = (x + 1) + (y * _divisions) + ((z+1) * pow(_divisions, 2)); //right centre forward
    int nbr2 = (x + 1) + (y * _divisions) + ((z-1) * pow(_divisions, 2)); //right centre back
    int nbr3 = (x - 1) + (y * _divisions) + ((z+1) * pow(_divisions, 2)); //left centre forward
    int nbr4 = (x - 1) + (y * _divisions) + ((z-1) * pow(_divisions, 2)); //left centre back
    int nbr5 = (x + 1) + (y * _divisions) + (z * pow(_divisions, 2)); //right centre centre
    int nbr6 = (x - 1) + (y * _divisions) + (z * pow(_divisions, 2)); //left centre centre
    int nbr7 = x + (y * _divisions) + ((z + 1) * pow(_divisions, 2)); //centre centre forward
    int nbr8 = x + (y * _divisions) + ((z - 1) * pow(_divisions, 2)); //centre centre back

    //top row
    int nbr9 = (x + 1) + ((y+1) * _divisions) + ((z+1) * pow(_divisions, 2)); //right top forward
    int nbr10 = (x + 1) + ((y+1) * _divisions) + ((z-1) * pow(_divisions, 2)); //right top back
    int nbr11 = (x - 1) + ((y+1) * _divisions) + ((z+1) * pow(_divisions, 2)); //left top forward
    int nbr12 = (x - 1) + ((y+1) * _divisions) + ((z-1) * pow(_divisions, 2)); //left top back
    int nbr13 = (x + 1) + ((y+1) * _divisions) + (z * pow(_divisions, 2)); //right top centre
    int nbr14 = (x - 1) + ((y+1) * _divisions) + (z * pow(_divisions, 2)); //left top centre
    int nbr15 = x + ((y+1) * _divisions) + ((z + 1) * pow(_divisions, 2)); //centre top forward
    int nbr16 = x + ((y+1) * _divisions) + ((z - 1) * pow(_divisions, 2)); //centre top back

    //bottom row
    int nbr17 = (x + 1) + ((y-1) * _divisions) + ((z+1) * pow(_divisions, 2)); //right bottom forward
    int nbr18 = (x + 1) + ((y-1) * _divisions) + ((z-1) * pow(_divisions, 2)); //right bottom back
    int nbr19 = (x - 1) + ((y-1) * _divisions) + ((z+1) * pow(_divisions, 2)); //left bottom forward
    int nbr20 = (x - 1) + ((y-1) * _divisions) + ((z-1) * pow(_divisions, 2)); //left bottom back
    int nbr21 = (x + 1) + ((y-1) * _divisions) + (z * pow(_divisions, 2)); //right bottom centre
    int nbr22 = (x - 1) + ((y-1) * _divisions) + (z * pow(_divisions, 2)); //left bottom centre
    int nbr23 = x + ((y-1) * _divisions) + ((z + 1) * pow(_divisions, 2)); //centre bottom forward
    int nbr24 = x + ((y-1) * _divisions) + ((z - 1) * pow(_divisions, 2)); //centre bottom back





      m_cells[i].m_neighbours.push_back(nbr0);

      if((x + 1) < _divisions)
      {
        m_cells[i].m_neighbours.push_back(nbr1);
      }
      else
      {
        m_cells[i].m_neighbours.push_back(-1);
      }

      if((x - 1) >= 0)
      {
        m_cells[i].m_neighbours.push_back(nbr2);
      }
      else
      {
        m_cells[i].m_neighbours.push_back(-1);
      }

      if((y + 1) < _divisions)
      {
        m_cells[i].m_neighbours.push_back(nbr3);
      }
      else
      {
        m_cells[i].m_neighbours.push_back(-1);
      }

      if((y - 1) >= 0)
      {
        m_cells[i].m_neighbours.push_back(nbr4);
      }
      else
      {
        m_cells[i].m_neighbours.push_back(-1);
      }

      if((z + 1) < _divisions)
      {
        m_cells[i].m_neighbours.push_back(nbr5);
      }
      else
      {
        m_cells[i].m_neighbours.push_back(-1);
      }

      if((z - 1) >= 0)
      {
        m_cells[i].m_neighbours.push_back(nbr6);
      }
      else
      {
        m_cells[i].m_neighbours.push_back(-1);
      }*/


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
            //std::cout<<"neighbour "<<nbr<<std::endl;
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
