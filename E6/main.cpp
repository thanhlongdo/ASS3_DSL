#include<iostream>
#include"InputReader.h"
#include"Graph.h"
#include"Graph2.h"
using namespace std;
void E6();

int main()
{
	E6();
	system("pause");
	return 0;
}
void E6()
{
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	InheGraph graph = InheGraph();

	ReadArrayInputOfGraph("E6.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//input to graph
	for (int i = 0; i < vertexCount; i++)
	{
		graph.InsertVertex(vertexDataArr[i]);
	}

	for (int i = 0; i < edgeCount; i++)
	{
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	}
	graph.printbyBFS();
	//==================================================================================
	int data;
	
	cout << "input data to delete: ";
	cin >> data;
	cout << "result:" << endl;
	while (data != -1)
	{
		graph.RemoveVertex(data);
		graph.printbyBFS();

		cout << "input data to delete: ";
		cin >> data;
		cout << "result:" << endl;
	}
}


