/*

    Qt OpenGL Tutorial - Lesson 02

    nehewidget.cpp
    v 1.00
    2002/12/05

    Copyright (C) 2002 Cavendish
                       cavendish@qiliang.net
                       http://www.qiliang.net/nehe_qt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

*/

#include "nehewidget.h"

NeHeWidget::NeHeWidget( QWidget* parent, const char* name, bool fs )
    : QGLWidget(parent)
{
  fullscreen = fs;
  setGeometry( 200, 200, 640, 480 );
  //setCaption( "NeHe's First Polygon Tutorial" );
  if ( fullscreen )
    showFullScreen();
}

NeHeWidget::~NeHeWidget()
{
}

void NeHeWidget::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  //原点坐标的转换
  glTranslatef( -1.5,  0.0, -6.0 );
  //开始绘制三角形
  glBegin( GL_TRIANGLES );
    glVertex3f(  0.0,  1.0,  0.0 );
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
  //绘制结束
  glEnd();
  //原点坐标的转换
  glTranslatef(  3.0,  0.0,  0.0 );
  //开始绘制四边形
  glBegin( GL_QUADS );
    glColor3f( 0.5, 0.5, 1.0 );
    glVertex3f( -1.0,  1.0,  0.0 );
    glVertex3f(  1.0,  1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
  glEnd();
}

void NeHeWidget::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0, 0.0, 0.0, 0.0 );
  glClearDepth( 1.0 );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void NeHeWidget::resizeGL( int width, int height )
{
  if ( height == 0 )
  {
    height = 1;
  }
  glViewport( 0, 0, (GLint)width, (GLint)height );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void NeHeWidget::keyPressEvent( QKeyEvent *e )
{
  switch ( e->key() )
  {
  case Qt::Key_F2:
    fullscreen = !fullscreen;
    if ( fullscreen )
    {
      showFullScreen();
    }
    else
    {
      showNormal();
      setGeometry( 0, 0, 640, 480 );
    }
    update();
    break;
  case Qt::Key_Escape:
    close();
  }
}
