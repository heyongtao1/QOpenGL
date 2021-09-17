/*

    Qt OpenGL Tutorial - Lesson 04

    nehewidget.cpp
    v 1.00
    2002/12/18

    Copyright (C) 2002 Cavendish
                       cavendish@qiliang.net
                       http://www.qiliang.net/nehe_qt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

*/

#include "nehewidget.h"
#include <QDebug>
NeHeWidget::NeHeWidget( QWidget* parent, const char* name, bool fs )
    : QGLWidget( parent )
{
  timer = new QTimer();
  connect(timer,&QTimer::timeout,this,[=](){
      rTri += 3.0;
      rQuad -= 1.0;
      updateGL();
  });
  timer->start(200);
  rTri = 0.0;
  rQuad = 0.0;
  fullscreen = fs;
  setGeometry( 200, 200, 640, 480 );
  //setCaption( "NeHe's Rotation Tutorial" );

  if ( fullscreen )
    showFullScreen();
}

NeHeWidget::~NeHeWidget()
{
    timer->deleteLater();
    timer = nullptr;
}

void NeHeWidget::paintGL()
{
    qDebug() << "update";
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  glTranslatef( -1.5,  0.0, -6.0 );
  glRotatef( rTri,  0.0,  1.0,  0.0 );

  glBegin( GL_TRIANGLES );
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f(  0.0,  1.0,  0.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
  glEnd();
  
  glLoadIdentity();
  glTranslatef(  1.5,  0.0, -6.0 );
  glRotatef( rQuad,  1.0,  0.0,  0.0 );

  glColor3f( 0.5, 0.5, 1.0 );
  glBegin( GL_QUADS );
    glVertex3f( -1.0,  1.0,  0.0 );
    glVertex3f(  1.0,  1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
  glEnd();
  
  //rTri += 1.0;
  //rQuad -= 0.15;
}

void NeHeWidget::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0, 0.0, 0.0, 0.5 );
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
