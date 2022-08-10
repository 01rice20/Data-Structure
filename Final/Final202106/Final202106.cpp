// Final202106.cpp
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include<stack>
#include<queue>
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

	int i = 0, s = 1;
	for (; i < size; i++) {
		if (word == pqArray[i].getItem()) {
			s = 0;
			pqArray[i].countUp();
		}
	}


	string tmpstring;
	int tmpsize = 0;

	if (size == PQSIZE)
		cout << "ARRAY Priority queue full!" << endl;
	else {
		if (s == 1) {		// 如果不重複
			pqArray[size].setItem(word);
			pqArray[size].setCount(1);
			size++;
		}
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (pqArray[i].getItem().size() == pqArray[j].getItem().size()) {	// 如果size（字串長度）一樣，count越大擺越前面
				if (pqArray[i].getCount() < pqArray[j].getCount()) {
					tmpstring = pqArray[j].getItem();
					tmpsize = pqArray[j].getCount();
					pqArray[j] = pqArray[i];
					pqArray[i].setItem(tmpstring);
					pqArray[i].setCount(tmpsize);
				}
				else if (pqArray[i].getCount() == pqArray[j].getCount()) {	// 如果count一樣，字串內容越大擺越前面（"efg">"abc"）
					if (pqArray[i].getItem() < pqArray[j].getItem()) {
						tmpstring = pqArray[j].getItem();
						tmpsize = pqArray[j].getCount();
						pqArray[j] = pqArray[i];
						pqArray[i].setItem(tmpstring);
						pqArray[i].setCount(tmpsize);
					}
				}
			}
			else if (pqArray[i].getItem().size() < pqArray[j].getItem().size()) {	// 把size較大的往前移
				tmpstring = pqArray[j].getItem();
				tmpsize = pqArray[j].getCount();
				pqArray[j] = pqArray[i];
				pqArray[i].setItem(tmpstring);
				pqArray[i].setCount(tmpsize);
			}
		}
	}

	return;

}

int pqArrayDelete(BinaryNode<string>* pqArray, int& size, const string word)
{
	if (size == 0) {
		cout << "ARRAY Priority queue empty!" << endl;
		return -1;
	}

	// add your code here


	//pqArray[size].countDown();
	//size--;

	int count = 0, check = -1;
	string tmpstring;
	for(int t = 0; t < size; t++){
		if(pqArray[t].getItem() == word){
			pqArray[t].countDown();
			if(pqArray[t].getCount() == 0){		//若字串被被刪到沒有了
				for(int m = t; m < size; m++){
					tmpstring = pqArray[m+1].getItem();
					count = pqArray[m+1].getCount();
					pqArray[m].setItem(tmpstring);
					pqArray[m].setCount(count);
				}
				size--;
				check=0;
				break;
			}
			check=pqArray[t].getCount();
		}
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (pqArray[i].getItem().size() == pqArray[j].getItem().size()) {	// 如果size（字串長度）一樣，count越大擺越前面
				if (pqArray[i].getCount() < pqArray[j].getCount()) {
					tmpstring = pqArray[j].getItem();
					count = pqArray[j].getCount();
					pqArray[j] = pqArray[i];
					pqArray[i].setItem(tmpstring);
					pqArray[i].setCount(count);
				}
				else if (pqArray[i].getCount() == pqArray[j].getCount()) {	// 如果count一樣，字串內容越大擺越前面（"efg">"abc"）
					if (pqArray[i].getItem() < pqArray[j].getItem()) {
						tmpstring = pqArray[j].getItem();
						count = pqArray[j].getCount();
						pqArray[j] = pqArray[i];
						pqArray[i].setItem(tmpstring);
						pqArray[i].setCount(count);
					}
				}
			}
			else if (pqArray[i].getItem().size() < pqArray[j].getItem().size()) {	// 把size較大的往前移
				tmpstring = pqArray[j].getItem();
				count = pqArray[j].getCount();
				pqArray[j] = pqArray[i];
				pqArray[i].setItem(tmpstring);
				pqArray[i].setCount(count);
			}
		}
	}
	return check;
}

void doQ1()
{
	BinaryNode<string> pqItems[PQSIZE];
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	int i, size = 0;

	while (1) {
		input("\nEnter A to Add words, R to Remove a word, or X to Exit", sInput);

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
		else if (sInput == "R" || sInput == "r") {
			if (size == 0)
				cout << "PQ is empty!" << endl;
			else {
				input("Enter word: ", aWord);

				if (pqArrayDelete(pqItems, size, aWord) < 0)
					cout << "Not exist in PQ!" << endl;
				else if (size == 0)
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
				cout << " - ";
			else
				cout << ' ' << matrixGraph[i][j];
		}
		cout << '\n';
	}
}

int countEdges(int** matrixGraph, int numVertices)
{
	// add your code here
	int cnt=0;
	for(int t = 0; t < numVertices; t++){
		for(int x = t + 1; x < numVertices; x++){
			if(matrixGraph[t][x] != INT_MAX)
				cnt++;
		}
	}

	return cnt;
}

int countWeights(int** matrixGraph, int numVertices)
{
	// add your code here
	int storeWeight[numVertices], cnt=0;
	for(int t = 0; t < numVertices; t++){
		storeWeight[t]=0;
	}
	for(int x = 0; x < numVertices; x++){
		for(int i = x + 1; i < numVertices; i++){
			for(int c = 0; c < numVertices; c++){
				if(matrixGraph[x][i] == storeWeight[c]){
					break;
				}else if(storeWeight[c] == 0 && matrixGraph[x][i] != 0){
					storeWeight[c] = matrixGraph[x][i];
					cnt++;
					break;
				}else if(matrixGraph[x][i] == INT_MAX)
					break;
			}
		}
	}
	
	return cnt;
}

int findMaxWeight(int** matrixGraph, int numVertices)
{

	// add your code here
	int storeWeight[numVertices], cnt=0;
	for(int t = 0; t < numVertices; t++){
		storeWeight[t]=0;
	}
	for(int x = 0; x < numVertices; x++){
		for(int i = x + 1; i < numVertices; i++){
			if(matrixGraph[x][i]!=INT_MAX && matrixGraph[x][i] > cnt){
				cnt = matrixGraph[x][i];
			}
		}
	}
	
	return cnt;
}

bool peekPath(int** matrixGraph, int numVertices, int startVertex, int endVertex)
{
	/*
	 q = a new empty queue
	
	 for ( each vertex v adjacent to startVertex )
	   	q.enqeue(v)


	 while (!q.isEmpty()) 
	 {
		q.dequeue(w)

		if ( w is equal to endVertex ) 
			return true;

		for ( each vertex u that is larger than w and adjacent to w )
				q.enqueue(u)
	 }
	 
	 return false;
	*/

	// add your code here


	return false;
}


void doQ2()
{
	string sInput;
	int numVertices, u, v, weight;

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
	/*
	0 1 - - - - - -
	1 0 - 3 4 - - -
	- - 0 - - 5 6 -
	- 3 - 0 - - - 7
	- 4 - - 0 - - -
	- - 5 - - 0 - -
	- - 6 - - - 0 -
	- - - 7 - - - 0
	*/

	cout << "\nThere are " << countEdges(matrixGraph, numVertices) << " edges and " << countWeights(matrixGraph, numVertices) << " different weights\n";

	cout << "\nThe max. edge weight is ";
	cout << findMaxWeight(matrixGraph, numVertices) << "\n";

	cout << "\nThere are paths between\n\n";
	for (int i = 0; i < numVertices - 1; i++)
		for (int j = i + 1; j < numVertices; j++)
			if (peekPath(matrixGraph, numVertices, i, j))
				cout << i << " <===> " << j << endl;
	/*
	0 <===> 1
	0 <===> 3
	0 <===> 4
	0 <===> 7
	1 <===> 3
	1 <===> 4
	1 <===> 7
	2 <===> 5
	2 <===> 6
	3 <===> 4
	3 <===> 7
	4 <===> 7
	5 <===> 6
	*/

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
		input("\nEnter command: A to Add, N to Count, C to Clear, or X to Exit", sInput);

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
			cout << endl << "The mirrored and reverse levelorder traversal of the BST are " << endl;
			myBST.levelorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "N" || sInput == "n") {
			cout << endl << "The iterative non leaf count of the BST is " << myBST.countNonLeaves("i");
			cout << endl << "The recursive non leaf count of the BST is " << myBST.countNonLeaves("r") << endl;
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

// ================ Q4 Begins Here ==================
void doQ4()
{
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	HashedEntry<string, string>* itemPtr;
	HashedDictionary<string, string> myHashTable(11);

	while (1) {
		input("\nEnter A to Add, R to Remove, Q to Query, D to Display, C to Clear, or X to Exit", sInput);

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
		}
		else if (sInput == "R" || sInput == "r") {
			input("Enter word: ", aWord);

			if (myHashTable.remove(aWord))
				cout << aWord << " is removed." << endl;
			else
				cout << "Word not found!" << endl;
		}
		else if (sInput == "Q" || sInput == "q") {
			input("Enter word: ", aWord);
			itemPtr = myHashTable.getEntry(aWord);

			if (itemPtr == nullptr)
				cout << "Word not found!" << endl;
			else {
				cout << "Retireved word is: ";
				displayWordCount(*itemPtr);
				cout << endl;
			}
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

