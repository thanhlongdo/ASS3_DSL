/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	InputReader.h
	Purpose: Helper file for reading input
	
	@author Kien Huynh
	@version 1.0 05-10-2016
***************************************************/
#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool ReadArrayInput(string filename, int*& arr, int& count) {
	ifstream myfile(filename.c_str());
	string line;
	count = 0;
	arr = NULL;
	cout << "Reading array: \n";
	if (myfile.is_open()) {
		//The first number should indicate how many numbers will appear in the second line
		myfile >> count;

		//The rest are elements of the array
		arr = new int[count];

		//Read them one by one
		for (int i = 0; i < count; i++) {
			myfile >> arr[i];
		}
	}
	else {
		cout << "Can't open file " << filename << ".";
		return false;
	}
	return true;
}

bool ReadArrayInputOfGraph(string filename, int*& vertexDataArr, int& vertexCount, int**& edgeDataArr, int& edgeCount) {
	ifstream myfile(filename.c_str());
	string line;
	vertexCount = 0;
	edgeCount = 0;
	vertexDataArr = NULL;
	edgeDataArr = NULL;
	cout << "Reading Graph data: \n";

	if (myfile.is_open()) {
		//Read vertex count on the first line
		myfile >> vertexCount;

		//Create an array to store the data
		vertexDataArr = new int[vertexCount];

		//Read them one by one
		for (int i = 0; i < vertexCount; i++) {
			myfile >> vertexDataArr[i];
		}

		//Read edge count on the 3rd line
		myfile >> edgeCount;

		//Create an array to store the Edge data
		//Each row of edgeDataArr indicates an edge
		//For example: edgeDataArr[0][0] = 5; edgeDataArr[0][1] = 7 means that there is an Edge goes from 5 to 7.
		edgeDataArr = new int*[edgeCount];
		for (int i = 0; i < edgeCount; i++) {
			edgeDataArr[i] = new int[2];
		}

		for (int i = 0; i < edgeCount; i++) {
			myfile >> edgeDataArr[i][0];
			myfile >> edgeDataArr[i][1];
		}
	}
	else {
		cout << "Can't open file " << filename << ".";
		return false;
	}
	return true;
}

bool ReadAdjacencyMat(string filename, int**& mat, int& count) {
	ifstream myfile(filename.c_str());
	string line;
	count = 0;
	mat = NULL;
	cout << "Reading adjacency matrix: \n";
	if (myfile.is_open()) {
		//Read vertex count on the first line
		myfile >> count;

		//Create an array to store the data
		mat = new int*[count];
		for (int i = 0; i < count; i++) {
			mat[i] = new int[count];
		}

		for (int i = 0; i < count; i++) {
			for (int j = 0; j < count; j++) {
				myfile >> mat[i][j];
			}
		}
	}
	else {
		cout << "Can't open file " << filename << ".";
		return false;
	}
	return true;
}

#endif
