#ifndef __FRACTUREWRITER_H__
#define __FRACTUREWRITER_H__

#include "../globalInclude.h"
#include "../dataStructures/intVoidMap.h"
#include "../dataStructures/array.h"
#include "../geometry/fracture.h"
#include <string>

using namespace std;

class FractureWriter {
private:
public:
  static void writeFractureToFile(string path,Fracture* fracture);
  static int getIndexForVert(int id,Array<IntVoidMap*>* verts);
};

#endif
