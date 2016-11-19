/*****************************************************************
file:graph2.cpp
contain: class which inherit from graph.cpp
*****************************************************************/
#include"Heap.h"
#include"Graph2.h"

void InheGraph::printbyBFS()
{
	resetVisit();

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

void InheGraph::resetVisit()
{
	Vertex *runVertex = gHead;

	while (runVertex != NULL)
	{
		runVertex->processed = false;
		runVertex = runVertex->nextVertex;
	}

}
