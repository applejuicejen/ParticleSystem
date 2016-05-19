#ifndef NOISE_H
#define NOISE_H

#include "ngl/Vec3.h"
#include <vector>

namespace Noise
{

  ngl::Vec3 ComputeNoise(ngl::Vec3 _particle_pos, ngl::Vec3 _cell_pos,float _size, int _divs, std::vector <ngl::Vec3> _gradients);
  ngl::Vec3 TrilinearInterpolation(std::vector <ngl::Vec3> _gradients, ngl::Real _Xd, ngl::Real _Yd, ngl::Real _Zd);

}



#endif // NOISE_H

