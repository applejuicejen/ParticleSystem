#include "Emitter.h"
#include <ngl/NGLInit.h>

Emitter::Emitter()
{

}

void Emitter::Initialize(float _num_particles,  ngl::Vec3 _initial_pos, ngl::Vec3 _initial_vel, float _lifespan, float _mass)
{
  for(int i = 0; i < _num_particles; i++)
  {
    ngl::Vec3 line = _initial_pos;
    //line.m_x = i*0.1;
    Particle p(false,i);
    p.setPosition(line);
    p.setInitPosition(line);
    p.setLifespan(_lifespan);
    p.setMass(_mass);
    p.setVelocity(_initial_vel);
    p.setInitVelocity(_initial_vel);
    m_particles.push_back(p);
  }
  //std::cout<<"num of particles: "<< m_particles.size()<<std::endl;
}

void Emitter::Emit()
{
  float particlesPF = 50;
  if(m_current_time > m_last_emission + m_emission_rate)
  {
    int active_particles = 0;
    for(int i = 0; i < m_particles.size(); i ++)
    {

      if(m_particles[i].getActive() == false)
      {
        m_particles[i].setActive(true);
        active_particles += 1;
        m_particles[i].Reset();

        if(active_particles >= particlesPF)
        {
          //i = m_particles.size();
          break;
        }
        m_last_emission = m_current_time;
      }
    }
  }

//  float active_particles;
//  for(int i = 0; i < m_particles.size(); i ++)
//  {

//    if(m_particles[i].getActive() == false)
//    {
//      m_particles[i].setActive(true);
//      active_particles += 1;
//      m_particles[i].Reset();

//      if(active_particles >= particlesPF)
//      {
//        //i = m_particles.size();
//        break;
//      }
//    }
//  }
  //std::cout<<"emission rate: "<<m_emission_rate<<std::endl;
}

void Emitter::Update()
{
  Emit();
  for(int i = 0; i < m_particles.size(); i ++)
  {
    if(m_particles[i].getActive()==true)
    {
      m_particles[i].Update(m_dt);
    }
  }
  m_current_time += m_dt;
  //std::cout<<"errrrooo"<<std::endl;
}

void Emitter::Draw()
{

  struct data
  {
    ngl::Vec3 pos;
    ngl::Vec3 colour;
  };

  std::vector<data> activeParticles;
  for(int i = 0; i < m_particles.size(); i ++)
  {
    if(m_particles[i].getActive() == true)
    {
      data p;
      p.pos = m_particles[i].getPosition();
      p.colour = m_particles[i].getColour();
      activeParticles.push_back(p);
    }
  }

  ngl::VertexArrayObject *vao=ngl::VertexArrayObject::createVOA(GL_POINTS);
  vao->bind();
  vao->setData(activeParticles.size()*sizeof(data),activeParticles[0].pos.m_x);
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(data),0);
  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(data),3);
  vao->setNumIndices(activeParticles.size());
  vao->draw();
  vao->unbind();
  vao->removeVOA();
  delete vao;
}


