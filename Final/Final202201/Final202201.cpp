// Final201706.cpp : 定義主控台應用程式的進入點。
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "BinarySearchTree.h"
#include "HashedDictionary.h" 

using namespace std;

void displayWordCount(BinaryNode<string>&  entry)
{
	cout << entry.getItem() << "(" << entry.getCount() << ")  ";
}

void displayWordCount(HashedEntry<string, string>&  entryPtr)
{
	cout << entryPtr.getItem() << "(" << entryPtr.getCount() << ")  ";
}

void input(string sMessage, string &sInputString)
{
	do {
		cout << sMessage << endl;
		cin >> sInputString;
	} while (cin.fail());
}

void input(string sMessage, int &inputNum)
{
	do {
		cout << sMessage << endl;
		cin >> inputNum;
	} while (cin.fail());
}

void stringToTokens(queue<string>& aQueue, string aString)
{
	string token, theDelimters = ".,!?;: ";
	int end = 0;
	int start = aString.find_first_not_of(theDelimters, end);

	while (start != string::npos) {
		end = aString.find_first_of(theDelimters, start);
		token = aString.substr(start, end - start);
		aQueue.push(token);
		start = aString.find_first_not_of(theDelimters, end);
	}
}

// ================ Q1 Begins Here ==================
#define PQSIZE	10

void pqArrayInsert(BinaryNode<string>* pqArray, int& size, const string word)
{
	if (size == PQSIZE)
		cout << "ARRAY Priority queue full!" << endl;


	// add your code here


	pqArray[size] = word;
	pqArray[size].countUp();
	size++;
}

int pqArrayCountdown(BinaryNode<string>* pqArray, int& size)
{
	if (size == 0) {
		cout << "ARRAY Priority queue empty!" << endl;
		return -1;
	}


	// add your code here


	//pqArray[size].countDown();
	//size--;

	return -1;
}

void doQ1()
{
	BinaryNode<string> pqItems[PQSIZE];
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	int i, size = 0;

	while (1) {
		input("\nEnter A to Add words, C to Count down, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty()) {
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				pqArrayInsert(pqItems, size, aWord);
			}

			for (i = 0; i < size; i++)
				displayWordCount(pqItems[i]);

			cout << endl;
		}
		else if (sInput == "C" || sInput == "c") {
			if (size == 0)
				cout << "PQ is empty!" << endl;
			else {
				input("Enter word: ", aWord);

				int count = pqArrayCountdown(pqItems, size);

				cout << "Word count: " << count << endl;

				if (count < 0)
					cout << "No words to countdown!" << endl;
				else if (count == 0)
					cout << "Last word deleted!" << endl;
				else {
					for (i = 0; i < size; i++)
						displayWordCount(pqItems[i]);

					cout << endl;
				}
			}
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// ================ Q2 Begins Here ==================
void showAdjMatrix(int** matrixGraph, int numVertices)
{
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			if (matrixGraph[i][j] == INT_MAX)
				cout << " -";
			else
				cout << ' ' << matrixGraph[i][j];
		}
		cout << '\n';
	}
}

void DFS_Recu(int** matrixGraph, int numVertices, int vertexNo, bool* visited)
{
	visited[vertexNo] = true;
	cout << " v" << vertexNo;
	

	// add your code here


	return;
}

void DFS_Iter(int** matrixGraph, int numVertices, int vertexNo, bool* visited)
{
	visited[vertexNo] = true;
	cout << " v" << vertexNo;


	// add your code here


	return;
}

void doDFS(int** matrixGraph, int numVertices, int vertexNo)
{
	bool* visited = new bool[numVertices];

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	cout << "\nDFS:";
	DFS_Recu(matrixGraph, numVertices, vertexNo, visited);

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	cout << "\nDFS:";
	DFS_Iter(matrixGraph, numVertices, vertexNo, visited);

	delete[] visited;

	return;
}

int maxEdgeWeight(int** matrixGraph, int numVertices) {
	return -1;
}

void doQ2()
{
	string sInput;
	int numVertices, u, v, weight, vertexNo, vertexStartNo;

	ifstream inFile("graph.txt");

	if (!inFile) {
		cerr << "Error: Failed to open " << "graph.txt" << " for input! \n";
		return;
	}

	if (inFile.peek() == EOF) {
		cerr << "Error: Empty input file! \n";
		return;
	}

	inFile >> numVertices;

	int **matrixGraph = new int*[numVertices];

	for (int i = 0; i < numVertices; i++) {
		matrixGraph[i] = new int[numVertices];

		for (int j = 0; j < numVertices; j++)
			matrixGraph[i][j] = INT_MAX;

		matrixGraph[i][i] = 0;
	}

	while (inFile.peek() != EOF) {
		inFile >> u >> v >> weight;

		if (inFile.fail())
			break;

		if (u < numVertices && v < numVertices)
			matrixGraph[u][v] = matrixGraph[v][u] = weight;
	}

	cout << "\nThe adjacency matrix:\n";
	showAdjMatrix(matrixGraph, numVertices);

	while (1) {
		input("\nEnter D to or X to Exit", sInput);

		if (sInput == "D" || sInput == "d") {
			input("Enter start vertex no: ", vertexStartNo);

			if (vertexStartNo < numVertices) {
				doDFS(matrixGraph, numVertices, vertexStartNo);
				cout << "\nMax Edge Weight: " << maxEdgeWeight(matrixGraph, numVertices);
			}
			else
				cerr << "Error: Vertex no out of range!  \n";
		}
		else  if (sInput == "X" || sInput == "x") {
			if (inFile.is_open())
				inFile.close();

			for (int i = 0; i < numVertices; i++)
				delete[] matrixGraph[i];

			delete matrixGraph;

			return;
		}
		else
			cout << "Unknown command!\r" << endl;
	}

	return;
}

// ================ Q3 Begins Here ==================

void display(BinaryNode<string>& aNode)
{
	cout << aNode.getItem() << "  ";
}

void doQ3()
{
	string sInput, aString, aLine;
	BinarySearchTree<string> myBST;

	while (1) {
		input("\nEnter command: A to Add, S to Successor, P to Parent, N to Count, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);

			string token, theDelimters = ".,!?;: ";
			int end = 0;
			int start = aLine.find_first_not_of(theDelimters, end);

			while (start != string::npos) {
				end = aLine.find_first_of(theDelimters, start);
				token = aLine.substr(start, end - start);
				myBST.add(token);
				start = aLine.find_first_not_of(theDelimters, end);
			}

			cout << endl << "The inoder traversal of the BST is " << endl;
			myBST.inorderTraverse(display);
			cout << endl << "The levelorder traversal of the BST is " << endl;
			myBST.levelorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "S" || sInput == "s") {
			input("Enter a word: ", aString);

			string sucessor = myBST.find(aString);

			if (sucessor != aString)
				cout << endl << "The inorder sucessor of " << aString << " is " << sucessor << endl;
			else
				cout << endl << aString << " has no inorder sucessor in the BST" << endl;
		}
		else if (sInput == "P" || sInput == "p") {
			input("Enter a word: ", aString);

			if (myBST.isParent(aString))
				cout << endl << aString << " is a parent node." << endl;
			else
				cout << endl << aString << " is not a parent node." << endl;
		}
		else if (sInput == "N" || sInput == "n") {
			cout << endl << "The parent count of the BST is " << myBST.countParents() << endl;
		}
		else if (sInput == "C" || sInput == "c") {
			myBST.clear();
			cout << endl << "BST is empty." << endl;
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}

	return;
}

// ================ Q3 Begins Here ==================
void doQ4()
{
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	HashedEntry<string, string>* itemPtr;
	HashedDictionary<string, string> myHashTable(11);

	while (1) {
		input("\nEnter A to Add,  S to Count Down, D to Display, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty()) {
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				myHashTable.add(aWord, aWord);
			}

			cout << "Word count after addition: " << myHashTable.countWords() << endl;
		}
		else if (sInput == "S" || sInput == "s") {

			myHashTable.countDown();
			cout << "Word count after count down: " << myHashTable.countWords() << endl;
		}
		else if (sInput == "D" || sInput == "d") {
			cout << "Words in buckets are: " << endl;

			int i, len = myHashTable.getTableSize();

			for (i = 0; i < len; i++) {
				cout << i << ": ";
				myHashTable.traverse(i, displayWordCount);
				cout << endl;
			}
		}
		else if (sInput == "C" || sInput == "c") {
			myHashTable.clear();
			cout << "Words in buckets are cleared." << endl;
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// =============== Main Begins Here =================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1) {
		cout << endl;
		cout << "1. Priroity queue operations" << endl;
		cout << "2. Graph operations" << endl;
		cout << "3. Binary search tree operations" << endl;
		cout << "4. Hash table operations" << endl;

		input("Enter Question Number( 1 ~ 4 ) or 0 to Exit:", sNum);

		switch (sNum[0] - '0') {
		case 0:
			return 0;
		case 1:
			doQ1();
			break;
		case 2:
			doQ2();
			break;
		case 3:
			doQ3();
			break;
		case 4:
			doQ4();
			break;
		}
	}
}
// ============== Main Program Ends Here ================
