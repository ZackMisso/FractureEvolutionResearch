#include <GL/glut.h>
#include <iostream>
#include "src/include/GL/glui.h"
#include "fracture.h"
#include "array.h"


using namespace std;

void createInterface();
void display();
void mouseClick(int button,int state,int x,int y);
void mouseMotion(int x,int y);
void keyboard(unsigned char key,int x,int y);
void reshape(int w,int h);
void mainLoop(void);

// Arguements
GLUI* subwindow;
Array<Fracture*>* fractures;
int activeFracture;
int window;


int main(int argc,char** argv) {
  cout << "Beginning Initialization" << endl;
  fractures = new Array<Fracture*>();
	fractures->add(new Fracture());
	activeFracture = 0;

	glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1200,1000);
  window = glutCreateWindow("Zackary Misso - Scene Graph Editor");
  // init the callbacks
  glutDisplayFunc(display);
  //glutMotionFunc(mouseMotion);
  //GLUI_Master.set_glutKeyboardFunc(keyboard);
  //GLUI_Master.set_glutMouseFunc(mouseClick);
  //GLUI_Master.set_glutReshapeFunc(reshape);
  //GLUI_Master.set_glutIdleFunc(mainLoop);
  // create the subwindow
  //subwindow = GLUI_Master.create_glui_subwindow(window,GLUI_SUBWINDOW_LEFT);
  //createInterface();
  //glEnable(GL_DEPTH_TEST);
  //glClearColor(0.0,0.0,0.0,1.0);
  //glMatrixMode(GL_PROJECTION);
  //gluPerspective(60,1,.1,100);
  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  //glEnable(GL_CULL_FACE);
  cout << "Finished Initialization" << endl;
  glutMainLoop();

  return 0;
}

void createInterface() {
  // to be implemented
}

void display() {
  cout << "RUNNING" << endl;
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_QUADS);
  glColor3f(1.0f,0.0f,0.0f);
  glVertex2f(-0.5f,-0.5f);
  glVertex2f(-0.5f,0.5f);
  glVertex2f(0.5f,0.5f);
  glVertex2f(0.5f,-0.5f);
  glEnd();
  glutSwapBuffers();
}

void mouseClick(int button,int state,int x,int y) {
  // to be implemented
}

void mouseMotion(int x,int y) {
  // to be implemented
}

void keyboard(unsigned char key,int x,int y) {
  // to be implemented
}

void reshape(int w,int h) {
  // to be implemented
}

void mainLoop(void) {
  // probably not going to use
}
