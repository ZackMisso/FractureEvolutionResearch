// USE ON LINUX
#include <GL/glut.h>
// USE ON MAC
//#include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
//#include <GLUT/glut.h>

#include "globalInclude.h"
#include <iostream>
#include "src/include/GL/glui.h"
#include "geometry/fracture.h"
#include "dataStructures/array.h"
#include "ui/interface.h"
#include "ui/interfaceData.h"
#include "settings/programData.h"
#include "settings/renderSettings.h"
#include "settings/selectData.h"
#include "evolution/mutations.h"
#include "test/tests.h"
#include "test/debugController.h"
#include "evolution/individual.h"
#include "evolution/mutationFunctions/addRandomEdgeMutation.h"
#include "evolution/mutationFunctions/addRandomVertMutation.h"
#include "evolution/mutationFunctions/edgeCurveMutation.h"
#include "evolution/mutationFunctions/removeRandomEdgeMutation.h"
#include "evolution/mutationFunctions/removeRandomVertMutation.h"
#include "evolution/mutationFunctions/vertPositionMutation.h"

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
void cb_findVertex(int id);
void cb_findEdge(int id);
void cb_findFace(int id);
void cb_addRandomEdgeM(int id);
void cb_addRandomVertM(int id);
void cb_edgeCurveM(int id);
void cb_removeRandomEdgeM(int id);
void cb_removeRandomVertM(int id);
void cb_vertPositionM(int id);

// Arguements
GLUI* subwindow;
Interface* interface;
InterfaceData* interfaceData;
ProgramData* programData;
RenderSettings* renderSettings;
SelectData* selectData;
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
  selectData = new SelectData();

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
  // create required subsystems
  interfaceData = new InterfaceData();
  interface = new Interface(subwindow);
  renderSettings = new RenderSettings();
  //renderSettings->setInterfaceRef(interfaceData);
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
  //if(argc > 2){
  //  for(int i=0;i<6;i++)
  //    Mutations::AddRandomVertex(programData->getCurrentFracture());
  //  DebugController::writeDebugState(programData->getCurrentFracture());
  //  return 0;
  //}
  glutMainLoop();

  return 0;
}

void createInterface() { // TODO :: MOVE THIS TO INTEFACE CLASS
  // Object Descripition Menu
  interface->objectDescriptionMenu = subwindow->add_rollout("Fracture Description",false);
  interface->edgesLabel = subwindow->add_statictext_to_panel(interface->objectDescriptionMenu,"Num Edges Will Go Here");
  interface->vertexsLabel = subwindow->add_statictext_to_panel(interface->objectDescriptionMenu,"Num Vertices Will Go Here");
  interface->facesLabel = subwindow->add_statictext_to_panel(interface->objectDescriptionMenu,"Num Faces Will Go Here");
  interface->saveFracture = subwindow->add_button_to_panel(interface->objectDescriptionMenu,"Save Fracture",1,cb_saveFracture);
  interface->loadFracture = subwindow->add_button_to_panel(interface->objectDescriptionMenu,"Load Fracture",1,cb_loadFracture);
  interface->clearFracture = subwindow->add_button_to_panel(interface->objectDescriptionMenu,"Clear Fracture",1,cb_clearFracture);
  // Settings Menu
  interface->interfaceMenu = subwindow->add_rollout("Settings",false);
  interface->selectFacesButton = subwindow->add_button_to_panel(interface->interfaceMenu,"Select Faces",1,cb_selectFaces);
  interface->selectEdgesButton = subwindow->add_button_to_panel(interface->interfaceMenu,"Select Edges",1,cb_selectEdges);
  interface->selectVertsButton = subwindow->add_button_to_panel(interface->interfaceMenu,"Select Verts",1,cb_selectVerts);
  interface->selectNoneButton = subwindow->add_button_to_panel(interface->interfaceMenu,"Select None",1,cb_selectNone);
  // Current Selection Menu
  interface->selectedMenu = subwindow->add_rollout("Current Selection",false);
  interface->faceSelectedMenu = subwindow->add_rollout_to_panel(interface->selectedMenu,"Selected Face",false);
  interface->faceID = subwindow->add_statictext_to_panel(interface->faceSelectedMenu,"not selected");
  interface->edgeSelectedMenu = subwindow->add_rollout_to_panel(interface->selectedMenu,"Selected Edge",false);
  interface->edgeID = subwindow->add_statictext_to_panel(interface->faceSelectedMenu,"not selected");
  interface->vertSelectedMenu = subwindow->add_rollout_to_panel(interface->selectedMenu,"Selected Vertex",false);
  interface->vertID = subwindow->add_statictext_to_panel(interface->faceSelectedMenu,"not selected");
  // Find Menu
  interface->findMenu = subwindow->add_rollout("Find Object",false);
  interface->findVertMenu = subwindow->add_rollout_to_panel(interface->findMenu,"Find Vertex",false);
  interface->findVertID = subwindow->add_edittext_to_panel(interface->findVertMenu,"Vertex ID",GLUI_EDITTEXT_INT);
  interface->findVertButton = subwindow->add_button_to_panel(interface->findVertMenu,"Find Vertex",1,cb_findVertex);
  interface->findEdgeMenu = subwindow->add_rollout_to_panel(interface->findMenu,"Find Edge",false);
  interface->findVertID = subwindow->add_edittext_to_panel(interface->findEdgeMenu,"Edge ID",GLUI_EDITTEXT_INT);
  interface->findVertButton = subwindow->add_button_to_panel(interface->findEdgeMenu,"Find Edge",1,cb_findEdge);
  interface->findFaceMenu = subwindow->add_rollout_to_panel(interface->findMenu,"Find Face",false);
  interface->findVertID = subwindow->add_edittext_to_panel(interface->findFaceMenu,"Face ID",GLUI_EDITTEXT_INT);
  interface->findVertButton = subwindow->add_button_to_panel(interface->findFaceMenu,"Find Face",1,cb_findFace);
  // Edit Fracture Menu
  interface->editFractureMenu = subwindow->add_rollout("Edit Fracture",false);
  interface->addVertexMenu = subwindow->add_rollout_to_panel(interface->editFractureMenu,"Add Vertex",false);
  interface->vertexXCoord = subwindow->add_edittext_to_panel(interface->addVertexMenu,"Add Vertex X",GLUI_EDITTEXT_FLOAT);
  interface->vertexYCoord = subwindow->add_edittext_to_panel(interface->addVertexMenu,"Add Vertex Y",GLUI_EDITTEXT_FLOAT);
  interface->addVertexButton = subwindow->add_button_to_panel(interface->addVertexMenu,"Create Vertex",1,cb_createVertex);
  interface->addEdgeMenu = subwindow->add_rollout_to_panel(interface->editFractureMenu,"Add Edge",false);
  //interface->vertexOneID = subwindow->add_rollout_to_panel
  // KEEP IMPLEMENTING

  interface->addEdgeButton = subwindow->add_button_to_panel(interface->addEdgeMenu,"Create Edge",1,cb_createEdge);
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
  interface->randomMutation = subwindow->add_button_to_panel(interface->renderMenu,"Add Random Edge",1,cb_addRandomEdgeM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->renderMenu,"Add Random Vert",1,cb_addRandomVertM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->renderMenu,"Edge Curve",1,cb_edgeCurveM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->renderMenu,"Remove Random Edge",1,cb_removeRandomEdgeM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->renderMenu,"Remove Random Vert",1,cb_removeRandomVertM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->renderMenu,"Vert Position",1,cb_vertPositionM);
}

void display() {
  //cout << "RUNNING" << endl;
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLineWidth(.5);
  glBegin(GL_LINES);
  glColor4f(0.7f,0.7f,0.7f,0.5f);
  // Draw Grid for Debugging
  for(real i=-0.5f;i<0.5f;i+=0.1f) {
    glVertex2f(i,0.5);
    glVertex2f(i,-0.5);
    glVertex2f(0.5f,i);
    glVertex2f(-0.5f,i);
  }

  glEnd();
  glColor3f(0.0f,1.0f,0.0f);

  programData->getCurrentFracture()->draw(renderSettings,interfaceData);

  glColor3f(1.0f,1.0f,1.0f);
  if(selectData->getSelectedVert()) {
    glBegin(GL_POINTS);
    selectData->getSelectedVert()->draw();
    glEnd();
  }
  if(selectData->getSelectedEdge()) {
    glBegin(GL_LINES);
    selectData->getSelectedEdge()->draw();
    glEnd();
  }
  if(selectData->getSelectedFace()) {
    // NEED TO IMPLEMENT FACE DRAW
    //glBegin(GL_TRIANGLES);
    //selectData->getSelectedFace()->draw();
    //glEnd();
  }

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
  Vertex* newVert = programData->getCurrentFracture()->giveVertexID(new Vertex(interface->vertexXCoord->get_float_val(),interface->vertexYCoord->get_float_val()));
  programData->getCurrentFracture()->getVerts()->add(newVert);
}

void cb_createEdge(int id) {
  cout << "Creating Edge has Yet to be implemented" << endl;
  Array<Vertex*>* verts = programData->getCurrentFracture()->getVerts();
  Vertex* one = 0x0;
  Vertex* two = 0x0;
  for(int i=0;i<verts->getSize();i++) {
    if(verts->get(i)->getID() == interface->vertexOneID->get_int_val())
      one = verts->get(i);
    if(verts->get(i)->getID() == interface->vertexTwoID->get_int_val())
      two = verts->get(i);
  }
  if(one && two) {
    Edge* edge = programData->getCurrentFracture()->giveEdgeID(new Edge(one->getLocation(),two->getLocation(),one->getID(),two->getID()));
    programData->getCurrentFracture()->getEdges()->add(edge);
  }
}

void cb_findVertex(int id) {
  int vertID = interface->findVertID->get_int_val();
  Array<Vertex*>* verts = programData->getCurrentFracture()->getVerts();
  selectData->setSelectedVert(0x0);
  selectData->setSelectedEdge(0x0);
  selectData->setSelectedFace(0x0);
  for(int i=0;i<verts->getSize();i++)
    if(verts->get(i)->getID() == vertID)
      selectData->setSelectedVert(verts->get(i));
}

void cb_findEdge(int id) {
  int edgeID = interface->findEdgeID->get_int_val();
  Array<Edge*>* edges = programData->getCurrentFracture()->getEdges();
  selectData->setSelectedVert(0x0);
  selectData->setSelectedEdge(0x0);
  selectData->setSelectedFace(0x0);
  for(int i=0;i<edges->getSize();i++)
    if(edges->get(i)->getID() == edgeID)
      selectData->setSelectedEdge(edges->get(i));
}

void cb_findFace(int id) {
  int faceID = interface->findFaceID->get_int_val();
  Array<Face*>* faces = programData->getCurrentFracture()->getFaces();
  selectData->setSelectedVert(0x0);
  selectData->setSelectedEdge(0x0);
  selectData->setSelectedFace(0x0);
  for(int i=0;i<faces->getSize();i++)
    if(faces->get(i)->getID() == faceID)
      selectData->setSelectedFace(faces->get(i));
}

void cb_addRandomEdgeM(int id) {
  AddRandomEdgeMutation* mutate = new AddRandomEdgeMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
}

void cb_addRandomVertM(int id) {
  AddRandomVertMutation* mutate = new AddRandomVertMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
}

void cb_edgeCurveM(int id) {
  EdgeCurveMutation* mutate = new EdgeCurveMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
}

void cb_removeRandomEdgeM(int id) {
  RemoveRandomEdgeMutation* mutate = new RemoveRandomEdgeMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
}

void cb_removeRandomVertM(int id) {
  RemoveRandomVertMutation* mutate = new RemoveRandomVertMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
}

void cb_vertPositionM(int id) {
  VertPositionMutation* mutate = new VertPositionMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
}
