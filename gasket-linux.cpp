/* Corey Finley                               */
/* 1 October 2013                             */
/* Addapted from Gasket file supplied on      */
/* dropbox.                                   */

/* two-dimensional Sierpinski gasket          */
/* generated using randomly selected vertices */
/* and bisection                              */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h> 
#include <fstream>
#include <iostream>

#define PI 3.14159265

/* you may have to change the include to <glut.h> or
elsewhere depending on where it is stored on your system */

/* glut.h usually has includes for gl.h and glu.h */
/* global rotation factor F and subdivisions M */
double F, M;

void myinit()
{

/* attributes */

      glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
      glColor3f(1.0, 0.0, 0.0); /* draw in red */

/* set up viewing */
/* 50.0 x 50.0 camera coordinate window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0, 50.0, 0.0, 50.0);
      glMatrixMode(GL_MODELVIEW);
}

void display()
{
    /* A triangle */
    GLfloat vertices[3][2]={{0.0,0.0},{25.0,50.0},{50.0,0.0}};

    int j, k;
	// distance from origin
	double distance = 0;

    GLfloat p0[2] ={7.5, 5.0};  /* arbitrary initial point inside triangle */
	GLfloat p1[2]; /* a second point for post rotation */
    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
    glBegin(GL_POINTS);

/* compute and plot 2^M new points */
/* M being the number of subdivisions */
    for( k=0; k<pow(2.0, M); k++)
    {
         j=rand()%3; /* pick a vertex at random */

     /* compute point halfway between selected vertex and old point */

         p0[0] = (p0[0]+vertices[j][0])/2.0;
         p0[1] = (p0[1]+vertices[j][1])/2.0;

	 /* get base coordinates for rotation */
		 p1[0] = p0[0];
		 p1[1] = p0[1];

	 /* calculate distance from origin */
		 distance = sqrt(pow(p0[1], 2.0)+pow(p0[2], 2.0));

	 /* rotate the point */

		 p1[0] = p0[0]*cos(distance*F)-p0[1]*sin(distance*F);
		 p1[1] = p0[0]*sin(distance*F)+p0[1]*cos(distance*F);

     /* plot new point */

         glVertex2fv(p1);

    }
     glEnd();
     glFlush(); /* clear buffers */
 }

int main(int argc, char* argv[])
{
	/* get f and m from the command line */
	if( argc != 3 ){
    	std::cout<<"usage: "<< argv[0] <<" <f> <m>\n";
		exit(1);
  	}else{
		F = atof(argv[1]);
		M = atof(argv[2]);
		std::cout << "f = " << F << " and m = " << M << std::endl; 
	}

/* standard GLUT initialization */

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Sierpinski Gasket Rotation"); /* window title */
    glutDisplayFunc(display);
              /* display callback invoked when window opened */
    myinit(); /* set attributes */
    glutMainLoop(); /* enter event loop */
}
