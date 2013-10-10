/* Corey Finley                               */
/* 7 October 2013                             */
/* Interactive viewing of two 3D teapots      */

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> 
#include <GL/gl.h>

int  l_click = GLUT_UP;
int  r_click = GLUT_UP;

int start_x1, start_y1, start_x2, start_y2;
double theta1, theta2, mouse_delta;

double HEIGHT = 500;
double WIDTH = 500;

void teapot1(){
  /* Size=1.0, Location: (-2.0, 0.0, -2.5)

     Material – 
      ambience (0.0215, 0.1745, 0.0215, 1.0), 
      diffusive (0.07568, 0.61424, 0.07568, 1.0), 
      specular (0.633, 0.727811, 0.633, 1.0), 
      shininess=0.6 */

  GLfloat amb[]={0.0215, 0.1745, 0.0215, 1.0};
  GLfloat diff[]={0.07568, 0.61424, 0.07568, 1.0};
  GLfloat spec[]={0.633, 0.727811, 0.633, 1.0};
  GLfloat shine[]={0.6};

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   amb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);

  glLoadIdentity();
  glTranslatef(-2.0,0.0,-2.5);
  glRotatef(theta1, 0, 1, 0);
  glutSolidTeapot(1.0);
}

void teapot2(){
  /* Size=1.0, Location: (2.0, 0.0, -2.5)

     Material – 
      ambience (0.2125, 0.1275, 0.054, 1.0), 
      diffusive (0.714, 0.4284, 0.18144, 1.0), 
      specular (0.393548, 0.271906, 0.166721, 1.0), 
      shininess=0.2 */
  glLoadIdentity();

  GLfloat amb[] ={0.2125,   0.1275,   0.054,    1.0};
  GLfloat diff[]={0.714,    0.4284,   0.18144,  1.0};
  GLfloat spec[]={0.393548, 0.271906, 0.166721, 1.0};
  GLfloat shine[]={0.2};

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   amb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);

  glTranslatef(2.0,0.0,-2.5);
  glRotatef(theta2, 0, 1, 0);
  glutSolidTeapot(1.0);
}

void setLighting(){
  glLoadIdentity();
  // lighting from assignment
  GLfloat position[]={.0, 3.0, -3.0, 1.0};
  GLfloat amb[]={1.0, 1.0, 1.0, 1.0};
  GLfloat dif[]={1.0, 1.0, 1.0, 1.0};
  GLfloat spc[]={1.0, 1.0, 1.0, 1.0};
  GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat local_view[] = {0.0};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spc);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

  gluLookAt(         // Eye
    0.0, 0.0, 0.0,   // Location
    0.0, 0.0, -1.0,  // Direction
    0.0, 1.0, 0.0);  // Up Direction
}

void init()
{
  glClearColor (0.0,0.0,0.0,1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5.0, 5.0, -5.0, 5.0, 0.0, 5.0); // bounding volume for the projection
  glMatrixMode(GL_MODELVIEW);
  
  glEnable(GL_DEPTH_TEST);    // enable hidden surface removal

  setLighting();
}

/* Callbacks */
// display frame
void display(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  teapot1(); //draw teapot1
  teapot2(); //draw teapot2
  glutSwapBuffers();
}

// interprate keyboard functions
void keyboard(unsigned char key, int x, int y){
}

// interprate mouse clicks
void mouseClick(int button, int state, int x, int y){
  if(GLUT_LEFT_BUTTON == button){
    start_x1 = x;
    start_y1 = y;
    l_click = state;
  }
  if(GLUT_RIGHT_BUTTON == button){
    start_x2 = x;
    start_y2 = y;
    r_click = state;
  }
}

// interprate mouse motion
void mouseMotion(int x, int y){
  if(l_click == GLUT_DOWN){
    mouse_delta = sqrt(pow((x-start_x1), 2) + pow((y-start_y1),2));
    theta1 = theta1+(360*mouse_delta/sqrt(HEIGHT*HEIGHT+WIDTH*WIDTH));
    glutPostRedisplay();
  }
  if(r_click == GLUT_DOWN){
    mouse_delta = sqrt(pow((x-start_x2), 2) + pow((y-start_y2),2));
    theta2 = theta2+(360*mouse_delta/sqrt(HEIGHT*HEIGHT+WIDTH*WIDTH));
    glutPostRedisplay();
  }
}



/* Main */
int main(int argc, char* argv[])
{
	/* standard GLUT initialization */
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(HEIGHT,WIDTH); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Teapot Display"); /* window title */

    init(); /* set attributes */

    /* Call Backs */
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutMainLoop(); /* enter event loop */
}
