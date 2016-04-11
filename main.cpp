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
#include "settings/evolutionSettings.h"
#include "evolution/mutations.h"
#include "test/tests.h"
#include "test/debugController.h"
#include "io/fileIOController.h"
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
void cb_printAllVertIDs(int id);
void cb_printAllEdgeIDs(int id);
void cb_printAllFaceIDs(int id);
void cb_printFaceEdges(int id);
void cb_printFaceVerts(int id);
void cb_printFaceClockwisePoints(int id);
void cb_printFaceInteriorAngles(int id);

// display callbacks
void cb_displayTriangulationOne(int id);
void cb_displayTriangulationTwo(int id);
void cb_displayVertAddConvexOne(int id);
void cb_displayVertAddConvexTwo(int id);
void cb_displayVertAddConvexThree(int id);
void cb_displayVertAddConcaveOne(int id);
void cb_displayVertAddConcaveTwo(int id);
void cb_displayVertAddConcaveThree(int id);
void cb_displayVertAddConcaveFour(int id);
void cb_displayVertAddConcaveFive(int id);
void cb_displayVertMoveConvexOne(int id);
void cb_displayVertMoveConvexTwo(int id);
void cb_displayVertMoveConvexThree(int id);
void cb_displayVertMoveConvexFour(int id);
void cb_displayVertMoveConcaveOne(int id);
void cb_displayVertMoveConcaveTwo(int id);
void cb_displayVertMoveConcaveThree(int id);
void cb_displayVertMoveConcaveFour(int id);
void cb_displayVertMoveConcaveFive(int id);
// display
void displayTriangulationOne();
void displayTriangulationTwo();
void displayVertAddConvexOne();
void displayVertAddConvexTwo();
void displayVertAddConvexThree();
void displayVertAddConcaveOne();
void displayVertAddConcaveTwo();
void displayVertAddConcaveThree();
void displayVertAddConcaveFour();
void displayVertAddConcaveFive();
void displayVertMoveConvexOne();
void displayVertMoveConvexTwo();
void displayVertMoveConvexThree();
void displayVertMoveConvexFour();
void displayVertMoveConcaveOne();
void displayVertMoveConcaveTwo();
void displayVertMoveConcaveThree();
void displayVertMoveConcaveFour();
void displayVertMoveConcaveFive();

// Arguements
GLUI* subwindow;
Interface* interface;
InterfaceData* interfaceData;
ProgramData* programData;
RenderSettings* renderSettings;
SelectData* selectData;
FileIOController* fileIO;
int window;


int main(int argc,char** argv) {
  cout << "Beginning Initialization" << endl;
  DebugController::init();
  cout << "Running Unit Tests" << endl;
  EvolutionSettings::initialize();
  if(unitTests()) {
    cout << "Exiting Because of Failed Unit Test" << endl;
    return 2;
  }

  programData = new ProgramData();
  selectData = new SelectData();
  fileIO = new FileIOController();

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
  //interface->faceID = subwindow->add_statictext_to_panel(interface->faceSelectedMenu,"not selected");
  interface->printFaceEdges = subwindow->add_button_to_panel(interface->faceSelectedMenu,"Face Edges",1,cb_printFaceEdges);
  interface->printFaceVerts = subwindow->add_button_to_panel(interface->faceSelectedMenu,"Face Verts",1,cb_printFaceVerts);
  interface->printClockwisePoints = subwindow->add_button_to_panel(interface->faceSelectedMenu,"Clockwise Points",1,cb_printFaceClockwisePoints);
  interface->printFaceAngles = subwindow->add_button_to_panel(interface->faceSelectedMenu,"Print Interior Angles",1,cb_printFaceInteriorAngles);
  interface->edgeSelectedMenu = subwindow->add_rollout_to_panel(interface->selectedMenu,"Selected Edge",false);
  //interface->edgeID = subwindow->add_statictext_to_panel(interface->faceSelectedMenu,"not selected");
  interface->vertSelectedMenu = subwindow->add_rollout_to_panel(interface->selectedMenu,"Selected Vertex",false);
  //interface->vertID = subwindow->add_statictext_to_panel(interface->faceSelectedMenu,"not selected");
  // Find Menu
  interface->findMenu = subwindow->add_rollout("Find Object",false);
  interface->printAllVertIDs = subwindow->add_button_to_panel(interface->findMenu,"Print Vertex IDs",1,cb_printAllVertIDs);
  interface->printAllEdgeIDs = subwindow->add_button_to_panel(interface->findMenu,"Print Edge IDs",1,cb_printAllEdgeIDs);
  interface->printAllFaceIDs = subwindow->add_button_to_panel(interface->findMenu,"Print Face IDs",1,cb_printAllFaceIDs);
  interface->findVertMenu = subwindow->add_rollout_to_panel(interface->findMenu,"Find Vertex",false);
  interface->findVertID = subwindow->add_edittext_to_panel(interface->findVertMenu,"Vertex ID",GLUI_EDITTEXT_INT);
  interface->findVertButton = subwindow->add_button_to_panel(interface->findVertMenu,"Find Vertex",1,cb_findVertex);
  interface->findEdgeMenu = subwindow->add_rollout_to_panel(interface->findMenu,"Find Edge",false);
  interface->findEdgeID = subwindow->add_edittext_to_panel(interface->findEdgeMenu,"Edge ID",GLUI_EDITTEXT_INT);
  interface->findEdgeButton = subwindow->add_button_to_panel(interface->findEdgeMenu,"Find Edge",1,cb_findEdge);
  interface->findFaceMenu = subwindow->add_rollout_to_panel(interface->findMenu,"Find Face",false);
  interface->findFaceID = subwindow->add_edittext_to_panel(interface->findFaceMenu,"Face ID",GLUI_EDITTEXT_INT);
  interface->findFaceButton = subwindow->add_button_to_panel(interface->findFaceMenu,"Find Face",1,cb_findFace);
  // Edit Fracture Menu
  interface->editFractureMenu = subwindow->add_rollout("Edit Fracture",false);
  interface->addVertexMenu = subwindow->add_rollout_to_panel(interface->editFractureMenu,"Add Vertex",false);
  interface->vertexXCoord = subwindow->add_edittext_to_panel(interface->addVertexMenu,"Add Vertex X",GLUI_EDITTEXT_FLOAT);
  interface->vertexYCoord = subwindow->add_edittext_to_panel(interface->addVertexMenu,"Add Vertex Y",GLUI_EDITTEXT_FLOAT);
  interface->addVertexButton = subwindow->add_button_to_panel(interface->addVertexMenu,"Create Vertex",1,cb_createVertex);
  interface->addEdgeMenu = subwindow->add_rollout_to_panel(interface->editFractureMenu,"Add Edge",false);
  interface->vertexOneID = subwindow->add_edittext_to_panel(interface->addEdgeMenu,"Vertex One ID",GLUI_EDITTEXT_INT);
  interface->vertexTwoID = subwindow->add_edittext_to_panel(interface->addEdgeMenu,"Vertex Two ID",GLUI_EDITTEXT_INT);
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
  interface->randomMutation = subwindow->add_button_to_panel(interface->evolutionMenu,"Random Mutation",1,cb_randomMutation);
  interface->randomMutation = subwindow->add_button_to_panel(interface->evolutionMenu,"Add Random Edge",1,cb_addRandomEdgeM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->evolutionMenu,"Add Random Vert",1,cb_addRandomVertM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->evolutionMenu,"Edge Curve",1,cb_edgeCurveM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->evolutionMenu,"Remove Random Edge",1,cb_removeRandomEdgeM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->evolutionMenu,"Remove Random Vert",1,cb_removeRandomVertM);
  interface->randomMutation = subwindow->add_button_to_panel(interface->evolutionMenu,"Vert Position",1,cb_vertPositionM);
  // Demo Menu
  interface->demoMenu = subwindow->add_rollout("Demo",false);
  interface->triangulationOne = subwindow->add_button_to_panel(interface->demoMenu,"Triangulation One",1,cb_displayTriangulationOne);
  interface->triangulationTwo = subwindow->add_button_to_panel(interface->demoMenu,"Triangulation Two",1,cb_displayTriangulationTwo);
  interface->vertAddConvexOne = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Convex One",1,cb_displayVertAddConvexOne);
  interface->vertAddConvexTwo = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Convex Two",1,cb_displayVertAddConvexTwo);
  interface->vertAddConvexThree = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Convex Three",1,cb_displayVertAddConvexThree);
  interface->vertAddConcaveOne = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Concave One",1,cb_displayVertAddConcaveOne);
  interface->vertAddConcaveTwo = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Concave Two",1,cb_displayVertAddConcaveTwo);
  interface->vertAddConcaveThree = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Concave Three",1,cb_displayVertAddConcaveThree);
  interface->vertAddConcaveFour = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Concave Four",1,cb_displayVertAddConcaveFour);
  interface->vertAddConcaveFive = subwindow->add_button_to_panel(interface->demoMenu,"Vert Add Concave Five",1,cb_displayVertAddConcaveFive);
  interface->vertMoveConvexOne = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Convex One",1,cb_displayVertMoveConvexOne);
  interface->vertMoveConvexTwo = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Convex Two",1,cb_displayVertMoveConvexTwo);
  interface->vertMoveConvexThree = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Convex Three",1,cb_displayVertMoveConvexThree);
  interface->vertMoveConvexFour = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Convex Four",1,cb_displayVertMoveConvexFour);
  interface->vertMoveConcaveOne = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Concave One",1,cb_displayVertMoveConcaveOne);
  interface->vertMoveConcaveTwo = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Concave Two",1,cb_displayVertMoveConcaveTwo);
  interface->vertMoveConcaveThree = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Concave Three",1,cb_displayVertMoveConcaveThree);
  interface->vertMoveConcaveFour = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Concave Four",1,cb_displayVertMoveConcaveFour);
  interface->vertMoveConcaveFive = subwindow->add_button_to_panel(interface->demoMenu,"Vert Move Concave Five",1,cb_displayVertMoveConcaveFive);
}

void display() {
  //cout << "RUNNING" << endl;
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLineWidth(.5);
  glBegin(GL_LINES);
  glColor4f(0.7f,0.7f,0.7f,0.5f);
  // Draw Grid for Debugging
  for(real i=-0.5f;i<=0.5f;i+=0.1f) {
    glVertex2f(i,0.5);
    glVertex2f(i,-0.5);
    glVertex2f(0.5f,i);
    glVertex2f(-0.5f,i);
  }

  glEnd();

  if(renderSettings->getTriangulationOne())
    displayTriangulationOne();
  else if(renderSettings->getTriangulationTwo())
    displayTriangulationTwo();
  else if(renderSettings->getVertAddConvexOne())
    displayVertAddConvexOne();
  else if(renderSettings->getVertAddConvexTwo())
    displayVertAddConvexTwo();
  else if(renderSettings->getVertAddConvexThree())
    displayVertAddConvexThree();
  else if(renderSettings->getVertAddConcaveOne())
    displayVertAddConcaveOne();
  else if(renderSettings->getVertAddConcaveTwo())
    displayVertAddConcaveTwo();
  else if(renderSettings->getVertAddConcaveThree())
    displayVertAddConcaveThree();
  else if(renderSettings->getVertAddConcaveFour())
    displayVertAddConcaveFour();
  else if(renderSettings->getVertAddConcaveFive())
    displayVertAddConcaveFive();
  else if(renderSettings->getVertMoveConvexOne())
    displayVertMoveConvexOne();
  else if(renderSettings->getVertMoveConvexTwo())
    displayVertMoveConvexTwo();
  else if(renderSettings->getVertMoveConvexThree())
    displayVertMoveConvexThree();
  else if(renderSettings->getVertMoveConvexFour())
    displayVertMoveConvexFour();
  else if(renderSettings->getVertMoveConcaveOne())
    displayVertMoveConcaveOne();
  else if(renderSettings->getVertMoveConcaveTwo())
    displayVertMoveConcaveTwo();
  else if(renderSettings->getVertMoveConcaveThree())
    displayVertMoveConcaveThree();
  else if(renderSettings->getVertMoveConcaveFour())
    displayVertMoveConcaveFour();
  else if(renderSettings->getVertMoveConcaveFive())
    displayVertMoveConcaveFive();
  else {
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
      glBegin(GL_POINTS);
      Array<Vertex*>* verts = selectData->getSelectedFace()->getVerts();
      for(int i=0;i<verts->getSize();i++)
        verts->get(i)->draw();
      glEnd();
      glBegin(GL_LINES);
      Array<Edge*>* edges = selectData->getSelectedFace()->getEdges();
      for(int i=0;i<edges->getSize();i++)
        edges->get(i)->draw();
      glEnd();
    }
  }

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
  if(Tests::angleTests()) {
    cout << "Angle Test Failed" << endl;
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

  //Mutations::AddRandomVertex(programData->getCurrentFracture());

  //cout << "NUM FACES :: " << programData->getCurrentFracture()->getFaces()->getSize() << endl;
  //cout << "NUM Edges :: " << programData->getCurrentFracture()->getEdges()->getSize() << endl;
  //cout << "NUM Verts :: " << programData->getCurrentFracture()->getVerts()->getSize() << endl;

  // Debug Code ::
  Fracture* fracture = programData->getCurrentFracture();
  Array<Face*>* faces = fracture->getFaces();
  for(int i=0;i<faces->getSize();i++) {
    DebugController::writeFaceState(faces->get(i));
    cout << endl;
    for(int j=0;j<faces->get(i)->getVerts()->getSize();j++)
      DebugController::writeVertState(faces->get(i)->getVerts()->get(j));
    cout << endl;
    for(int j=0;j<faces->get(i)->getEdges()->getSize();j++)
      DebugController::writeEdgeState(faces->get(i)->getEdges()->get(j));
    cout << endl;
  }


  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_selectFaces(int id) {
  cout << "Selecting Faces has yet to be implemented" << endl;
  // to be implemented
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_selectEdges(int id) {
  cout << "Selecting Edges has yet to be implemented" << endl;
  // to be implemented
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_selectVerts(int id) {
  cout << "Selecting Verts has yet to be implemented" << endl;
  // to be implemented
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_selectNone(int id) {
  cout << "Selecting None has yet to be implemented" << endl;
  // to be implemented
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_createVertex(int id) {
  //cout << "Creating Vertex has Yet to be implemented" << endl;
  Vertex* newVert = programData->getCurrentFracture()->giveVertexID(new Vertex(interface->vertexXCoord->get_float_val(),interface->vertexYCoord->get_float_val()));
  programData->getCurrentFracture()->getVerts()->add(newVert);
  glutSetWindow(window);
  glutPostRedisplay();
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
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_findVertex(int id) {
  int vertID = interface->findVertID->get_int_val();
  const char* text = interface->findVertID->get_text();
  cout << "Vert ID :: " << vertID << " :: " << text << endl;
  Array<Vertex*>* verts = programData->getCurrentFracture()->getVerts();
  selectData->setSelectedVert(0x0);
  selectData->setSelectedEdge(0x0);
  selectData->setSelectedFace(0x0);
  for(int i=0;i<verts->getSize();i++)
    if(verts->get(i)->getID() == vertID) {
      //cout << "Found Selected" << endl;
      selectData->setSelectedVert(verts->get(i));
      Vertex* vert = verts->get(i);
      cout << "Edges for Vert: ";
      for(int i=0;i<vert->getEdges()->getSize();i++)
        cout << vert->getEdges()->get(i)->getID() << " ";
      cout << endl;
    }
  //cout << "IN HERE" << endl;
  glutSetWindow(window);
  glutPostRedisplay();
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
  glutSetWindow(window);
  glutPostRedisplay();
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
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_addRandomEdgeM(int id) {
  AddRandomEdgeMutation* mutate = new AddRandomEdgeMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_addRandomVertM(int id) {
  AddRandomVertMutation* mutate = new AddRandomVertMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
  Fracture* fracture = programData->getCurrentFracture();
  cout << "Num Faces: " << fracture->getFaces()->getSize() << endl;
  //fracture->recount();
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_edgeCurveM(int id) {
  EdgeCurveMutation* mutate = new EdgeCurveMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_removeRandomEdgeM(int id) {
  RemoveRandomEdgeMutation* mutate = new RemoveRandomEdgeMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_removeRandomVertM(int id) {
  RemoveRandomVertMutation* mutate = new RemoveRandomVertMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_vertPositionM(int id) {
  VertPositionMutation* mutate = new VertPositionMutation();
  mutate->mutate(programData->getCurrentFracture());
  delete mutate;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_printAllVertIDs(int id) {
  Array<Vertex*>* verts = programData->getCurrentFracture()->getVerts();
  cout << "Vertex IDs :: " << endl;
  for(int i=0;i<verts->getSize();i++) {
    cout << "ID :: " << verts->get(i)->getID();
    cout << "In Faces : ";
    for(int j=0;j<verts->get(i)->getFaceIDs()->getSize();j++)
      cout << verts->get(i)->getFaceIDs()->get(j).val << " ";
    cout << endl;
  }
  cout << endl;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_printAllEdgeIDs(int id) {
  Array<Edge*>* edges = programData->getCurrentFracture()->getEdges();
  cout << "Edge IDs :: " << endl;
  for(int i=0;i<edges->getSize();i++) {
    cout << "ID :: " << edges->get(i)->getID();
    cout << "In Faces : ";
    for(int j=0;j<edges->get(i)->getFaceIDs()->getSize();j++)
      cout << edges->get(i)->getFaceIDs()->get(j).val << " ";
    cout << endl;
  }
  cout << endl;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_printAllFaceIDs(int id) {
  Array<Face*>* faces = programData->getCurrentFracture()->getFaces();
  cout << "Face IDs :: " << endl;
  for(int i=0;i<faces->getSize();i++)
    cout << "ID :: " << faces->get(i)->getID() << endl;
  cout << endl;
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_printFaceEdges(int id) {
  if(selectData->getSelectedFace()) {
    Face* face = selectData->getSelectedFace();
    for(int i=0;i<face->getEdges()->getSize();i++)
      DebugController::writeEdgeState(face->getEdges()->get(i));
  }
  else
    cout << "Please Select a Face First" << endl;
}

void cb_printFaceVerts(int id) {
  if(selectData->getSelectedFace()) {
    Face* face = selectData->getSelectedFace();
    for(int i=0;i<face->getVerts()->getSize();i++)
      DebugController::writeVertState(face->getVerts()->get(i));
  }
  else
    cout << "Please Select a Face First" << endl;
}

void cb_printFaceClockwisePoints(int id) {
  if(selectData->getSelectedFace()) {
    Face* face = selectData->getSelectedFace();
    Array<Point2>* points = face->sortPointsByPath();
    if(face->isClockwise(points))
      points = face->reversePath(points);
    for(int i=0;i<points->getSize();i++)
      DebugController::writePointState(points->get(i));
    points->clear();
    delete points;
  }
  else
    cout << "Please Select a Face First" << endl;
}

void cb_printFaceInteriorAngles(int id) {
  if(selectData->getSelectedFace()) {
    Face* face = selectData->getSelectedFace();
    Array<Point2>* points = face->sortPointsByPath();
    if(face->isClockwise(points))
      points = face->reversePath(points);
    Array<Edge*>* tmpEdges = new Array<Edge*>();
    for(int i=1;i<points->getSize();i++)
      tmpEdges->add(new Edge(points->get(i),points->get(i-1)));
    tmpEdges->add(new Edge(points->get(0),points->get(points->getSize()-1)));
    // write the edges to make sure they are in the right order
    cout << "Temporary Edges: " << endl;
    for(int i=0;i<tmpEdges->getSize();i++)
      DebugController::writeEdgeState(tmpEdges->get(i));
    cout << "Interior Angles: " << endl;
    for(int i=1;i<tmpEdges->getSize();i++)
      cout << "Edge: " << i << " and: " << i-1 << " Angle: " << tmpEdges->get(i)->interiorAngle(tmpEdges->get(i-1)) / PI * 180 << endl;
    cout << "Last and first Edge: " << tmpEdges->get(tmpEdges->getSize()-1)->interiorAngle(tmpEdges->get(0)) / PI * 180 << endl;
    while(tmpEdges->getSize())
      delete tmpEdges->removeLast();
    delete tmpEdges;
    points->clear();
    delete points;
  }
  else
    cout << "Please Select a Face First" << endl;
}

// display callbacks
void cb_displayTriangulationOne(int id) {
  renderSettings->resetDisplay();
  renderSettings->setTriangulationOne(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayTriangulationTwo(int id) {
  renderSettings->resetDisplay();
  renderSettings->setTriangulationTwo(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConvexOne(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConvexOne(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConvexTwo(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConvexTwo(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConvexThree(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConvexThree(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConcaveOne(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConcaveOne(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConcaveTwo(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConcaveTwo(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConcaveThree(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConcaveThree(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConcaveFour(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConcaveFour(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertAddConcaveFive(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertAddConcaveFive(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConvexOne(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConvexOne(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConvexTwo(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConvexTwo(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConvexThree(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConvexThree(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConvexFour(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConvexFour(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConcaveOne(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConcaveOne(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConcaveTwo(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConcaveTwo(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConcaveThree(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConcaveThree(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConcaveFour(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConcaveFour(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

void cb_displayVertMoveConcaveFive(int id) {
  renderSettings->resetDisplay();
  renderSettings->setVertMoveConcaveFive(true);
  glutSetWindow(window);
  glutPostRedisplay();
}

// display
void displayTriangulationOne() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,0);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,0);
  glVertex2f(0,0);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glEnd();
}

void displayTriangulationTwo() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,0);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  //glBegin(GL_LINES);
  //glVertex2f(-0.4,0.15);
  //glVertex2f(-0.3,-0.3);
  //glVertex2f(-0.3,-0.3);
  //glVertex2f(0,0);
  //glVertex2f(0,0);
  //glVertex2f(0.3,-0.25);
  //glVertex2f(0.3,-0.25);
  //glVertex2f(0.4,0.2);
  //glVertex2f(0.4,0.2);
  //glVertex2f(0.2,0.3);
  //glVertex2f(0.2,0.3);
  //glVertex2f(-0.4,0.15);
  //glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*0.5);
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,0);
  glVertex2f(0,0);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.4,0.15);
  glVertex2f(0,0);
  glVertex2f(0.2,0.3);
  glVertex2f(0,0);
  glVertex2f(0.4,0.2);
  glVertex2f(0,0);
  glEnd();
}

void displayVertAddConvexOne() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glEnd();
}

void displayVertAddConvexTwo() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.03,-0.03);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glEnd();
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_LINES);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glEnd();
}

void displayVertAddConvexThree() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glEnd();
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POINTS);
  glVertex2f(0.03,-0.03);
  glVertex2f(-0.1,0.225);
  glVertex2f(0.15,-0.3);
  glEnd();
  glBegin(GL_LINES);
  glVertex2f(0.03,-0.03);
  glVertex2f(-0.1,0.225);
  glVertex2f(0.03,-0.03);
  glVertex2f(0.15,-0.3);
  glEnd();
}

void displayVertAddConcaveOne() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(0.0,0.4);
  glVertex2f(-0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.2);
  glEnd();
}

void displayVertAddConcaveTwo() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glEnd();
  glColor3f(1.0f,0.0f,0.0f);
  glLineWidth((real)renderSettings->getEdgeSize()*1.0);
  glBegin(GL_LINES);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(0.0,0.4);
  glVertex2f(-0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.4);
  glEnd();
  glColor3f(1.0f,1.0f,1.0f);
  glLineWidth((real)renderSettings->getEdgeSize()*0.3);
  glBegin(GL_LINES);
  glVertex2f(0.0,0.4);
  glVertex2f(-0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.4);
  glEnd();
}

void displayVertAddConcaveThree() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(0.0,0.4);
  glVertex2f(-0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.2);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(-0.1,0.05);
  glEnd();
  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_LINES);
  glVertex2f(0.0,0.4);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.2);
  glEnd();
}

void displayVertAddConcaveFour() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(0.0,0.4);
  glVertex2f(-0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.2);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(-0.1,0.05);
  glVertex2f(-0.2,0.0);
  glEnd();
  glColor3f(1.0f,0.0f,1.0f);
  glBegin(GL_POINTS);
  glVertex2f(0.1,-0.03);
  glEnd();
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_LINES);
  glVertex2f(-0.1,0.05);
  glVertex2f(-0.2,0.0);
  glEnd();
  glColor3f(1.0f,0.0f,1.0f);
  glBegin(GL_LINES);
  glVertex2f(-0.1,0.05);
  glVertex2f(0.1,-0.03);
  glEnd();
}

void displayVertAddConcaveFive() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(0.0,0.4);
  glVertex2f(0.3,-0.2);
  glVertex2f(0.0,0.4);
  glVertex2f(-0.3,-0.2);
  glVertex2f(-0.3,-0.2);
  glVertex2f(0.0,0.05);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.2);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(-0.1,0.05);
  glVertex2f(-0.2,0.0);
  glVertex2f(-0.032,0.022);
  glEnd();
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_LINES);
  glVertex2f(-0.1,0.05);
  glVertex2f(-0.2,0.0);
  glVertex2f(-0.1,0.05);
  glVertex2f(-0.032,0.022);
  glEnd();
}

void displayVertMoveConvexOne() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(0.0,-0.0);
  glVertex2f(-0.1,0.225);
  glVertex2f(0.15,-0.3);
  glEnd();
  glBegin(GL_LINES);
  glVertex2f(0.0,-0.0);
  glVertex2f(-0.1,0.225);
  glVertex2f(0.0,-0.0);
  glVertex2f(0.15,-0.3);
  glEnd();
}

void displayVertMoveConvexTwo() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.0,-0.0);
  glVertex2f(-0.1,0.225);
  glVertex2f(0.15,-0.3);
  glEnd();
  glColor3f(1.0f,0.0f,0.0f);
  glLineWidth((real)renderSettings->getEdgeSize()*0.6);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.4,0.15);
  glVertex2f(0.0,0.0);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.0,0.0);
  glVertex2f(0,-.35);
  glVertex2f(0.0,0.0);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.0,0.0);
  glVertex2f(0.4,0.2);
  glVertex2f(0.0,0.0);
  glVertex2f(0.2,0.3);
  glVertex2f(0.0,0.0);
  glEnd();
}

void displayVertMoveConvexThree() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.08,-0.06);
  glVertex2f(-0.1,0.225);
  glVertex2f(0.15,-0.3);
  glEnd();
  glColor3f(1.0f,0.0f,0.0f);
  glLineWidth((real)renderSettings->getEdgeSize()*0.6);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.08,-0.06);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.08,-0.06);
  glVertex2f(0,-.35);
  glVertex2f(-0.08,-0.06);
  glVertex2f(0.3,-0.25);
  glVertex2f(-0.08,-0.06);
  glVertex2f(0.4,0.2);
  glVertex2f(-0.08,-0.06);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.08,-0.06);
  glEnd();
}

void displayVertMoveConvexFour() {
  glPointSize((real)renderSettings->getVertSize());
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_POINTS);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.4,0.15);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0,-.35);
  glVertex2f(0,-.35);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.3,-0.25);
  glVertex2f(0.4,0.2);
  glVertex2f(0.4,0.2);
  glVertex2f(0.2,0.3);
  glVertex2f(0.2,0.3);
  glVertex2f(-0.4,0.15);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(-0.08,-0.06);
  glVertex2f(-0.1,0.225);
  glVertex2f(0.15,-0.3);
  glEnd();
  glBegin(GL_LINES);
  glVertex2f(-0.08,-0.06);
  glVertex2f(-0.1,0.225);
  glVertex2f(-0.08,-0.06);
  glVertex2f(0.15,-0.3);
  glEnd();
}

void displayVertMoveConcaveOne() {
  glColor3f(0.0f,1.0f,0.0f);
  glPointSize((real)renderSettings->getVertSize());
  glBegin(GL_POINTS);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.3,0.3);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,-0.05);
  glVertex2f(-0.07,0.3);
  glEnd();
  glBegin(GL_LINES);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,-0.05);
  glVertex2f(0.2,0.0);
  glVertex2f(-0.07,0.3);
  glEnd();
}

void displayVertMoveConcaveTwo() {
  glColor3f(0.0f,1.0f,0.0f);
  glPointSize((real)renderSettings->getVertSize());
  glBegin(GL_POINTS);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.3,0.3);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,-0.05);
  glVertex2f(-0.07,0.3);
  glEnd();
  glBegin(GL_LINES);
  //glVertex2f(0.2,0.0);
  //glVertex2f(0.3,-0.05);
  //glVertex2f(0.2,0.0);
  //glVertex2f(-0.07,0.3);
  glEnd();
  glColor3f(0.0,0.0,1.0);
  glBegin(GL_LINES);
  glVertex2f(0.2,0.0);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,0.3);
  glVertex2f(0.2,0.0);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.2,0.0);
  glVertex2f(0.0,0.05);
  glEnd();
  glColor3f(1.0,0.0,1.0);
  glBegin(GL_LINES);
  glVertex2f(0.2,0.0);
  glVertex2f(-0.3,-0.3);
  glEnd();
}

void displayVertMoveConcaveThree() {
  glColor3f(0.0f,1.0f,0.0f);
  glPointSize((real)renderSettings->getVertSize());
  glBegin(GL_POINTS);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.3,0.3);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,-0.05);
  glVertex2f(-0.07,0.3);
  glEnd();
  glColor3f(1.0,0.0,0.0);
  glLineWidth((real)renderSettings->getEdgeSize()*0.6);
  glBegin(GL_LINES);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(0.2,0.0);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.2,0.0);
  glVertex2f(0.0,0.05);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.2,0.0);
  glVertex2f(0.3,0.3);
  glEnd();
}

void displayVertMoveConcaveFour() {
  glColor3f(0.0f,1.0f,0.0f);
  glPointSize((real)renderSettings->getVertSize());
  glBegin(GL_POINTS);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.3,0.3);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(0.13,0.04);
  glVertex2f(0.3,-0.05);
  glVertex2f(-0.07,0.3);
  glEnd();
  glColor3f(1.0,0.0,0.0);
  glLineWidth((real)renderSettings->getEdgeSize()*0.6);
  glBegin(GL_LINES);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(0.13,0.04);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.13,0.04);
  glVertex2f(0.0,0.05);
  glVertex2f(0.13,0.04);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.13,0.04);
  glVertex2f(0.3,0.3);
  glEnd();
}

void displayVertMoveConcaveFive() {
  glColor3f(0.0f,1.0f,0.0f);
  glPointSize((real)renderSettings->getVertSize());
  glBegin(GL_POINTS);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glEnd();
  glLineWidth((real)renderSettings->getEdgeSize()*1.2);
  glBegin(GL_LINES);
  glVertex2f(-0.3,0.3);
  glVertex2f(0.3,0.3);
  glVertex2f(-0.3,0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(-0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.0,0.05);
  glVertex2f(0.3,-0.3);
  glVertex2f(0.3,0.3);
  glEnd();
  glBegin(GL_POINTS);
  glVertex2f(0.13,0.04);
  glVertex2f(0.3,-0.05);
  glVertex2f(-0.07,0.3);
  glEnd();
  glBegin(GL_LINES);
  glVertex2f(0.13,0.04);
  glVertex2f(0.3,-0.05);
  glVertex2f(0.13,0.04);
  glVertex2f(-0.07,0.3);
  glEnd();
}
