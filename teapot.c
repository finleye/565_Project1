/* Corey Finley                               */
/* 7 October 2013                             */
/* Interactive viewing of two 3D teapots      */

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> 
#include <GL/gl.h>

void drawTeapots(){
  glTranslatef(-2.0,0.0,-2.5);
	glutSolidTeapot(1.0);
	glTranslatef(4.0,0.0,0);
  glutSolidTeapot(1.0);
}

void init()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5.0, 5.0, -5.0, 5.0, 0.0, 5.0); // bounding volume for the projection
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  

  glEnable(GL_DEPTH_TEST);    // enable hidden surface removal

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // glShadeModel(GL_FLAT);   // flat shading
  glShadeModel(GL_SMOOTH);    // smooth shading
}

void display()
{
  glClearColor (0.0,0.0,0.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  // From assignment description for lighting
  GLfloat position[]={.0, 3.0, -3.0, 1.0};
  GLfloat amb[]={1.0, 1.0, 1.0, 1.0};
  GLfloat dif[]={1.0, 1.0, 1.0, 1.0};
  GLfloat spc[]={1.0, 1.0, 1.0, 1.0};
  GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat local_view[] = {0.0};

  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spc);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

  gluLookAt(        // Eye
    0.0, 0.0, 0.0,  // Location
    0.0, 0.0, -1.0, // Direction
    0.0, 1.0, 0.0);  // Up Direction

  drawTeapots();
  glutSwapBuffers();
 }

int main(int argc, char* argv[])
{
	/* standard GLUT initialization */
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(600,600); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Teapot Display"); /* window title */

    init(); /* set attributes */
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop(); /* enter event loop */
}
