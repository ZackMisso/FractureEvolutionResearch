#ifndef __FRACTUREREADER_H__
#define __FRACTUREREADER_H__

#include "globalInclude.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "fracture.h"

#define LINE_SIZE 1024;
#define TOKEN_LENGTH 8;

using namespace std;

enum TokenID { T_NONE=-1, T_VERT, T_EDGE, T_FACE, T_FACE_VERT, T_FACE_EDGE };

struct TokenPair {
  char strval[TOKEN_LENGTH];
  TokenID id;
  bool operator==(const TokenPair& other) const {
    return strcmp(strval,other.strval) == 0 && id == other.id;
  }
  bool operator!=(const TokenPair& other) const {
    return !(*this==other);
  }
};

class FractureReader {
public:
  TokenPair *tokenMatch(char *srchtok) {
    if(!srchtok) return NULL;
    TokenPair *ptokp=&tokenMap[0];
    for(;*ptokp!=EMPTY_PAIR&&strcmp(ptokp->strval,srchtok)!=0;ptokp++) { }
    if(*ptokp==EMPTY_PAIR) ptokp=0;
    return ptokp;
  }

  void loadOBJ(const char* objfile, Fracture* fracture) {
    fstream ifs;
    char line[LINE_SIZE];
    //cout << "READIING" << endl;
    char *tok;
    ifs.open(objfile);
    //cout << "REED" << endl;
    while(!ifs.eof()) {
      //cout << "HEY LISTEN" << endl
      ifs.getline(line,LINE_SIZE);
      //cout << "LISTEN HEY" << endl;
      //cout << line << endl;
      tok=strtok(line,TOK_SEPS);
      //cout << "BOOP" << endl;
      TokenPair *ptok=tokenMatch(tok);
      //cout << "POOB" << endl;
      if(ptok) {
        switch(ptok->id) {
          case T_VERT: processVertex(tok,fracture); break;
          case T_EDGE: processEdge(tok,fracture); break;
          case T_FACE: processFace(tok,fracture); break;
          case T_FACE_VERT: processFaceVert(tok,fracture); break;
          case T_FACE_EDGE: processFaceEdge(tok,fracture); break;
          default: /*processSkip(tok);*/ break;
        }
      }
    }
    //cout << "FINISHED READING" << endl;
    ifs.close();
  }

  int readFloats(char *tok,real *buf,int bufsz) {
    int i=0;
    while((tok=strtok(0,TOK_SEPS))!=0 && i<bufsz)
    buf[i++]=atof(tok);
    return i;
  }

  int readInts(char *tok,int *buf,int bufsz) {
    int i=0;
    while((tok=strtok(0,TOK_SEPS))!=0 && i<bufsz)
    buf[i++]=atoi(tok);
    return i;
  }

  void processSkip(char*tok) { }

  void processVertex(char* tok, Fracture *fracture) {
    //cout << "PROCESSING VERTEX" << endl;
    // IMPLEMENT THIS METHOD
    //float values[3];
    //int cnt=readFloats(tok,values,3);
    //if(cnt>=3) pmesh->addVertex(values);
  }

  void processEdge(tok,fracture) {
    // to be implemented
  }

  void processFace(char *tok,Fracture *fracture) {
    //cout << "PROCESSING FACE" << endl;
    // IMPLEMENT THIS METHOD
    //int ids[256];
    //int cnt=readInts(tok,ids,256);
    //if(cnt>=3){
    //  int tri[3]={ids[0]-1,ids[1]-1,ids[2]-1};
    //  pmesh->addFace(tri);
    //  for(int i=3;i<cnt;i++){
    //    tri[1]=tri[2];
    //    tri[2]=ids[i]-1;
    //    pmesh->addFace(tri);
    //  }
    //}
  }

  void processFaceVert(tok,fracture) {
    // to be implemented
  }

  void processFaceEdge(tok,fracture) {
    // to be implemented
  }

  TokenPair EMPTY_PAIR={"",T_NONE};

  TokenPair tokenMap[3] = {
    {"v", T_VERT},{"f", T_FACE},
    EMPTY_PAIR
  };

  const char* TOK_SEPS = " \t";
};

#endif
