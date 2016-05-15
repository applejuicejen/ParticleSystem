#include "Particle.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

Particle::Particle(bool _active, int _ID)
{
  m_active = _active;
  m_gravity = ngl::Vec3(0, -9.8, 0);

  srand(_ID);
  ngl::Real r = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  ngl::Real g = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  ngl::Real b = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  m_colour = ngl::Vec3(r,g,b);
}

void Particle::Update(float _timestep)
{
    //std::cout<< "helooooooo"<<std::endl;
    //std::cout<< m_gravity.m_y <<std::endl;
    //std::cout<<"m_force "<< m_force.m_x<< ", "<< m_force.m_y<< ", "<< m_force.m_z<<std::endl;
    m_force += m_gravity;
    //drag
    m_force += m_velocity;
    ngl::Vec3 acc;
    acc = m_force / (m_mass);
    m_position += m_velocity * _timestep;
    m_velocity += _timestep * acc;
    m_lifeleft -= _timestep;
    m_force = ngl::Vec3(0,0,0);
    if (m_lifeleft <= 0)
    {
      m_active = false;
    }
    //std::cout<<"point: " << m_position.m_x<< ", "<< m_position.m_y<< ", "<< m_position.m_z<<std::endl;
}

void Particle::addForce(ngl::Vec3 _force)
{
  m_force += _force;
  //std::cout<<"m_force "<< m_force.m_x<< ", "<< m_force.m_y<< ", "<< m_force.m_z<<std::endl;
  //std::cout<<"_force "<< _force.m_x<< std::endl;
}

void Particle::Reset()
{
  m_position = ngl::Vec3(m_init_position.m_x+(-5 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/10.0f)),
                         m_init_position.m_y,
                         m_init_position.m_z+(-5 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/10.0f)));;
  m_velocity = ngl::Vec3(-5 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/10.0f),
                         -3 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/7.0f),
                         -5 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/10.0f));
  m_lifeleft = m_lifespan;
}

