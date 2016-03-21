#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "globalInclude.h"
#include "src/include/GL/glui.h"

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
  // interface menu
  GLUI_Rollout* interfaceMenu;
  GLUI_Button* selectFacesButton;
  GLUI_Button* selectEdgesButton;
  GLUI_Button* selectVertsButton;
  GLUI_Button* selectNoneButton;
  // edit fracture
  GLUI_Rollout* editFractureMenu;
  GLUI_Rollout* addVertexMenu;
  GLUI_EditText* vertexXCoord;
  GLUI_EditText* vertexYCoord;
  GLUI_Button* addVertexButton;
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

//public:
  Interface(GLUI* subwindow);
  ~Interface();
  //void createInterface(GLUI* subwindow);
  // callbacks
  //void cb_saveFracture(int id);
  //void cb_loadFracture(int id);
};

#endif
