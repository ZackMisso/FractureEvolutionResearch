// this is a main class to be built on my laptop (No Graphics representation)

/*#include <iostream>
#include "fracture.h"
#include "array.h"
#include "interface.h"
#include "interfaceData.h"
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
void cb_selectFaces(int id);
void cb_selectEdges(int id);
void cb_selectVerts(int id);
void cb_selectNone(int id);
void cb_createVertex(int id);
void cb_createEdge(int id);

// Arguements
ProgramData* programData;
RenderSettings* renderSettings;
int window;


int mainMac(int argc,char** argv) {
  cout << "Beginning Initialization" << endl;
  DebugController::init();
  cout << "Running Unit Tests" << endl;
  if(unitTests()) {
    cout << "Exiting Because of Failed Unit Test" << endl;
    return 2;
  }

  programData = new ProgramData();
  renderSettings = new RenderSettings();
  createInterface();

  cout << "Finished Initialization" << endl;
  return 0;
}

void createInterface() { // TODO :: MOVE THIS TO INTEFACE CLASS
  // no
}

void display() {
  // none
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
  if(Tests::vertSortTest()) {
    cout << "Vert Sort Test Failed" << endl;
    return true;
  }
  if(Tests::vertReverseTest()) {
    cout << "Vert Reverse Test Failed" << endl;
    return true;
  }
  // Not Needed
  //if(Tests::edgeIsOnTest()) {
  //  cout << "Edge Is On Test Failed" << endl;
  //  return true;
  //}
  // I don't think I need adjacentcies
  //if(Tests::adjacentsTest()) {
  //  cout << "Adjacents Test Failed" << endl;
  //  return true;
  //}
  if(Tests::detectIfConvexTest()) {
    cout << "Detect If Convex Failed" << endl;
    return true;
  }
  if(Tests::convexSplitTest()) {
    cout << "Convex Split Test Failed" << endl;
    return true;
  }
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

void cb_selectFaces(int id) {
  cout << "Selecting Faces has yet to be implemented" << endl;
  // to be implemented
}

void cb_selectEdges(int id) {
  cout << "Selecting Edges has yet to be implemented" << endl;
  // to be implemented
}

void cb_selectVerts(int id) {
  cout << "Selecting Verts has yet to be implemented" << endl;
  // to be implemented
}

void cb_selectNone(int id) {
  cout << "Selecting None has yet to be implemented" << endl;
  // to be implemented
}

void cb_createVertex(int id) {
  cout << "Creating Vertex has Yet to be implemented" << endl;
  // to be implemented
}

void cb_createEdge(int id) {
  cout << "Creating Edge has Yet to be implemented" << endl;
  // to be implemented
}
*/
