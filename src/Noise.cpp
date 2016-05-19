#include "Noise.h"
#include <iostream>

namespace Noise
{

  ngl::Vec3 ComputeNoise(ngl::Vec3 _particle_pos, ngl::Vec3 _cell_pos,float _size, int _divs, std::vector <ngl::Vec3> _gradients)
  {
//    Xd = (x - x0)/(x1 - x0)
//    Yd = (y - y0)/(y1 - y0)
//    Zd = (z - z0)/(z1 - z0)
    ngl::Real cell_size = _size/_divs;
    ngl::Real x0 = _cell_pos.m_x - (cell_size*0.5);
    ngl::Real x1 = _cell_pos.m_x + (cell_size*0.5);

    ngl::Real y0 = _cell_pos.m_y - (cell_size*0.5);
    ngl::Real y1 = _cell_pos.m_y + (cell_size*0.5);

    ngl::Real z0 = _cell_pos.m_z - (cell_size*0.5);
    ngl::Real z1 = _cell_pos.m_z + (cell_size*0.5);


    ngl::Real Xd = (_particle_pos.m_x - x0)/(x1 - x0);
    ngl::Real Yd = (_particle_pos.m_y - y0)/(y1 - y0);
    ngl::Real Zd = (_particle_pos.m_z - z0)/(z1 - z0);



    return TrilinearInterpolation(_gradients, Xd, Yd, Zd);

    //return ngl::Vec3(0,0,0);
  }

  ngl::Vec3 TrilinearInterpolation(std::vector <ngl::Vec3> _gradients, ngl::Real _Xd, ngl::Real _Yd, ngl::Real _Zd)
  {
    ngl::Vec3 c00 = _gradients[0] * (1 - _Xd) + _gradients[4] * (_Xd);
    ngl::Vec3 c01 = _gradients[1] * (1 - _Xd) + _gradients[5] * (_Xd);
    ngl::Vec3 c10 = _gradients[2] * (1 - _Xd) + _gradients[6] * (_Xd);
    ngl::Vec3 c11 = _gradients[3] * (1 - _Xd) + _gradients[7] * (_Xd);

    ngl::Vec3 c0 = c00 * (1 - _Yd) + (c10 * _Yd);
    ngl::Vec3 c1 = c01 * (1 - _Yd) + (c11 * _Yd);

    ngl::Vec3 c = c0 * (1 - _Zd) + c1 * _Zd;

    return c;
  }

}



