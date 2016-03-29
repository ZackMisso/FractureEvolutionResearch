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
  GLUI_Rollout* selectedMenu;
  GLUI_Rollout* faceSelectedMenu;
  GLUI_StaticText* faceID;
  GLUI_Rollout* vertSelectedMenu;
  GLUI_StaticText* vertID;
  GLUI_Rollout* edgeSelectedMenu;
  GLUI_StaticText* edgeID;
  // find menu
  GLUI_Rollout* findMenu;
  GLUI_Button* printAllVertIDs;
  GLUI_Button* printAllEdgeIDs;
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
  GLUI_Rollout* addEdgeMenu;
  GLUI_EditText* vertexOneID;
  GLUI_EditText* vertexTwoID;
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
  GLUI_Button* addRandomEdgeMutation;
  GLUI_Button* addRandomVertMutation;
  GLUI_Button* edgeCurveMutation;
  GLUI_Button* removeRandomEdgeMutation;
  GLUI_Button* removeRandomVertMutation;
  GLUI_Button* vertPositionMutation;
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
