#ifndef __FRACTUREREADER_H__
#define __FRACTUREREADER_H__

#include "../globalInclude.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "../geometry/fracture.h"

#define LINE_SIZE 1024
#define TOKEN_LENGTH 8

using namespace std;

enum TokenID { T_NONE=-1, T_VERT, T_EDGE, T_FACE, T_FACE_VERT, T_FACE_EDGE, T_FACE_QUIT };

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
private:

public:
  TokenPair *tokenMatch(char *srchtok);
  void loadFile(const char* file, Fracture* fracture);
  int readFloats(char *tok,real *buf,int bufsz);
  int readInts(char *tok,int *buf,int bufsz);
  void processSkip(char*tok);
  void processVertex(char* tok, Fracture *fracture);
  void processEdge(char *tok,Fracture *fracture);
  void processFace(char *tok,Fracture *fracture);
  void processFaceVert(char* tok,Fracture* fracture);
  void processFaceEdge(char* tok,Fracture* fracture);
  void processFaceQuit(char* tok,Fracture* fracture);

  TokenPair EMPTY_PAIR={"",T_NONE};

  TokenPair tokenMap[7] = {
    {"v", T_VERT},{"f", T_FACE},{"e",T_EDGE},{"fv",T_FACE_VERT},{"fe",T_FACE_EDGE},{"fq",T_FACE_QUIT},
    {"",T_NONE}
  };
  const char* TOK_SEPS = " \t";
};

#endif
