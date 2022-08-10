// Final202206.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include<stack>
#include<queue>
#include "BinarySearchTree.h"
#include "HashedDictionary.h" 

using namespace std;

void displayWordCount(BinaryNode<string>& entry)
{
	cout << entry.getItem() << "(" << entry.getCount() << ")  ";
}

void displayWordCount(HashedEntry<string, string>& entryPtr)
{
	cout << entryPtr.getItem() << "(" << entryPtr.getCount() << ")  ";
}

void input(string sMessage, string& sInputString)
{
	do {
		cout << sMessage << endl;
		cin >> sInputString;
	} while (cin.fail());
}

void input(string sMessage, int& inputNum)
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
	// add your code here

	int note = 1, cnt = 0;
	string string;
	
	if (size == PQSIZE){
		cout << "ARRAY Priority queue full!" << endl;
		return;
	} else {
		for (int i = 0; i < size; i++) {
			if (word == pqArray[i].getItem()) {
				pqArray[i].countUp();
				note = 0;
			}
		}
		if (note == 1) {		// 如果不重複
			pqArray[size].setItem(word);
			pqArray[size].setCount(1);
			size++;
		}
		for (int t = 0; t < size - 1; t++) {
			for (int i = t + 1; i < size; i++) {
				if (pqArray[t].getCount() < pqArray[i].getCount()) {	// 把cnt較大的往前移
					string = pqArray[t].getItem();
					cnt = pqArray[t].getCount();
					pqArray[t] = pqArray[i];
					pqArray[i].setItem(string);
					pqArray[i].setCount(cnt);
				}else if (pqArray[t].getCount() == pqArray[i].getCount()) {	// 如果cnt一樣
					if (pqArray[t].getItem().size() < pqArray[i].getItem().size()) {	// size越大越前面
						string = pqArray[t].getItem();
						cnt = pqArray[t].getCount();
						pqArray[t] = pqArray[i];
						pqArray[i].setItem(string);
						pqArray[i].setCount(cnt);
					}else if (pqArray[t].getItem().size() == pqArray[i].getItem().size()) {	// 如果size一樣，字串內容越大擺越前面（"efg">"abc"）
						if (pqArray[t].getItem() < pqArray[i].getItem()) {
							string = pqArray[t].getItem();
							cnt = pqArray[t].getCount();
							pqArray[t] = pqArray[i];
							pqArray[i].setItem(string);
							pqArray[i].setCount(cnt);
						}
					}
				}
			}
		}
	}
	return;
}


// I am a girl she is a girl too
int pqArrayDelete(BinaryNode<string>* pqArray, int& size, const string word)
{
	if (size == 0) {
		cout << "ARRAY Priority queue empty!" << endl;
		return -1;
	}
	// add your code here

	int cnt = 0, check = -1;
	string string;
	for(int t = 0; t < size; t++){
		if(pqArray[t].getItem() == word){
			pqArray[t].countDown();
			if(pqArray[t].getCount() == 0){		//若字串被被刪到沒有了
				for(int m = t; m < size; m++){
					string = pqArray[m+1].getItem();
					cnt = pqArray[m+1].getCount();
					pqArray[m].setItem(string);
					pqArray[m].setCount(cnt);
				}
				size--;
				check = 0;
				break;
			}
			check = pqArray[t].getCount();
		}
	}

	for (int t = 0; t < size - 1; t++) {
		for (int i = t + 1; i < size; i++) {
			if (pqArray[t].getCount() < pqArray[i].getCount()) {	// 把cnt較大的往前移
				string = pqArray[t].getItem();
				cnt = pqArray[t].getCount();
				pqArray[t] = pqArray[i];
				pqArray[i].setItem(string);
				pqArray[i].setCount(cnt);
			}else if (pqArray[t].getCount() == pqArray[i].getCount()) {	// 如果cnt一樣
				if (pqArray[t].getItem().size() < pqArray[i].getItem().size()) {	// size越大越前面
					string = pqArray[t].getItem();
					cnt = pqArray[t].getCount();
					pqArray[t] = pqArray[i];
					pqArray[i].setItem(string);
					pqArray[i].setCount(cnt);
				}else if (pqArray[t].getItem().size() == pqArray[i].getItem().size()) {	// 如果size一樣，字串內容越大擺越前面（"efg">"abc"）
					if (pqArray[t].getItem() < pqArray[i].getItem()) {
						string = pqArray[t].getItem();
						cnt = pqArray[t].getCount();
						pqArray[t] = pqArray[i];
						pqArray[i].setItem(string);
						pqArray[i].setCount(cnt);
					}
				}
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
				cout << " -";
			else
				cout << ' ' << matrixGraph[i][j];
		}
		cout << '\n';
	}
}


int averageEdgeWeight(int** matrixGraph, int numVertices)
{
	// add your code here
	int num = 0, cnt = 0;
	for(int t = 0;t < numVertices; t++){
		for(int i = t + 1; i < numVertices; i++){
			if(matrixGraph[t][i] < INT_MAX && matrixGraph[t][i] != 0){
				num += matrixGraph[t][i];
				cnt++;
			}
		}
	}
	num /= cnt;
	return num;
}


void updateEdgeWeight(int** matrixGraph, int numVertices, int vertexNo1, int vertexNo2, int weight)
{
	// add your code here
	if(matrixGraph[vertexNo1][vertexNo2] < INT_MAX && vertexNo1 != vertexNo2){
		matrixGraph[vertexNo1][vertexNo2] = weight;
		matrixGraph[vertexNo2][vertexNo1] = weight;
	}
	
	return;
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

	int** matrixGraph = new int* [numVertices];

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
		input("\nEnter command: V for average edge weight, U to update edge weight, or X to Exit", sInput);

		if (sInput == "V" || sInput == "v") {
			cout << "The average edge weight is " << averageEdgeWeight(matrixGraph, numVertices) << endl;
		}
		else if (sInput == "u" || sInput == "U") {
			int vertexNo1, vertexNo2, weight;
			input("Enter vertex1 no: ", vertexNo1);
			input("Enter vertex1 no: ", vertexNo2);
			input("Enter new weight: ", weight);

			updateEdgeWeight(matrixGraph, numVertices, vertexNo1, vertexNo2, weight);
			cout << "The graph after updating edge weight:\r\n";
			showAdjMatrix(matrixGraph, numVertices);
			cout << "The average edge weight is " << averageEdgeWeight(matrixGraph, numVertices) << endl;
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r\n" << endl;
	}

	return;
}
// ================ Q3 Begins Here ==================

void display(BinaryNode<int>& aNode)
{
	cout << aNode.getItem() << "  ";
}

void doQ3()
{
	string sInput, aString, aLine;
	BinarySearchTree<int> myBST;
	int key;

	while (1) {
		input("\nEnter command: A to Add, S for isAllSingle, C for nodesOfOnlyChild, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			while (true)
			{
				cout << "Enter a value, 0 to end: ";
				cin >> key;

				if (key == 0)
					break;

				myBST.add(key);
			}

			cout << endl << "The inoder traversal of the BST is " << endl;
			myBST.inorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "S" || sInput == "s") {
			input("Enter a value: ", key);

			if (myBST.isAllSingleR(key))
				cout << endl << "R: All " << key << "'s child and decendent are their parents' only child." << endl;
			else
				cout << endl << "R: Not all " << key << "'s child and decendent are their parents' only child." << endl;

			if (myBST.isAllSingleI(key))
				cout << endl << "I: All " << "'s child and decendent are their parents' only child." << endl;
			else
				cout << endl << "I: Not all " << key << "'s child and decendent are their parents' only child." << endl;

		}
		else if (sInput == "C" || sInput == "c") {
			cout << endl << "I: Count of the nodes having an only child is " << myBST.nodesOfOnlyChildI() << endl;
			cout << endl << "R: Count of the nodes having an only child is " << myBST.nodesOfOnlyChildR() << endl;
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
