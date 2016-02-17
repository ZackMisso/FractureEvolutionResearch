#include "fracture.h"

Fracture::Fracture() {
	verts = new Array<Vertex*>();
	edges = new Array<Edge*>();
}

Fracture::~Fracture() {
	while(verts->getSize())
		delete verts->removeLast();
	while(edges->getSize())
		delete edges->removeLast();
	delete verts;
	delete edges;
}

void Fracture::createNewVertex(float x,float y) {
	// need to figure out how to connect it with all verts near it...
	verts->add(new Vertex(x,y));
}

void Fracture::createNewEdge(Vertex* one,Vertex* two) {
	Edge *edge = new Edge(one->getLocation(),two->getLocation());
	one->getEdges()->add(edge);
	two->getEdges()->add(edge);	
}

void Fracture::draw() {
	for(int i=0;i<verts->getSize();i++)
		verts->get(i)->draw();
	for(int i=0;i<edges->getSize();i++)
		edges->get(i)->draw();
}
