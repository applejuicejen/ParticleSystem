#include "Noise.h"
#include <iostream>

namespace Noise
{

  ngl::Vec3 ComputeNoise(ngl::Vec3 _particle_pos, ngl::Vec3 _cell_pos,float _size, int _divs, std::vector <ngl::Vec3> _gradients)
  {
    ngl::Real cell_size = _size/_divs;
    ngl::Real u = (_cell_pos.m_x - (cell_size*0.5)) - _particle_pos.m_x;
    ngl::Real v = (_cell_pos.m_y - (cell_size*0.5)) - _particle_pos.m_y;
    ngl::Real w = (_cell_pos.m_z - (cell_size*0.5)) - _particle_pos.m_z;

    std::cout<<"cell.x : "<< _cell_pos.m_x - (cell_size*0.5) <<std::endl;

    std::cout<<"U: "<< u<<std::endl;
    //FindContributions(_gradients);

    std::cout<<"particle position: " << _particle_pos.m_x << ", "<<_particle_pos.m_y<<", "<<_particle_pos.m_z<<std::endl;
    std::cout<<"cell position: " << _cell_pos.m_x << ", "<<_cell_pos.m_y<<", "<<_cell_pos.m_z<<std::endl;


//    for(int i = 0; i < _gradients.size(); i ++)
//    {
//      std::cout<<"neighbour gradients: "<<_gradients[i].m_x << ", " << _gradients[i].m_y << ", " << _gradients[i].m_z << std::endl;
//    }
    return ngl::Vec3(0,0,0);
  }

  void FindContributions(std::vector <ngl::Vec3> _gradients, ngl::Real _u, ngl::Real _v, ngl::Real _w)
  {

  }

}



