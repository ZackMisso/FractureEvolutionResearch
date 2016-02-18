#include "fracture.h"
#include <GL/glut.h>

#include <iostream>

using namespace std;

Fracture::Fracture() {
	verts = new Array<Vertex*>();
	edges = new Array<Edge*>();
	faces = new Array<Face*>();
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
	verts->add(new Vertex(-0.5,-0.5));
	verts->add(new Vertex(-0.5,0.5));
	verts->add(new Vertex(0.5,0.5));
	verts->add(new Vertex(0.5,-0.5));
	edges->add(new Edge(-0.5,-0.5,-0.5,0.5));
	edges->add(new Edge(-0.5,0.5,0.5,0.5));
	edges->add(new Edge(0.5,0.5,0.5,-0.5));
	edges->add(new Edge(0.5,-0.5,-0.5,-0.5));
	Face* face = new Face();
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

void Fracture::createNewVertex(float x,float y) {
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

void Fracture::draw(RenderSettings* renderSettings) {
	if(renderSettings->getDisplayFaces()) {
		// maybe draw the faces
	}
	if(renderSettings->getDisplayVerts()) {
		glPointSize((float)renderSettings->getVertSize());
		glBegin(GL_POINTS);
		//glPointSize((float)renderSettings->getVertSize());
		cout << "DRAWING VERTS :: " << (float)renderSettings->getVertSize() << endl;
		for(int i=0;i<verts->getSize();i++)
			verts->get(i)->draw();
		glEnd();
	}
	if(renderSettings->getDisplayEdges()) {
		glLineWidth((float)renderSettings->getEdgeSize());
		glBegin(GL_LINES);
		//glLineWidth((float)renderSettings->getEdgeSize());
		for(int i=0;i<edges->getSize();i++)
			edges->get(i)->draw();
		glEnd();
	}
}

Array<Vertex*>* Fracture::getVerts() { return verts; }
Array<Edge*>* Fracture::getEdges() { return edges; }
Array<Face*>* Fracture::getFaces() { return faces; }
