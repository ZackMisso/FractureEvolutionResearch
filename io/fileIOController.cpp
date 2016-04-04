#include "fileIOController.h"

FileIOController::FileIOController() {
  fractureReader = new FractureReader();
  fractureWriter = new FractureWriter();
  shapeReader = new ShapeReader();
  shapeWriter = new ShapeWriter();
}

FileIOController::~FileIOController() {
  delete fractureWriter;
  delete fractureReader;
  delete shapeReader;
  delete shapeWriter;
}

FractureReader* FileIOController::getFractureReader() { return fractureReader; }
FractureWriter* FileIOController::getFractureWriter() { return fractureWriter; }
ShapeReader* FileIOController::getShapeReader() { return shapeReader; }
ShapeWriter* FileIOController::getShapeWriter() { return shapeWriter; }

void FileIOController::setFractureReader(FractureReader* param) { fractureReader = param; }
void FileIOController::setFractureWriter(FractureWriter* param) { fractureWriter = param; }
void FileIOController::setShapeReader(ShapeReader* param) { shapeReader = param; }
void FileIOController::setShapeWriter(ShapeWriter* param) { shapeWriter = param; }
