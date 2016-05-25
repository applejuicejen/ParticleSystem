#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <iostream>
#include <cmath>
#include "Emitter.h"
#include "Noise.h"


//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=2.1;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=15.0;

NGLScene::NGLScene(int _timer)
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Smoke Simulation");

  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0;
  m_spinYFace=0;
  m_timerValue = _timer;
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(QResizeEvent *_event)
{
  m_width=_event->size().width()*devicePixelRatio();
  m_height=_event->size().height()*devicePixelRatio();
  m_cam.setShape(45.0f,(float)width()/height(),0.05f,350.0f);
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();
  m_cam.setShape(45.0f,(float)_w/_h,0.05f,350.0f);
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  /*===CAMERA===*/
  //creating static camera

  m_grid_size = 500;
  m_grid_divs = 4;
  ngl::Vec3 from(m_grid_size/2,m_grid_size/2,2000);
  ngl::Vec3 to(m_grid_size/2,m_grid_size/2,m_grid_size/2);
  ngl::Vec3 up(0,1,0);

  m_cam.set(from,to,up);
  m_cam.setShape(45,(float)720.0f/576.0f, 0.001,2500);

  /*===SHADERS===*/
  // grab an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  shader->createShaderProgram("Colour");

  shader->attachShader("ColourVertex",ngl::ShaderType::VERTEX);
  shader->attachShader("ColourFragment",ngl::ShaderType::FRAGMENT);
  shader->loadShaderSource("ColourVertex","shaders/colour.vs");
  shader->loadShaderSource("ColourFragment","shaders/colour.fs");

  shader->compileShader("ColourVertex");
  shader->compileShader("ColourFragment");
  shader->attachShaderToProgram("Colour","ColourVertex");
  shader->attachShaderToProgram("Colour","ColourFragment");

  shader->bindAttribute("Colour",0,"inVert");

  shader->linkProgramObject("Colour");
  (*shader)["Colour"]->use();

  shader->setShaderParam4f("Colour",1.0,1.0,0.0,1);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_ONE, GL_ONE);
  glPointSize(3);

  m_timerValue = 15;
  startSimTimer();

  m_ps.Initialize(10000, ngl::Vec3(0, m_grid_size, 0), m_grid_size*2, ngl::Vec3(0, 0, 0), 6.0, 0.6);
  m_ps.setTimestep((float)m_timerValue/1000.0f);
  //cell.Initialize();
  //ngl::Real size = 30;
  //cell.setSize(size);
  //cell.setGravity(ngl::Vec3(5.5,0,0));
  m_grid.Initialize(m_grid_size, m_grid_divs);

}

void NGLScene::timerEvent( QTimerEvent *_event)
{
  if(_event->timerId()== m_timer)
  {
    for (int i = 0; i < m_ps.m_particles.size(); i ++)
    {
      ngl::Vec3 pos = m_ps.m_particles[i].m_position;
      pos/=(m_grid_size/m_grid_divs);

      int x = (int)pos.m_x;
      int y = (int)pos.m_y;
      int z = (int)pos.m_z;

      int cell_num = x + (y * m_grid_divs) + (z * pow(m_grid_divs, 2));


//      ngl::Vec3 point = m_ps.m_particles[i].m_position;
//      ngl::Vec3 cell = m_grid.m_cells[cell_num].m_position;
//      int x_sign = 1;
//      int y_sign = 1;
//      int z_sign = 1;

//      if(point.m_x < cell.m_x)
//      {
//        x_sign = -1;
//      }
//      if(point.m_y < cell.m_y)
//      {
//        y_sign = -1;
//      }
//      if(point.m_z < cell.m_z)
//      {
//        z_sign = -1;
//      }

//      std::vector<ngl::Vec3> gradients;
//      findGradients(cell_num, x, y, z, gradients);
//      findGradients(cell_num, x, y, (z + z_sign), gradients);
//      findGradients(cell_num, x, (y + y_sign), z, gradients);
//      findGradients(cell_num, x, (y + y_sign), (z + z_sign), gradients);

//      findGradients(cell_num, (x + x_sign), y, z, gradients);
//      findGradients(cell_num, (x + x_sign), y, (z + z_sign), gradients);
//      findGradients(cell_num, (x + x_sign), (y + y_sign), z, gradients);
//      findGradients(cell_num, (x + x_sign), (y + y_sign), (z + z_sign), gradients);

      if(x < 0 || y < 0 || z < 0 || x >= m_grid_divs || y >= m_grid_divs || z >= m_grid_divs)
      {
        continue;
      }
      else
      {

//          ngl::Vec3 noise = Noise::ComputeNoise(m_ps.m_particles[i].m_position, m_grid.m_cells[cell_num].getPosition(),
//                              m_grid_size, m_grid_divs, gradients);
//          std::cout<<"noise " << noise.m_x <<", "<< noise.m_y << ", " << noise.m_z << std::endl;
            ngl::Vec3 f = m_grid.m_cells[cell_num].m_force*70;
            ngl::Vec3 direction = ngl::Vec3(m_grid_size/2,m_grid_size/2,m_grid_size/2)-m_ps.m_particles[i].m_position;

            m_ps.m_particles[i].addForce(f+(direction*0.9));
      }

    }
    //std::cout<<"paraaaaaaa"<<std::endl;
    m_ps.Update();
  }
  update();

}


void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_width,m_height);

  //create rotation matrices
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;

  rotX.rotateX(m_spinXFace);
  rotY.rotateY(m_spinYFace);

  //multiply the rotations
  m_mouseGlobalTX = rotY * rotX;

  //add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  ngl::Transformation trans;
  trans.setRotation(m_spinXFace,m_spinYFace,0);
  // set this in the TX stack
  ngl::Mat4 MV;
  ngl::Mat4 MVP;

  MV=trans.getMatrix()*m_cam.getViewMatrix() ;
  MVP=MV*m_cam.getProjectionMatrix() ;

  MVP = m_mouseGlobalTX*m_cam.getVPMatrix();

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  (*shader)["Colour"]->use();
  shader->setShaderParamFromMat4("MVP",MVP);

  m_ps.Draw();
  //m_grid.Draw();






}



//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent (QMouseEvent * _event)
{
  if(m_rotate && _event->buttons() == Qt::LeftButton)
  {
    int diffx = _event->x() - m_origX;
    int diffy = _event->y() - m_origY;
    m_spinXFace += (float) 0.5f * diffy;
    m_spinYFace += (float) 0.5f * diffx;
    m_origX = _event->x();
    m_origY = _event->y();
    update();
  }
  else if(m_translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();
  }
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent ( QMouseEvent * _event)
{
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate = true;
  }
  else if(_event->button() == Qt::RightButton)
  {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_translate = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent ( QMouseEvent * _event )
{
  if(_event->button() == Qt::LeftButton)
  {
    m_rotate = false;
  }
  if(_event->button() == Qt::RightButton)
  {
    m_translate = false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{
  if(_event->delta() > 0)
  {
    m_modelPos.m_z += ZOOM;
  }
  else if(_event->delta() < 0)
  {
    m_modelPos.m_z -= ZOOM;
  }
  update();
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
  // turn off wire frame
  case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
  // show full screen
  case Qt::Key_F : showFullScreen(); break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}


void NGLScene::startSimTimer()
{
  m_timer=startTimer(m_timerValue);
}

void NGLScene::stopSimTimer()
{
 killTimer(m_timer);
}

void NGLScene::findGradients(int _cell_num, int _x, int _y, int _z, std::vector<ngl::Vec3> &_gradients )
{

  int index = _cell_num;

  index =  _x + (_y * m_grid_divs) + ((_z) * pow(m_grid_divs, 2));

  if((_x < m_grid_divs && _x >= 0) && (_y < m_grid_divs && _y >= 0) && _z < m_grid_divs && _z >= 0)
  {
    _gradients.push_back(m_grid.m_cells[index].getGradient());
  }
  else
  {
    _gradients.push_back(ngl::Vec3(0,0,0));
  }
}
