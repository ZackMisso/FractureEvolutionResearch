#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "../globalInclude.h"
#include "../src/include/GL/glui.h"

// this class contains all objects in the user interface

class Interface {
public:
  // fracture description
  GLUI_Rollout* objectDescriptionMenu;
  GLUI_StaticText* edgesLabel;
  GLUI_StaticText* vertexsLabel;
  GLUI_StaticText* facesLabel;
  GLUI_Button* saveFracture;
  GLUI_Button* loadFracture;
  GLUI_Button* clearFracture;
  // settings menu
  GLUI_Rollout* interfaceMenu;
  GLUI_Button* selectFacesButton;
  GLUI_Button* selectEdgesButton;
  GLUI_Button* selectVertsButton;
  GLUI_Button* selectNoneButton;
  // current selection
  GLUI_Rollout* selectedMenu; // new
  GLUI_Rollout* faceSelectedMenu; // new
  GLUI_StaticText* faceID; // new
  GLUI_Rollout* vertSelectedMenu; // new
  GLUI_StaticText* vertID; // new
  GLUI_Rollout* edgeSelectedMenu; // new
  GLUI_StaticText* edgeID; // new
  // find menu
  GLUI_Rollout* findMenu;
  GLUI_Rollout* findVertMenu;
  GLUI_EditText* findVertID;
  GLUI_Button* findVertButton;
  GLUI_Rollout* findEdgeMenu;
  GLUI_EditText* findEdgeID;
  GLUI_Button* findEdgeButton;
  GLUI_Rollout* findFaceMenu;
  GLUI_EditText* findFaceID;
  GLUI_Button* findFaceButton;

  // edit fracture
  GLUI_Rollout* editFractureMenu;
  GLUI_Rollout* addVertexMenu;
  GLUI_EditText* vertexXCoord;
  GLUI_EditText* vertexYCoord;
  GLUI_Button* addVertexButton;
  GLUI_Rollout* addEdgeMenu; // new
  GLUI_EditText* vertexOneID; // new
  GLUI_EditText* vertexTwoID; // new
  GLUI_Button* addEdgeButton;
  // camera menu
  GLUI_Rollout* cameraMenu;
  // render menu
  GLUI_Rollout* renderMenu;
  GLUI_EditText* vertSizeText;
  GLUI_EditText* edgeSizeText;
  GLUI_Button* displayVertsButton;
  GLUI_Button* displayEdgesButton;
  GLUI_Button* displayFacesButton;
  GLUI_Button* displayFaceTrimeshButton;
  // evolution menu
  GLUI_Rollout* evolutionMenu;
  GLUI_Button* randomMutation;
  // test menu
  GLUI_Rollout* testMenu; // new
  GLUI_StaticText* mouseXpos; // new
  GLUI_StaticText* mouseYpos; // new

//public:
  Interface(GLUI* subwindow);
  ~Interface();
  //void createInterface(GLUI* subwindow);
  // callbacks
  //void cb_saveFracture(int id);
  //void cb_loadFracture(int id);
};

#endif
