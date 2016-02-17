#include "fracture.h"

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
	// do face detections stuffs
}

void Fracture::draw() {
	for(int i=0;i<verts->getSize();i++)
		verts->get(i)->draw();
	for(int i=0;i<edges->getSize();i++)
		edges->get(i)->draw();
	// maybe draw the faces
}

Array<Vertex*>* getVerts() { return verts; }
Array<Edge*>* getEdges() { return edges; }
Array<Face*>* getFaces() { return faces; }
