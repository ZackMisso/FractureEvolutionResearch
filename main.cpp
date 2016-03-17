// USE ON LINUX
#include <GL/glut.h>
// USE ON MAC
//#include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
//#include <GLUT/glut.h>

#include <iostream>
#include "src/include/GL/glui.h"
#include "fracture.h"
#include "array.h"
#include "interface.h"
#include "programData.h"
#include "renderSettings.h"
#include "mutations.h"
#include "tests.h"
#include "debugController.h"

using namespace std;

void createInterface();
void display();
void mouseClick(int button,int state,int x,int y);
void mouseMotion(int x,int y);
void keyboard(unsigned char key,int x,int y);
void reshape(int w,int h);
void mainLoop(void);
bool unitTests();

// callbacks
void cb_saveFracture(int id);
void cb_loadFracture(int id);
void cb_clearFracture(int id);
void cb_vertsOnOff(int id);
void cb_edgesOnOff(int id);
void cb_facesOnOff(int id);
void cb_randomMutation(int id);
void cb_trimeshOnOff(int id);

// Arguements
GLUI* subwindow;
Interface* interface;
ProgramData* programData;
RenderSettings* renderSettings;
int window;


int main(int argc,char** argv) {
  cout << "Beginning Initialization" << endl;
  DebugController::init();
  cout << "Running Unit Tests" << endl;
  if(unitTests()) {
    cout << "Exiting Because of Failed Unit Test" << endl;
    return 2;
  }

  programData = new ProgramData();

	glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1200,1000);
  window = glutCreateWindow("Zackary Misso - Fracture Evolver");
  // init the callbacks
  glutDisplayFunc(display);
  //glutMotionFunc(mouseMotion);
  GLUI_Master.set_glutKeyboardFunc(keyboard);
  GLUI_Master.set_glutMouseFunc(mouseClick);
  GLUI_Master.set_glutReshapeFunc(reshape);
  GLUI_Master.set_glutIdleFunc(mainLoop);
  // create the subwindow
  subwindow = GLUI_Master.create_glui_subwindow(window,GLUI_SUBWINDOW_LEFT);
  interface = new Interface(subwindow);
  renderSettings = new RenderSettings();

  createInterface();

  // STUFF FOR LATER //////////////
  //glEnable(GL_DEPTH_TEST);
  //glClearColor(0.0,0.0,0.0,1.0);
  //glMatrixMode(GL_PROJECTION);
  //gluPerspective(60,1,.1,100);
  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  //glEnable(GL_CULL_FACE);
  /////////////////////////////////
  cout << "Finished Initialization" << endl;
  if(argc > 2){
    for(int i=0;i<6;i++)
      Mutations::AddRandomVertex(programData->getCurrentFracture());
    DebugController::writeDebugState(programData->getCurrentFracture());
    return 0;
  }
  glutMainLoop();

  return 0;
}

void createInterface() {
  // Object Descripition Menu
  interface->objectDescriptionMenu = subwindow->add_rollout("Fracture Description",false);
  interface->edgesLabel = subwindow->add_statictext_to_panel(interface->objectDescriptionMenu,"Num Edges Will Go Here");
  interface->vertexsLabel = subwindow->add_statictext_to_panel(interface->objectDescriptionMenu,"Num Vertices Will Go Here");
  interface->facesLabel = subwindow->add_statictext_to_panel(interface->objectDescriptionMenu,"Num Faces Will Go Here");
  interface->saveFracture = subwindow->add_button_to_panel(interface->objectDescriptionMenu,"Save Fracture",1,cb_saveFracture);
  interface->loadFracture = subwindow->add_button_to_panel(interface->objectDescriptionMenu,"Load Fracture",1,cb_loadFracture);
  interface->clearFracture = subwindow->add_button_to_panel(interface->objectDescriptionMenu,"Clear Fracture",1,cb_clearFracture);
  // Edit Fracture Menu
  interface->editFractureMenu = subwindow->add_rollout("Edit Fracture",false);
  // Camera Menu
  interface->cameraMenu = subwindow->add_rollout("Camera",false);
  // Render Menu
  interface->renderMenu = subwindow->add_rollout("Render",false);
  interface->displayVertsButton = subwindow->add_button_to_panel(interface->renderMenu,"Verts On/Off",1,cb_vertsOnOff);
  interface->displayEdgesButton = subwindow->add_button_to_panel(interface->renderMenu,"Edges On/Off",1,cb_edgesOnOff);
  interface->displayFacesButton = subwindow->add_button_to_panel(interface->renderMenu,"Faces On/Off",1,cb_facesOnOff);
  interface->displayFaceTrimeshButton = subwindow->add_button_to_panel(interface->renderMenu,"Trimesh On/Off",1,cb_trimeshOnOff);
  // Evolution Menu
  interface->evolutionMenu = subwindow->add_rollout("Evolution",false);
  interface->randomMutation = subwindow->add_button_to_panel(interface->renderMenu,"Random Mutation",1,cb_randomMutation);
}

void display() {
  //cout << "RUNNING" << endl;
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLineWidth(.5);
  glBegin(GL_LINES);
  glColor4f(0.7f,0.7f,0.7f,0.5f);
  // Draw Grid for Debugging
  for(float i=-0.5f;i<0.5f;i+=0.1f) {
    glVertex2f(i,0.5);
    glVertex2f(i,-0.5);
    glVertex2f(0.5f,i);
    glVertex2f(-0.5f,i);
  }

  glEnd();
  glColor3f(0.0f,1.0f,0.0f);

  programData->getCurrentFracture()->draw(renderSettings);

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

bool unitTests() {
  if(Tests::intersectionTestOne()) {
    cout << "First Intersection Test Failed" << endl;
    return true;
  }
  if(Tests::intersectionTestTwo()) {
    cout << "Second Intersection Test Failed" << endl;
    return true;
  }
  if(Tests::intersectionTestThree()) {
    cout << "Third Intersection Test Failed" << endl;
    return true;
  }
  if(Tests::pointBetweenTest()) {
    cout << "Point Between Test Failed" << endl;
    return true;
  }
  //if(Tests::vertSortTest()) {
  //  cout << "Vert Sort Test Failed" << endl;
  //  return true;
  //}
  //if(Tests::vertReverseTest()) {
  //  cout << "Vert Reverse Test Failed" << endl;
  //  return true;
  //}
  //if(Tests::edgeIsOnTest()) {
  //  cout << "Edge Is On Test Failed" << endl;
  //  return true;
  //}
  //if(Tests::adjacentsTest()) {
  //  cout << "Adjacents Test Failed" << endl;
  //  return true;
  //}
  //if(Tests::detectIfConvexTest()) {
  //  cout << "Detect If Convex Failed" << endl;
  //  return true;
  //}
  //if(Tests::convexSplitTest()) {
  //  cout << "Convex Split Test Failed" << endl;
  //  return true;
  //}
  //if(Tests::concaveSplitTest()) {
  //  cout << "Concave Split Test Failed" << endl;
  //  return true;
  //}
  //if(Tests::trimeshCreationTest()) {
  //  cout << "Trimesh Creation Test Failed" << endl;
  //  return true;
  //}
  // implement more as needed
  return false;
}

///////////////////// CALLBACKS ////////////////////////

void cb_saveFracture(int id) {
  cout << "Saving still needs to be implemented" << endl;
  cout << "Also Writing Log" << endl;
  DebugController::writeDebugState(programData->getCurrentFracture());
}

void cb_loadFracture(int id) {
  cout << "Loading still needs to be implemented" << endl;
}

void cb_clearFracture(int id) {
  cout << "Clearing still needs to be implemented" << endl;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_vertsOnOff(int id) {
  renderSettings->setDisplayVerts(!renderSettings->getDisplayVerts());
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_edgesOnOff(int id) {
  renderSettings->setDisplayEdges(!renderSettings->getDisplayEdges());
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_facesOnOff(int id) {
  cout << "Displaying Faces Still needs to be implemented" << endl;
  renderSettings->setDisplayFaces(!renderSettings->getDisplayFaces());
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_trimeshOnOff(int id) {
  cout << "Displaying Face Trimesh Still needs to be implemented" << endl;
  renderSettings->setDisplayFaceTrimesh(!renderSettings->getDisplayFaceTrimesh());
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_randomMutation(int id) {
  //cout << endl;
  //cout << "Random Mutation Needs to be implemented" << endl;
  //DebugController::writeDebugState(programData->getCurrentFracture());
  //cout << endl;
  Mutations::AddRandomVertex(programData->getCurrentFracture());
  //cout << "NUM FACES :: " << programData->getCurrentFracture()->getFaces()->getSize() << endl;
  //cout << "NUM Edges :: " << programData->getCurrentFracture()->getEdges()->getSize() << endl;
  //cout << "NUM Verts :: " << programData->getCurrentFracture()->getVerts()->getSize() << endl;
  glutSetWindow(window);
  glutPostRedisplay();
}
