#ifndef __INTERFACE_H__
#define __INTERFACE_H__

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
  // edit fracture
  GLUI_Rollout* editFractureMenu;
  // camera menu
  GLUI_Rollout* cameraMenu;
  // render menu
  GLUI_Rollout* renderMenu;
  GLUI_EditText* vertSizeText;
  GLUI_EditText* edgeSizeText;
  GLUI_Button* displayVertsButton;
  GLUI_Button* displayEdgesButton;
  GLUI_Button* displayFacesButton;
  // evolution menu
  GLUI_Rollout* evolutionMenu;

//public:
  Interface(GLUI* subwindow);
  ~Interface();
  //void createInterface(GLUI* subwindow);
  // callbacks
  //void cb_saveFracture(int id);
  //void cb_loadFracture(int id);
};

#endif
