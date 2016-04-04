#ifndef __FILEIOCONTROLLER_H__
#define __FILEIOCONTROLLER_H__

#include "../globalInclude.h"
#include "fractureWriter.h"
#include "fractureReader.h"
#include "shapeReader.h"
#include "shapeWriter.h"

class FileIOController {
private:
  FractureReader* fractureReader;
  FractureWriter* fractureWriter;
  ShapeReader* shapeReader;
  ShapeWriter* shapeWriter;
public:
  FileIOController();
  ~FileIOController();
  // getter methods
  FractureReader* getFractureReader();
  FractureWriter* getFractureWriter();
  ShapeReader* getShapeReader();
  ShapeWriter* getShapeWriter();
  // setter methods
  void setFractureReader(FractureReader* param);
  void setFractureWriter(FractureWriter* param);
  void setShapeReader(ShapeReader* param);
  void setShapeWriter(ShapeWriter* param);
};

#endif
