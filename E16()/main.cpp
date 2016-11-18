#include<iostream>
#include"InputReader.h"
#include"Graph.h"
#include"Graph2.h"
using namespace std;
void E16();

int main()
{

	E16();
	return 0;
}

void E16()
{	
	//************************************************/
	//creatte graph from data which read from txt file
	/*************************************************/
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	InheGraph graph = InheGraph();

	ReadArrayInputOfGraph("E16.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//input to graph
	for (int i = 0; i < vertexCount; i++)
	{
		graph.InsertVertex(vertexDataArr[i]);
	}

	for (int i = 0; i < edgeCount; i++)
	{
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	}

	//*************************************************
	//print graph
	/**************************************************/

	graph.printbyBFS();

	//
	graph.stronglyConnected(vertexCount) ? cout << "yes" : cout << "no";

}
