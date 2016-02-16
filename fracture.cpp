#include "fracture.h"

#include <iostream>

using namespace std;

Fracture::Fracture() {
	verts = new Array<Vertex*>();
	edges = new Array<Edge*>();
	faces = new Array<Face*>();
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

void Fracture::clearAndReloadFaces() {
	// we may not want to do this
}

void Fracture::createNewVertex(float x,float y) {
	// need to figure out how to connect it with all verts near it...
	verts->add(new Vertex(x,y));
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

void Fracture::draw() {
	for(int i=0;i<verts->getSize();i++)
		verts->get(i)->draw();
	for(int i=0;i<edges->getSize();i++)
		edges->get(i)->draw();
	// maybe draw the faces
}

Array<Vertex*>* Fracture::getVerts() { return verts; }
Array<Edge*>* Fracture::getEdges() { return edges; }
Array<Face*>* Fracture::getFaces() { return faces; }
