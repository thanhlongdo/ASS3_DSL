/*****************************************************************
file:graph2.cpp
contain: class which inherit from graph.cpp
*****************************************************************/

#include"Graph2.h"
void InheGraph::printbyBFS()
{
	if (gHead == NULL)
		return;
	queue Queue = queue();

	Vertex *beginNode = gHead;

	while (beginNode != NULL)
	{
		Queue.enqueue(beginNode->data);

		while (!Queue.Emty())
		{
			Vertex *tempvertex = GetVertex(Queue.head->data);

			supportforPrinbyBFS(Queue.head->data);//print node.
			tempvertex->processed = true;// visited node

			Queue.dequeue();

			Edge *tempedge = tempvertex->firstEdge;
			while (tempedge != NULL)
			{
				Vertex *tempvt = GetVertex(tempedge->destination->data);

				if ((tempvt->processed == false) && (Queue.dataExist(tempvt->data) == false))
					Queue.enqueue(tempedge->destination->data);

				tempedge = tempedge->nextEdge;
			}
		}

		for (beginNode = gHead; beginNode != NULL && beginNode->processed == true; beginNode = beginNode->nextVertex);

		//condition to break;
		if (beginNode == NULL)
			break;
	}
}

//hàm này sẽ in node có giá trị tương ứng với giá trị đưa vào
void InheGraph::supportforPrinbyBFS(int data)
{
	Vertex *tempvertex = GetVertex(data);
	Edge *tempEdge = tempvertex->firstEdge;

	cout << data;
	while (tempEdge != NULL)
	{
		cout << "->" << tempEdge->destination->data;
		tempEdge = tempEdge->nextEdge;
	}
	cout << endl;
}

//hàm này tìm node chứa data trùng với data đưa vào và trả mấy xem node đó đứng thứ mấy trong linked list
// return 9999 is error
int InheGraph::positionofNode(int data)
{
	int index = 0;
	Vertex *runVertex = gHead;

	while (runVertex != NULL && runVertex->data != data)
	{
		index++;
		runVertex = runVertex->nextVertex;
	}

	if (runVertex != NULL)
		return index;

	cout << "error";
	return 9999;

}

nodequeue::nodequeue(int data)
{
	this->data = data;
	next = NULL;
}

nodequeue::nodequeue()
{
	data = 0;
	next = NULL;
}

queue::queue()
{
	head = tail = NULL;
}

void queue::enqueue(int data)
{
	if (head == NULL)
		head = tail = new nodequeue(data);
	else
	{
		tail->next = new nodequeue(data);
		tail = tail->next;
	}
}

void queue::dequeue()
{
	if (head == NULL)
		return;
	else if (head == tail)
	{
		delete tail;
		head = tail = NULL;
	}
	else
	{
		nodequeue *runptr = head;

		head = head->next;

		runptr->next = NULL;
		delete runptr;
		runptr = NULL;
	}
}

bool queue::Emty()
{
	if (head == NULL)
		return true;
	return false;
}

bool queue::dataExist(int data)
{
	nodequeue *runptr = head;

	while (runptr != NULL)
	{
		if (runptr->data == data)
			return true;

		runptr = runptr->next;
	}

	return false;
}
//
//Vertex* Graph::GetVertex(int vData) {
//	Vertex* tmp = gHead;
//	while (tmp != NULL) {
//		if (tmp->data == vData) {
//			return tmp;
//		}
//		tmp = tmp->nextVertex;
//	}
//	return NULL;
//}

/* stronglyconnected():
\return: true if graph is strongly connected graph. else return false
*/
bool InheGraph::stronglyConnected(int size)
{
	//step1: Initialize all vertices as not visited.
	resetVisit();
	//step2: Do a DFS traversal of graph starting from any arbitrary vertex v. If DFS traversal doesn’t visit all vertices, then return false.

	//visit node by using breath first search  from gHead
	onevisitother();

	// checking if existing a node which is not visited . then return false
	if (checking() == false)
		return false;

	//step 3:  Reverse all arcs (or find transpose or reverse of graph)

	//transform graph to matrix
	int **twoDimensionArray = graphToMatrix();

	//create a graph which is reserved graph
	InheGraph reservedGraph = InheGraph();

	//add vertex
	Vertex *runVertex = gHead;
	while (runVertex != NULL)
	{
		reservedGraph.InsertVertex(runVertex->data);
		runVertex = runVertex->nextVertex;
	}
	//add edge
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (twoDimensionArray[i][j] == 1)
			{
				reservedGraph.InsertEdge(returnVertexE16(j), returnVertexE16(i));
			}
		}
	}

	//step4: Mark all vertices as not-visited in reversed graph
	reservedGraph.resetVisit();

	//step5: Do a DFS traversal of reversed graph starting from same vertex v (Same as step 2). 
	//If DFS traversal doesn’t visit all vertices, then return false. Otherwise return true.

	//visit node by using breath first search  from gHead
	reservedGraph.onevisitother();

	// checking if existing a node which is not visited . then return false
	if (reservedGraph.checking() == false)
		return false;


	return true;
}

int InheGraph::returnVertexE16(int n)
{
	Vertex *tmpVertex = gHead;
	int i = 0;
	while (i<n)
	{
		i++;
		tmpVertex = tmpVertex->nextVertex;
	}

	return tmpVertex->data;
}

void InheGraph::resetVisit()
{
	Vertex *runVertex = gHead;

	while (runVertex != NULL)
	{
		runVertex->processed = false;
		runVertex = runVertex->nextVertex;
	}

}

void InheGraph::onevisitother()
{
	queue Queue = queue();

	Queue.enqueue(gHead->data);
	while (!Queue.Emty())
	{

		Vertex *tempvertex = GetVertex(Queue.head->data);

		//supportforPrinbyBFS(Queue.head->data);//print node.
		tempvertex->processed = true;// visited node

		Queue.dequeue();

		Edge *tempedge = tempvertex->firstEdge;
		while (tempedge != NULL)
		{
			Vertex *tempvt = GetVertex(tempedge->destination->data);

			if ((tempvt->processed == false) && (Queue.dataExist(tempvt->data) == false))
				Queue.enqueue(tempedge->destination->data);

			tempedge = tempedge->nextEdge;
		}
	}

}

bool InheGraph::checking()
{
	Vertex *runVertex = gHead;
	while (runVertex != NULL)
	{
		if (runVertex->processed == false)
			return false;
		runVertex = runVertex->nextVertex;
	}
	return true;
}

int ** InheGraph::graphToMatrix()
{
	//declare memory for array
	int **twoDimensionArray = new int*[size];
	for (int i = 0; i < size; i++)
	{
		twoDimensionArray[i] = new int[size];
	}

	//set defaulse data of array is 0
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			twoDimensionArray[i][j] = 0;
		}
	}

	//write data to array
	Vertex *runVertex = gHead;
	while (runVertex != NULL)
	{
		Edge *runEdge = runVertex->firstEdge;
		while (runEdge != NULL)
		{
			int row = positionofNode(runVertex->data);
			int column = positionofNode(runEdge->destination->data);
			twoDimensionArray[row][column] = 1;

			runEdge = runEdge->nextEdge;
		}

		runVertex = runVertex->nextVertex;
	}

	return twoDimensionArray;
}
