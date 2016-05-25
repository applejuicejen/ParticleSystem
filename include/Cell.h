#ifndef CELL_H
#define CELL_H
#include <ngl/Vec3.h>
#include <vector>
#include <iostream>

class Cell
{
public:
  Cell();
  void Initialize(int _ID);
  void Update(float _timestep);
  void Reset();
  void setCell();
  void Draw();

  ngl::Vec3 getPosition(){return m_position;}
  void setPosition(ngl::Vec3 _position){m_position = _position;}

  ngl::Vec3 getVelocity(){return m_velocity;}
  void setVelocity(ngl::Vec3 _velocity){m_velocity = _velocity;}

  ngl::Vec3 getInitVelocity(){return m_init_velocity;}
  void setInitVelocity(ngl::Vec3 _velocity){m_init_velocity = _velocity;}

  ngl::Vec3 getGravity(){return m_gravity;}
  void setGravity(ngl::Vec3 _gravity){ m_gravity = _gravity;}

  ngl::Real getSize(){return m_size;}
  void setSize(ngl::Real _size){ m_size = _size;}

  void setForce(ngl::Vec3 _force){m_force = _force;}
  void setCellForces(float _size);
  ngl::Vec3 getGradient(){return m_gradient;}
  void setGradient(ngl::Vec3 _gradient){m_gradient = _gradient;}

  ngl::Vec3 m_force;
  std::vector<int> m_neighbours;
  std::vector<ngl::Vec3> m_gradients;
  ngl::Vec3 m_position;



private:

  ngl::Vec3 m_velocity;
  ngl::Vec3 m_init_velocity;
  ngl::Vec3 m_gravity;
  float m_pressure;
  ngl::Real m_size;
  ngl::Vec3 m_gradient;

  std::vector<ngl::Vec3> m_gradient_set;
  std::vector<ngl::Vec3> m_square;
};
#endif // CELL_H

