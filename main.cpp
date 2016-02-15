#include <GL/glut.h>
#include <iostream>
#include "src/include/GL/glui.h"

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
int window;

int main(int argc,char** argv) {
  cout << "Beginning Initialization" << endl;
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1200,1000);
  window = glutCreateWindow("Zackary Misso - Scene Graph Editor");
  // init the callbacks
  glutDisplayFunc(display);
  glutMotionFunc(mouseMotion);
  GLUI_Master.set_glutKeyboardFunc(keyboard);
  GLUI_Master.set_glutMouseFunc(mouseClick);
  GLUI_Master.set_glutReshapeFunc(reshape);
  GLUI_Master.set_glutIdleFunc(mainLoop);
  // create the subwindow
  subwindow = GLUI_Master.create_glui_subwindow(window,GLUI_SUBWINDOW_LEFT);
  createInterface();
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0,0.0,0.0,1.0);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(60,1,.1,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_CULL_FACE);
  cout << "Finished Initialization" << endl;
  glutMainLoop();
}

void createInterface() {
  // to be implemented
}

void display() {
  // to be implemented
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
