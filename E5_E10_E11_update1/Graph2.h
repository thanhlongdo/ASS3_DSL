#ifdef __GNUC__
#pragma message("g++ used")
#define DEPRECATED(func, message) func __attribute__ ((deprecated(message)))
#elif defined(_MSC_VER)
#define DEPRECATED(func, message) __declspec(deprecated(message)) func
#else
#pragma message("WARNING: UNKNOWN COMPILER")
#define DEPRECATED(func) func
#endif

#ifndef GRAPH2_H
#define GRAPH2_H
#include <cassert>
#include <iostream>
#include"Graph.h"
using namespace std;


class InheEdge:public Edge{};

class InheVertex: public Vertex
{
protected:
	/* only use for E14 task 
	\0 is vertex in white box
	\1 is vertex in pray box
	\2 is vertex in black box
	\ visit this web for more detail: https://www.youtube.com/watch?v=rKQaZuoUR4M&t=385s
	*/
	int processE14;
public:
	InheVertex() :Vertex()
	{
		processE14 = 0;
	}
};

class InheGraph:public Graph
{
public: 
	void printbyBFS();
	int positionofNode(int data);
private:
	void supportforPrinbyBFS(int data);
	void resetVisit();
};

class nodequeue
{
public:
	int data;
	nodequeue *next;

	nodequeue();
	nodequeue(int data);
};
class queue 
{
public:
	nodequeue *head, *tail;
	queue();
	void enqueue(int data);
	void dequeue();
	bool Emty();
	bool dataExist(int data);
};
#endif