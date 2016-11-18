/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Graph.cpp
	Purpose: Implementation of Graph related classes

	@author Kien Huynh
	@version 1.1 05-10-2016
***************************************************/
#include "Graph.h"

//***************************//
//Vertex class implementation//
//***************************//

Vertex::Vertex() {
	data = 0;
	nextVertex = NULL;
	inDegree = 0;
	outDegree = 0;
	processed = false;//status
	firstEdge = NULL;
}

Vertex::Vertex(int _data) {
	data = _data;
	nextVertex = NULL;
	inDegree = 0;
	outDegree = 0;
	processed = false;
	firstEdge = NULL;
}

//*************************//
//Edge class implementation//
//*************************//

Edge::Edge(Vertex* _destination) {
	destination = _destination;
	nextEdge = NULL;
}

//**************************//
//Graph class implementation//
//**************************//

Graph::Graph() {
	gHead = NULL;
	size = 0;
}

Graph::Graph(Vertex* _gHead) {
	gHead = _gHead;
	size = 1;
}

bool Graph::InsertVertex(Vertex* v) {
	if (gHead == NULL) {
		gHead = v;
		size++;
		return true;
	}

	Vertex* pTemp = gHead;
	while (pTemp->nextVertex != NULL) {
		//To avoid confusion, we do not allow Nodes with same data in our graph
		if (pTemp->data == v->data) {
			cout << "\nDifferent Vertices in a Graph should have different data\n";
			cout << "Vertex insertion with data = " << pTemp->data << " failed\n";
			return false;
		}
		pTemp = pTemp->nextVertex;
	}
	size++;
	pTemp->nextVertex = v;
	return true;
}

bool Graph::InsertVertex(int vData) {
	Vertex* newVertex = new Vertex(vData);
	if (gHead == NULL) {
		gHead = newVertex;
		size++;
		return true;
	}
	
	Vertex* pTemp = gHead;
	while (pTemp->nextVertex != NULL) {
		//To avoid confusion, we do not allow Nodes with same data in our graph
		if (pTemp->data == vData) {
			cout << "\nDifferent Vertices in a Graph should have different data\n";
			cout << "Vertex insertion with data = " << pTemp->data << " failed\n";
			return false;
		}
		pTemp = pTemp->nextVertex;
	}

	size++;
	pTemp->nextVertex = newVertex;
	return true;
}


bool Graph::VertexExist(Vertex* v) {
	Vertex* tmp = gHead;
	while (tmp != NULL) {
		if (tmp->data == v->data) {
			return true;
		}
		tmp = tmp->nextVertex;
	}
	return false;
}

bool Graph::VertexExist(int vData) {
	Vertex* tmp = gHead;
	while (tmp != NULL) {
		if (tmp->data == vData) {
			return true;
		}
		tmp = tmp->nextVertex;
	}
	return false;
}

Vertex* Graph::GetVertex(int vData) {
	Vertex* tmp = gHead;
	while (tmp != NULL) {
		if (tmp->data == vData) {
			return tmp;
		}
		tmp = tmp->nextVertex;
	}
	return NULL;
}

bool Graph::InsertEdgeFromVertices(Vertex* from, Vertex* to) {
	if (from->firstEdge == NULL) {
		from->firstEdge = new Edge(to);
		return true;
	}
	else {
		//Check if an Edge already exists
		Edge* eTmp = from->firstEdge;
		Edge* edgeTail = eTmp;

		if (from->data == to->data) {
			//We do not allow a Vertex to point to itself
			//(It would be difficult for students to manage)
			cout << "\nA vertex should not point to itself\n";
			cout << "Edge insertion failed\n";
			return false;
		}

		while (eTmp != NULL) {
			if (eTmp->destination->data == to->data) {
				//This edge already exists, nothing to do here
				cout << "\nEdge already exists\n";
				cout << "Edge insertion failed\n";
				return false;
			}
			edgeTail = eTmp;
			eTmp = eTmp->nextEdge;
		}
		Edge* newEdge = new Edge(to);
		from->outDegree++;
		to->inDegree++;
		edgeTail->nextEdge = newEdge;
	}
	return true;
}

bool Graph::InsertEdge(Vertex* from, Vertex* to) {
	//Perform checking if [from] and [to] exist in the graph yet
	if (!VertexExist(from)) {
		InsertVertex(from);
	}

	if (!VertexExist(to)) {
		InsertVertex(to);
	}

	return InsertEdgeFromVertices(from, to);
}

bool Graph::InsertEdge(int fromData, int toData) {
	//Perform checking if [from] and [to] exist in the graph yet
	if (!VertexExist(fromData)) {
		InsertVertex(fromData);
	}

	if (!VertexExist(toData)) {
		InsertVertex(toData);
	}

	Vertex* from = GetVertex(fromData);
	Vertex* to = GetVertex(toData);

	return InsertEdgeFromVertices(from, to);
}

bool Graph::InsertEdge(Vertex* from, Edge* from_to){
	if (!VertexExist(from)) {
		InsertVertex(from);
	}

	Vertex* to = from_to->destination;

	if (!VertexExist(to)) {
		InsertVertex(to);
	}

	if (from->firstEdge == NULL) {
		from->firstEdge = from_to;
		return true;
	}
	else {
		//Check if an Edge already exists
		Edge* eTmp = from->firstEdge;
		Edge* edgeTail = eTmp;

		if (from->data == to->data) {
			//We do not allow a Vertex to point to itself
			//(It would be difficult for students to manage)
			cout << "\nA vertex should not point to itself\n";
			cout << "Edge insertion failed\n";
			return false;
		}

		while (eTmp != NULL) {
			if (eTmp->destination->data == to->data) {
				//This edge already exists, nothing to do here
				cout << "\nEdge already exists\n";
				cout << "Edge insertion failed\n";
				return false;
			}
			edgeTail = eTmp;
			eTmp = eTmp->nextEdge;
		}
		from->outDegree++;
		to->inDegree++;
		edgeTail->nextEdge = from_to;
	}
	return true;
}

//==========================================================================
