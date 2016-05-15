
#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>

typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 12);

rng_type rng;
#include <ngl/NGLInit.h>

Cell::Cell()
{

}

void Cell::Initialize(int _ID)
{
  ngl::Vec3 g0 = (0,1,1);
  ngl::Vec3 g1 = (0,1,-1);
  ngl::Vec3 g2 = (0,-1,1);
  ngl::Vec3 g3 = (0,-1,-1);
  ngl::Vec3 g4 = (1,0,1);
  ngl::Vec3 g5 = (1,0,-1);
  ngl::Vec3 g6 = (-1,0,1);
  ngl::Vec3 g7 = (-1,0,-1);
  ngl::Vec3 g8 = (1,1,0);
  ngl::Vec3 g9 = (1,-1,0);
  ngl::Vec3 g10 = (-1,1,0);
  ngl::Vec3 g11 = (-1,-1,0);

  m_gradients.push_back(g0);
  m_gradients.push_back(g1);
  m_gradients.push_back(g2);
  m_gradients.push_back(g3);
  m_gradients.push_back(g4);
  m_gradients.push_back(g5);
  m_gradients.push_back(g6);
  m_gradients.push_back(g7);
  m_gradients.push_back(g8);
  m_gradients.push_back(g9);
  m_gradients.push_back(g10);
  m_gradients.push_back(g11);

  rng_type::result_type const seedval = _ID;
  rng.seed(seedval);

  rng_type::result_type random_number = udist(rng);

  m_gradient = m_gradients[random_number];
  std::cout<<"gradient " <<m_gradient.m_x<< ", "<< m_gradient.m_y << ", " << m_gradient.m_z<<std::endl;

}

void Cell::setCell()
{

}


void Cell::Update(float _timestep)
{

}

void Cell::Reset()
{

}

void Cell::Draw()
{


  struct data
  {
    ngl::Vec3 pos;
    ngl::Vec3 colour;
  };

  std::vector<data> points;
  //cell.setSize(200);

  ngl::Real half_size = m_size*0.5;

  data p;
  p.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_size,
                              m_position.m_y + half_size,
                              m_position.m_z + half_size));
  p.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(p);

  data p1;
  p1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_size,
                               m_position.m_y + half_size,
                               m_position.m_z - half_size));
  p1.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(p1);

  data q;
  q.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                              m_position.m_y + half_size,
                              m_position.m_z + half_size));
  q.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(q);

  data q1;
  q1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                               m_position.m_y + half_size,
                              m_position.m_z - half_size));
  q1.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(q1);

  data s;
  s.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                              m_position.m_y - half_size,
                              m_position.m_z + half_size));
  s.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(s);

  data s1;
  s1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                               m_position.m_y - half_size,
                               m_position.m_z - half_size));
  s1.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(s1);

  data r;
  r.pos = ngl::Vec3(ngl::Vec3(m_position.m_x-half_size,
                              m_position.m_y-half_size,
                              m_position.m_z + half_size));
  r.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(r);

  data r1;
  r1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x-half_size,
                               m_position.m_y-half_size,
                               m_position.m_z - half_size));
  r1.colour = ngl::Vec3(0.7, 0.7, 0.7);
  points.push_back(r1);

  const static GLubyte indices[]=  {
                                      0,1,3,2, //top
                                      4,5,3,2,
                                      4,6,0,2,
                                      0,1,7,6,
                                      7,5,4,6
                                   };

  ngl::VertexArrayObject *vao=ngl::VertexArrayObject::createVOA(GL_LINE_LOOP);
  vao->bind();
  vao->setRawIndexedData(sizeof(data)*sizeof(points),&points[0],sizeof(indices),&indices[0],GL_UNSIGNED_BYTE,GL_STATIC_DRAW);
  vao->setData(points.size()*sizeof(data),points[0].pos.m_x);
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(data),0);
  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(data),3);
  vao->setNumIndices(sizeof(indices));
  vao->draw();
  vao->unbind();
  vao->removeVOA();
  delete vao;
}
