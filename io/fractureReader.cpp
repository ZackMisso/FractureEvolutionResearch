#include "fractureReader.h"

TokenPair* FractureReader::tokenMatch(char *srchtok) {
  if(!srchtok) return NULL;
  TokenPair *ptokp=&tokenMap[0];
  for(;*ptokp!=EMPTY_PAIR&&strcmp(ptokp->strval,srchtok)!=0;ptokp++) { }
  if(*ptokp==EMPTY_PAIR) ptokp=0;
  return ptokp;
}

void FractureReader::loadFile(const char* file,Fracture* fracture) {
  fstream ifs;
  char line[LINE_SIZE];
  char *tok;
  ifs.open(file);
  while(!ifs.eof()) {
    ifs.getline(line,LINE_SIZE);
    tok=strtok(line,TOK_SEPS);
    TokenPair *ptok=tokenMatch(tok);
    if(ptok) {
      switch(ptok->id) {
        case T_VERT: processVertex(tok,fracture); break;
        case T_EDGE: processEdge(tok,fracture); break;
        case T_FACE: processFace(tok,fracture); break;
        case T_FACE_VERT: processFaceVert(tok,fracture); break;
        case T_FACE_EDGE: processFaceEdge(tok,fracture); break;
        case T_FACE_QUIT: processFaceQuit(tok,fracture); break;
        default: /*processSkip(tok);*/ break;
      }
    }
  }
  ifs.close();
}

int FractureReader::readFloats(char* tok,real* buf,int bufsz) {
  int i=0;
  while((tok=strtok(0,TOK_SEPS))!=0 && i<bufsz)
  buf[i++]=atof(tok);
  return i;
}

int FractureReader::readInts(char *tok,int *buf,int bufsz) {
  int i=0;
  while((tok=strtok(0,TOK_SEPS))!=0 && i<bufsz)
  buf[i++]=atoi(tok);
  return i;
}

void FractureReader::processSkip(char*tok) { }

void FractureReader::processVertex(char* tok, Fracture *fracture) {
  //cout << "PROCESSING VERTEX" << endl;
  // IMPLEMENT THIS METHOD
  //float values[3];
  //int cnt=readFloats(tok,values,3);
  //if(cnt>=3) pmesh->addVertex(values);
}

void FractureReader::processEdge(char* tok,Fracture* fracture) {
  // to be implemented
}

void FractureReader::processFace(char *tok,Fracture *fracture) {
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

void FractureReader::processFaceVert(char* tok,Fracture* fracture) {
  // to be implemented
}

void FractureReader::processFaceEdge(char* tok,Fracture* fracture) {
  // to be implemented
}

void FractureReader::processFaceQuit(char* tok,Fracture* fracture) {
  // to be implemented
}
