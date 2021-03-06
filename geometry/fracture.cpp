#include "fracture.h"
#include <GL/glut.h>

#include <iostream>

using namespace std;

Fracture::Fracture() {
	verts = new Array<Vertex*>();
	edges = new Array<Edge*>();
	faces = new Array<Face*>();
	triMesh = new TriMesh();
	ids = new IDTracker();
	init(0);
}

Fracture::Fracture(bool param) {
	verts = new Array<Vertex*>();
	edges = new Array<Edge*>();
	faces = new Array<Face*>();
	triMesh = new TriMesh();
	ids = new IDTracker();
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
	delete ids;
}

Fracture* Fracture::copy() {
	Fracture* fracture = new Fracture();
	fracture->setIDs(ids->copy());
	for(int i=0;i<edges->getSize();i++)
		fracture->getEdges()->add(edges->get(i)->copy());
	for(int i=0;i<verts->getSize();i++)
		fracture->getVerts()->add(verts->get(i)->copy(fracture->getEdges()));
	for(int i=0;i<faces->getSize();i++)
		fracture->getFaces()->add(faces->get(i)->copy(fracture->getVerts(),fracture->getEdges()));
	return fracture;
}

void Fracture::init(int points) {
	//cout << "INITING" << endl;
	verts->add(giveVertexID(new Vertex(-0.5,-0.5)));
	verts->add(giveVertexID(new Vertex(-0.5,0.5)));
	verts->add(giveVertexID(new Vertex(0.5,0.5)));
	verts->add(giveVertexID(new Vertex(0.5,-0.5)));
	for(int i=0;i<4;i++) {
		verts->get(i)->setBoundary(true);
		verts->get(i)->setIsCorner(true);
	}
	// fix edge assignment
	edges->add(giveEdgeID(new Edge(-0.5,-0.5,-0.5,0.5,0,1)));
	edges->add(giveEdgeID(new Edge(-0.5,0.5,0.5,0.5,1,2)));
	edges->add(giveEdgeID(new Edge(0.5,0.5,0.5,-0.5,2,3)));
	edges->add(giveEdgeID(new Edge(0.5,-0.5,-0.5,-0.5,3,0)));
	for(int i=0;i<4;i++)
		edges->get(i)->setIsBoundary(true);
	Face* face = giveFaceID(new Face());
	for(int i=0;i<4;i++){
		face->addVert(verts->get(i));
		face->addEdge(edges->get(i));
	}
	faces->add(face);
	for(int i=0;i<points;i++) { /* implement later */ }
}

bool Fracture::doesSimilarEdgeExists(Edge* edge) {
	for(int i=0;i<edges->getSize();i++)
		if(edge->getFirst().equals(edges->get(i)->getFirst()))
			if(edge->getSecond().equals(edges->get(i)->getSecond()))
				return true;
	return false;
}

void Fracture::recount() {
	cout << "Called Recount" << endl;
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

	// New Idea Below
	for(int i=0;i<faces->getSize();i++)
		faces->get(i)->clear();
	for(int i=0;i<verts->getSize();i++)
		for(int j=0;j<faces->getSize();j++)
			if(verts->get(i)->belongsToFace(faces->get(j)->getID()))
				faces->get(j)->getVerts()->add(verts->get(i));
	for(int i=0;i<edges->getSize();i++)
		for(int j=0;j<faces->getSize();j++)
			if(edges->get(i)->belongsToFace(faces->get(j)->getID()))
				faces->get(j)->getEdges()->add(edges->get(i));
}

void Fracture::createTriMesh() { // TODO :: TEST
	triMesh->clean();
	for(int i=0;i<faces->getSize();i++) {
		faces->get(i)->splitIntoTrimesh();
		triMesh->addTriangles(faces->get(i)->getTriMesh());
	}
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

Array<Face*>* Fracture::getFacesWithVertex(Vertex* vertex) {
	Array<Face*>* tmp = new Array<Face*>();
	for(int i=0;i<vertex->getFaceIDs()->getSize();i++)
		for(int j=0;j<faces->getSize();j++)
			if(faces->get(j)->getID() == vertex->getFaceIDs()->get(i).val) {
				tmp->add(faces->get(j));
				j = faces->getSize();
			}
	return tmp;
}

Array<Face*>* Fracture::getFacesWithEdge(Edge* edge) {
	Array<Face*>* tmp = new Array<Face*>();
	for(int i=0;i<edge->getFaceIDs()->getSize();i++)
		for(int j=0;j<faces->getSize();j++)
			if(faces->get(j)->getID() == edge->getFaceIDs()->get(i).val) {
				tmp->add(faces->get(j));
				j = faces->getSize();
			}
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
		for(int i=0;i<verts->getSize();i++)
			verts->get(i)->draw();
		glEnd();
	}
	if(renderSettings->getDisplayEdges()) {
		glLineWidth((real)renderSettings->getEdgeSize());
		glBegin(GL_LINES);
		for(int i=0;i<edges->getSize();i++)
			edges->get(i)->draw();
		glEnd();
	}
}

Vertex* Fracture::giveVertexID(Vertex* vert) {
	vert->setID(ids->incrementNextVert());
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
	edge->setID(ids->incrementNextEdge());
	return edge;
}

Face* Fracture::giveFaceID(Face* face) {
	face->setID(ids->incrementNextFace());
	return face;
}

Array<Vertex*>* Fracture::getVerts() { return verts; }
Array<Edge*>* Fracture::getEdges() { return edges; }
Array<Face*>* Fracture::getFaces() { return faces; }
TriMesh* Fracture::getTriMesh() { return triMesh; }
IDTracker* Fracture::getIDs() { return ids; }

void Fracture::setVerts(Array<Vertex*>* param) { verts = param; }
void Fracture::setEdges(Array<Edge*>* param) { edges = param; }
void Fracture::setFaces(Array<Face*>* param) { faces = param; }
void Fracture::setIDs(IDTracker* param) { ids = param; }
