#include "fracture.h"
// USE ON LINUX
#include <GL/glut.h>
// USE ON MAC
//#include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
//#include <GLUT/glut.h>

#include <iostream>

using namespace std;

Fracture::Fracture() {
	verts = new Array<Vertex*>();
	edges = new Array<Edge*>();
	faces = new Array<Face*>();
	triMesh = new TriMesh();
	nextVertID = 0;
	nextEdgeID = 0;
	nextFaceID = 0;
	init(0);
}

Fracture::~Fracture() {
	while(verts->getSize())
		delete verts->removeLast();
	while(edges->getSize())
		delete edges->removeLast();
	while(faces->getSize())
		delete faces->removeLast();
	delete verts;
	delete edges;
	delete faces;
}

void Fracture::init(int points) {
	//cout << "INITING" << endl;
	verts->add(giveVertexID(new Vertex(-0.5,-0.5))));
	verts->add(giveVertexID(new Vertex(-0.5,0.5)));
	verts->add(giveVertexID(new Vertex(0.5,0.5)));
	verts->add(giveVertexID(new Vertex(0.5,-0.5)));
	for(int i=0;i<4;i++)
		verts->get(i)->setBoundary(true);
	// fix edge assignment
	edges->add(giveEdgeID(new Edge(-0.5,-0.5,-0.5,0.5,0,1)));
	edges->add(giveEdgeID(new Edge(-0.5,0.5,0.5,0.5,1,2)));
	edges->add(giveEdgeID(new Edge(0.5,0.5,0.5,-0.5,2,3)));
	edges->add(giveEdgeID(new Edge(0.5,-0.5,-0.5,-0.5,3,0)));
	for(int i=0;i<4;i++)
		edges->get(i)->setBoundary(true);
	Face* face = giveFaceID(new Face());
	for(int i=0;i<4;i++){
		face->getVerts()->add(verts->get(i));
		face->getEdges()->add(edges->get(i));
	}
	faces->add(face);
	for(int i=0;i<points;i++) { /* implement later */ }
}

void Fracture::clearAndReloadFaces() {
	// we may not want to do this
}

bool Fracture::doesSimilarEdgeExists(Edge* edge) {
	for(int i=0;i<edges->getSize();i++)
		if(edge->getFirst().equals(edges->get(i)->getFirst()))
			if(edge->getSecond().equals(edges->get(i)->getSecond()))
				return true;
	return false;
}

void Fracture::recount() {
	edges->clear();
	verts->clear();
	for(int i=0;i<faces->getSize();i++){
		for(int j=0;j<faces->get(i)->getVerts()->getSize();j++)
			if(!verts->contains(faces->get(i)->getVerts()->get(j)))
				verts->add(faces->get(i)->getVerts()->get(j));
		for(int j=0;j<faces->get(i)->getEdges()->getSize();j++)
			if(!edges->contains(faces->get(i)->getEdges()->get(j)))
				edges->add(faces->get(i)->getEdges()->get(j));
	}
}

void Fracture::createTriMesh() { // TODO :: TEST
	triMesh->clean();
	for(int i=0;i<faces->getSize();i++) {
		faces->get(i)->splitIntoTrimesh();
		triMesh->addTriangles(faces->get(i)->getTriMesh());
	}
	// WHY IS THIS NEEDED DONT NEED ADJACENTCIES
	//triMesh->addBoundaryTriangles();
	//triMesh->calculateAllAdjacents();
}

void Fracture::createNewVertex(real x,real y) { // probably do not need
	// need to figure out how to connect it with all verts near it...
	Vertex* newVert = new Vertex(x,y);
	Point2 p;
	p.xpos = x;
	p.ypos = y;
	Face* face = 0x0;
	for(int i=0;i<faces->getSize();i++)
		if(faces->get(i)->contains(p))
			face = faces->get(i);
	if(!face) {
		// the point already exists... or it is on an edge (need to add functionality)
	} else {
		verts->add(newVert);
		Array<Face*>* newFaces = face->separate(newVert);

		while(newFaces->getSize())
			faces->add(newFaces->removeLast());
		delete newFaces;
		delete face;
	}
	// do face detection stuffs
}

void Fracture::createNewEdge(Vertex* one,Vertex* two) {
	Edge *edge = new Edge(one->getLocation(),two->getLocation());
	one->getEdges()->add(edge);
	two->getEdges()->add(edge);
	Face* oldFace = 0x0;
	for(int i=0;i<faces->getSize();i++)
		if(faces->get(i)->contains(one) && faces->get(i)->contains(two))
			oldFace = faces->get(i);
	if(!oldFace) {
		// THIS IS A MAJOR ERROR.... FIX TO BE MADE LATER
		cout << "MAJOR ERROR :: Cant Split Edge" << endl;
	}
	// keep implementing
	// do face detections stuffs probably
}

//real Fracture::faceArea() {
//	real totalArea
//}

Array<Face*>* Fracture::getFacesWithVertex(Vertex* vertex) {
	Array<Face*>* tmp = new Array<Face*>();
	for(int i=0;i<faces->getSize();i++)
		if(faces->get(i)->contains(vertex))
			tmp->add(faces->get(i));
	return tmp;
}

Array<Face*>* Fracture::getFacesWithEdge(Edge* edge) {
	Array<Face*>* tmp = new Array<Face*>();
	for(int i=0;i<faces->getSize();i++)
		if(faces->get(i)->contains(edge))
			tmp->add(faces->get(i));
	return tmp;
}

void Fracture::draw(RenderSettings* renderSettings,InterfaceData* interfaceData) {
	// DRAWING FACES WILL NOT BE IMPLEMENTED
	//if(renderSettings->getDisplayFaces()) {
	//	// maybe draw the faces
	//}
	if(renderSettings->getDisplayFaceTrimesh()) {
		glLineWidth((real)renderSettings->getEdgeSize()*1.2);
		glColor3f(0.0f,0.0f,1.0f);
		glBegin(GL_TRIANGLES);
		triMesh->draw(interfaceData);
		glEnd();
	}
	if(renderSettings->getDisplayVerts()) {
		glPointSize((real)renderSettings->getVertSize());
		glBegin(GL_POINTS);
		//glPointSize((float)renderSettings->getVertSize());
		//cout << "DRAWING VERTS :: " << (float)renderSettings->getVertSize() << endl;
		//cout << "NUMBER OF VERTS :: " << verts->getSize() << endl;
		for(int i=0;i<verts->getSize();i++)
			verts->get(i)->draw();
		glEnd();
	}
	if(renderSettings->getDisplayEdges()) {
		glLineWidth((real)renderSettings->getEdgeSize());
		glBegin(GL_LINES);
		//cout << "NUMBER OF EDGES :: " << edges->getSize() << endl;
		//glLineWidth((float)renderSettings->getEdgeSize());
		for(int i=0;i<edges->getSize();i++)
			edges->get(i)->draw();
		glEnd();
	}
}

Vertex* Fracture::giveVertexID(Vertex* vert) {
	vert->setID(nextVertID++);
	return vert;
}

Edge* Fracture::giveEdgeID(Edge* edge) {
	Vertex* one;
	Vertex* two;
	// inefficient
	if(edge->getFirstVertID() != -1 && edge->getSecondVertID() != -1) {
		for(int i=0;i<verts->getSize();i++) {
			if(verts->get(i)->getID() == edge->getFirstVertID())
				one = verts->get(i);
			if(verts->get(i)->getID() == edge->getSecondVertID())
				two = verts->get(i);
		}
		one->getEdges()->add(edge);
		two->getEdges()->add(edge);
	}
	edge->setID(nextEdgeID++);
	return edge;
}

Face* Fracture::giveFaceID(Face* face) {
	face->setID(nextFaceID++);
	return face;
}

// Brute Force Method
Array<Face*>* Fracture::calculateAllFaces() {
	// to be implemented
	return 0x0;
}

Array<Vertex*>* Fracture::getVerts() { return verts; }
Array<Edge*>* Fracture::getEdges() { return edges; }
Array<Face*>* Fracture::getFaces() { return faces; }
TriMesh* Fracture::getTriMesh() { return triMesh; }
int Fracture::getNextVertID() { return nextVertID; }
int Fracture::getNextEdgeID() { return nextEdgeID; }
int Fracture::getNextFaceID() { return nextFaceID; }

void Fracture::setVerts(Array<Vertex*>* param) { verts = param; }
void Fracture::setEdges(Array<Edge*>* param) { edges = param; }
void Fracture::setFaces(Array<Face*>* param) { faces = param; }
void Fracture::setNextVertID(int param) { nextVertID = param; }
void Fracture::setNextEdgeID(int param) { nextEdgeID = param; }
void Fracture::setNextFaceID(int param) { nextFaceID = param; }
