#include "fractureWriter.h"
#include <iostream>
#include <fstream>

void FractureWriter::writeFractureToFile(string path,Fracture* fracture) {
  // get all verts
  fracture->recount();
  Array<Vertex*>* verts = fracture->getVerts();
  Array<Edge*>* edges = fracture->getEdges();
  Array<Face*>* faces = fracture->getFaces();
  Array<IntVoidMap*>* vertMap = new Array<IntVoidMap*>();
  Array<IntVoidMap*>* edgeMap = new Array<IntVoidMap*>();
  Array<IntVoidMap*>* faceMap = new Array<IntVoidMap*>();
  for(int i=0;i<verts->getSize();i++)
    vertMap->add(new IntVoidMap((void*)verts->get(i),verts->get(i)->getID()));
  for(int i=0;i<edges->getSize();i++)
    edgeMap->add(new IntVoidMap((void*)edges->get(i),edges->get(i)->getID()));
  for(int i=0;i<faces->getSize();i++)
    faceMap->add(new IntVoidMap((void*)faces->get(i),faces->get(i)->getID()));
  vertMap = IntVoidMap::sort(vertMap);
  edgeMap = IntVoidMap::sort(edgeMap);
  faceMap = IntVoidMap::sort(faceMap);
  // writing to file
  ofstream fileStream;
  fileStream.open(path);
  for(int i=0;i<vertMap->getSize();i++) {
    Vertex* vert = (Vertex*)vertMap->get(i)->getVal();
    fileStream << "v " << vert->getLocation().xpos << " " << vert->getLocation().ypos << endl;
  }
  for(int i=0;i<edgeMap->getSize();i++) {
    Edge* edge = (Edge*)edgeMap->get(i)->getVal();
    int one = getIndexForVert(edge->getFirstVertID(),vertMap);
    int two = getIndexForVert(edge->getSecondVertID(),vertMap);
    fileStream << "e " << one << " " << two << endl;
  }
  for(int i=0;i<faceMap->getSize();i++) {
    Face* face = (Face*)faceMap->get(i)->getVal();
    cout << "f" << endl;
    cout << "fv ";
    for(int i=0;i<face->getVerts()->getSize();i++)
      cout << getIndexForVert(face->getVerts()->get(i)->getID(),vertMap) << " ";
    cout << endl;
    cout << "fe ";
    for(int i=0;i<face->getEdges()->getSize();i++)
      cout << getIndexForEdge(face->getEdges()->get(i)->getID(),edgeMap) << " ";
    cout << endl;
    cout << "fq" << endl;
  }
  fileStream.close();
}

// This is O(N) can be O(lgN)
int FractureWriter::getIndexForVert(int id,Array<IntVoidMap*>* verts) {
  for(int i=0;i<verts->getSize();i++)
    if(verts->get(i)->getKey() == id)
      return i;
  return -1;
}

// This is O(N) can be O(lgN)
int FractureWriter::getIndexForEdge(int id,Array<IntVoidMap*>* edges) {
  for(int i=0;i<edges->getSize();i++)
    if(edges->get(i)->getKey() == id)
      return i;
  return -1;
}
