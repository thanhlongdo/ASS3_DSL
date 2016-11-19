/*****************************************************************
file:graph2.cpp
contain: class which inherit from graph.cpp
*****************************************************************/

#include"Graph2.h"
#include"graph.h"

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

				if ((tempvt!=NULL)&&(tempvt->processed == false) && (Queue.dataExist(tempvt->data) == false))
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

bool InheGraph::RemoveEdge(Vertex* from, Edge* from_to)
{
	if (from->firstEdge == NULL)
		return false;
	else if (from->firstEdge->nextEdge == NULL && from_to==from->firstEdge)
	{
		Edge *runEdge = from->firstEdge;
		
		from->firstEdge = NULL;
		delete runEdge;
		runEdge = NULL;
	}
	else
	{
		Edge *runEdge = from->firstEdge;

		//find edge to delete
		while (runEdge!=from_to)
		{
			runEdge = runEdge->nextEdge;
		}

		//can't find edge to delete
		if (runEdge == NULL)
			return false;

		//delete edge
		if (runEdge==from->firstEdge)
		{
			from->firstEdge = runEdge->nextEdge;
			runEdge->nextEdge = NULL;
			delete runEdge;
			runEdge = NULL;
		}
		else
		{
			Edge *preEdge = from->firstEdge;

			while (preEdge->nextEdge != runEdge)
			{
				preEdge = preEdge->nextEdge;
			}

			preEdge->nextEdge = runEdge->nextEdge;
			delete runEdge;
			runEdge = NULL;
		}
	}

	return true;
}

bool InheGraph::RemoveEdge(int fromData, int toData)
{
	Vertex *runVertex = gHead;
	while (runVertex->data!=fromData&&runVertex!=NULL)
	{
		runVertex = runVertex->nextVertex;
	}
	if (runVertex == NULL)//fromdata don't exist in graph
		return false;

	Edge *runEdge = runVertex->firstEdge;
	while (runEdge!=NULL&&runEdge->destination->data!=toData)
	{
		runEdge = runEdge->nextEdge;
	}
	if (runEdge == NULL)//don't exist these edge in graph
		return false;

	RemoveEdge(runVertex, runEdge);

	return true;
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

bool InheGraph::RemoveVertex(int reData)
{
	Vertex *runvertex = gHead;
	while (runvertex != NULL&&runvertex->data != reData)
		runvertex = runvertex->nextVertex;

	if (runvertex == NULL)
		return false;

	RemoveVertex(runvertex);
	return true;
}

bool InheGraph::RemoveVertex(Vertex* vertex)
{
	//remove edge point to vertex
	deleteEDgeTo(vertex->data);

	//delete edge of vertex
	deleteALLEdge(vertex);

	//delete vertex
	if (gHead == NULL)
		return false;
	else if (gHead->nextVertex == NULL&&vertex == gHead)
	{
		delete vertex;
		gHead= vertex = NULL;
	}
	else if (gHead == vertex)
	{
		gHead = gHead->nextVertex;
		vertex->nextVertex = NULL;
		delete vertex;
		vertex = NULL;
	}
	else
	{
		Vertex *preVertex = gHead;
	
		while (preVertex != NULL&&preVertex->nextVertex != vertex)
		{
			preVertex = preVertex->nextVertex;
		}

		if (preVertex == NULL)
			return false;
		else
		{
			preVertex->nextVertex = vertex->nextVertex;
			delete vertex;
			vertex = NULL;
		}

	}

	return true;
}

void InheGraph::deleteALLEdge(Vertex *vertex)
{
	if (vertex->firstEdge == NULL)
		return;
	else
	{
		Edge *runVertex = vertex->firstEdge, *nextVertex = vertex->firstEdge->nextEdge;

		vertex->firstEdge = NULL;
		while (runVertex != NULL)
		{
			runVertex->nextEdge = NULL;
			delete runVertex;
			runVertex = nextVertex;
			if(nextVertex!=NULL)
				nextVertex = nextVertex->nextEdge;
		}
	}
}

void InheGraph::deleteEDgeTo(int data)
{
	Vertex *runvertex = gHead;

	while (runvertex != NULL)
	{
		Edge *runEdge = runvertex->firstEdge;
		while (runEdge != NULL)
		{
			Edge *tempVertex = runEdge->nextEdge;
			if (runEdge->destination->data == data)
				RemoveEdge(runvertex->data, data);

			runEdge = tempVertex;
		}

		runvertex=runvertex->nextVertex;
	}
}