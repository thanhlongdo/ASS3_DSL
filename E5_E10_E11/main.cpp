#include<iostream>
#include"InputReader.h"
#include"Graph.h"
#include"Graph2.h"
#include"Heap.h"
#include<iomanip>
using namespace std;

void E10();
void convertHeaptoGraph(int position, Heap heap, int sizeHeap, InheGraph &graph);
void E5();
void E11();
void E14();
void numberCycles(InheGraph graph);

int main()
{


	return 0;
}

void E5()
{
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	InheGraph graph = InheGraph();

	ReadArrayInputOfGraph("E5.txt", vertexDataArr, vertexCount, edgeDataArr,edgeCount);
	
	//input to graph
	for (int i = 0; i < vertexCount; i++)
	{
		graph.InsertVertex(vertexDataArr[i]);
	}

	for (int i = 0; i < edgeCount; i++)
	{
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	}

	//print graph
	graph.printbyBFS();
}
	
void E10()
{
	int *arr = NULL;
	int count = 0;
	Heap heap = Heap();
	InheGraph graph = InheGraph();

	ReadArrayInput("E10.txt", arr, count);

	heap = Heap::ArrayToHeap(arr, count);

	heap.PrintHeapTree();

	convertHeaptoGraph(0, heap, count, graph);

	graph.printbyBFS();
}

//function: convert heap to graph
void convertHeaptoGraph(int position, Heap heap, int sizeHeap, InheGraph & graph)
{
	graph.InsertVertex(heap[position]);

	if (2 * position + 1 < sizeHeap)
	{
		convertHeaptoGraph(2*position + 1, heap, sizeHeap, graph);
		graph.InsertEdge(heap[position], heap[2 * position + 1]);
	}

	if (2 * position + 2 < sizeHeap)
	{
		convertHeaptoGraph(2*position + 2, heap, sizeHeap, graph);
		graph.InsertEdge(heap[position], heap[2 * position + 2]);
	}
}

void E11()
{
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	InheGraph graph = InheGraph();

	ReadArrayInputOfGraph("E11.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//input to graph
	for (int i = 0; i < vertexCount; i++)
	{
		graph.InsertVertex(vertexDataArr[i]);
	}

	for (int i = 0; i < edgeCount; i++)
	{
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	}
	
	//======================================================================================

	

	//declare memory for array
	int **twoDimensionArray = new int*[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		twoDimensionArray[i] = new int[vertexCount];
	}

	//set defaulse data of array is 0
	for (int i=0;i<vertexCount;i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			twoDimensionArray[i][j] = 0;
		}
	}

	//write data to array
	Vertex *runVertex = graph.gHead;
	while (runVertex != NULL)
	{
		Edge *runEdge = runVertex->firstEdge;
		while (runEdge != NULL)
		{
			int row = graph.positionofNode(runVertex->data);
			int column = graph.positionofNode(runEdge->destination->data);
			twoDimensionArray[row][column] = 1;

			runEdge = runEdge->nextEdge;
		}

		runVertex = runVertex->nextVertex;
	}

	//print array
	runVertex = graph.gHead;
	cout << "        ";
	for (int i = 0; i < vertexCount; i++)
	{
		cout <<setw(5)<< runVertex->data << " | ";
		runVertex = runVertex->nextVertex;
	}
	cout << endl;

	runVertex = graph.gHead;
	for (int i = 0; i<vertexCount; i++)
	{
		cout << setw(5) << runVertex->data << " | ";
		for (int j = 0; j < vertexCount; j++)
		{
			cout << setw(5) << twoDimensionArray[i][j] << " | ";
		}
		cout << endl;

		runVertex = runVertex->nextVertex;
	}

}

/*count the number of cycles in graph
\pre: graph
\pos: nothing
\return : number of cycles in graph
*/
void numberCycles(InheGraph graph)
{
	InheVertex *runvertex=
}

void E14()
{
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	InheGraph graph = InheGraph();

	ReadArrayInputOfGraph("E5.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//input to graph
	for (int i = 0; i < vertexCount; i++)
	{
		graph.InsertVertex(vertexDataArr[i]);
	}

	for (int i = 0; i < edgeCount; i++)
	{
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	}

	//==================================================================================



}

