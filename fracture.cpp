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
	triMesh->addBoundaryTriangles();
	triMesh->calculateAllAdjacents();
}

void Fracture::createNewVertex(float x,float y) { // probably do not need
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
	// DRAWING FACES WILL NOT BE IMPLEMENTED
	//if(renderSettings->getDisplayFaces()) {
	//	// maybe draw the faces
	//}
	if(renderSettings->getDisplayFaceTrimesh()) {
		glLineWidth((float)renderSettings->getEdgeSize()*1.2);
		glColor3f(0.0f,0.0f,1.0f);
		glBegin(GL_TRIANGLES);
		triMesh->draw();
		glEnd();
	}
	if(renderSettings->getDisplayVerts()) {
		glPointSize((float)renderSettings->getVertSize());
		glBegin(GL_POINTS);
		//glPointSize((float)renderSettings->getVertSize());
		//cout << "DRAWING VERTS :: " << (float)renderSettings->getVertSize() << endl;
		//cout << "NUMBER OF VERTS :: " << verts->getSize() << endl;
		for(int i=0;i<verts->getSize();i++)
			verts->get(i)->draw();
		glEnd();
	}
	if(renderSettings->getDisplayEdges()) {
		glLineWidth((float)renderSettings->getEdgeSize());
		glBegin(GL_LINES);
		//cout << "NUMBER OF EDGES :: " << edges->getSize() << endl;
		//glLineWidth((float)renderSettings->getEdgeSize());
		for(int i=0;i<edges->getSize();i++)
			edges->get(i)->draw();
		glEnd();
	}
}

Array<Vertex*>* Fracture::getVerts() { return verts; }
Array<Edge*>* Fracture::getEdges() { return edges; }
Array<Face*>* Fracture::getFaces() { return faces; }
TriMesh* Fracture::getTriMesh() { return triMesh; }
