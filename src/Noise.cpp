
#include "Noise.h"
#include <iostream>

namespace Noise
{

  ngl::Vec3 ComputeNoise(ngl::Vec3 _particle_pos, std::vector <ngl::Vec3> _gradients)
  {

//    for(int i = 0; i < _gradients.size(); i ++)
//    {
//      std::cout<<"neighbour gradients: "<<_gradients[i].m_x << ", " << _gradients[i].m_y << ", " << _gradients[i].m_z << std::endl;
//    }
    return ngl::Vec3(0,0,0);
  }

  //void FindContributions(std::vector <ngl::Vec3> _gradients, ngl::Real _u, ngl::Real _v, ngl::Real _w)
  //{

  //}

}



