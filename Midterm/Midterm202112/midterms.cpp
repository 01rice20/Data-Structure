// Midterm2021_12.cpp : 定義主控台應用程式的進入點。
//
#include <iostream>
#include <string>
#include <cctype>
#include "polynomial1.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"

#define SIZE 10

void input(string sMessage, string& sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;
	return;
}

void output(string sMessage)
{
	if (sMessage.length() > 0)
		cout << endl << sMessage << endl;

	return;
}

int inputNumber(string sMessage, int A[])
{
	int i;

	for (i = 0; i < SIZE; i++) {
		cout << sMessage;
		cin >> A[i];

		if (A[i] == 0)
			break;
	}

	return i;
}

// ================ Question 1 Begins Here ==================
void reverse(int A[], int start, int end)
{
	int tmp, mid = end / 2;
	if (start > mid) return;

	tmp = A[start];
	A[start] = A[end - start];
	A[end - start] = tmp;


	return reverse(A, start + 1, end);
}

void accumulate(int A[], int start, int end)
{
	if (start == end) return;

	A[start + 1] += A[start];

	return accumulate(A, start + 1, end);
}

void doQ1()
{
	int aArray[SIZE];
	int size = inputNumber("Enter a number (0 to end): ", aArray);

	cout << endl << "Input numbers: ";

	for (int i = 0; i < size; i++)
		cout << aArray[i] << " ";

	reverse(aArray, 0, size - 1);

	cout << endl << "after reverse: ";

	for (int i = 0; i < size; i++)
		cout << aArray[i] << " ";

	cout << endl;

	accumulate(aArray, 0, size - 1);

	cout << endl << "after accumulate: ";

	for (int i = 0; i < size; i++)
		cout << aArray[i] << " ";

	cout << endl;

	return;
}

// ================ Question 1 Ends Here ==================

// ================ Question 2 Begins Here =================
void doQ2()
{
	ArrayPolynomial aArrPoly, copiedArrPoly;
	LinkedPolynomial aLinkPol, copiedLinkPol;

	int coef, expo, maxExpo = 0;

	aArrPoly.clear();

	for (int i = 0; i < MAX_TERMS; i++) {
		cout << "\ninput a's coefficient and exponent: ";
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		if (expo > maxExpo)
			maxExpo = expo;

		aArrPoly.inputArrayBasedTerms(coef, expo);
		aLinkPol.inputLinkBasedTerms(coef, expo);
	}

	cout << "\n\na = ";
	aArrPoly.printArrayBasedPoly();

	cout << "\na = ";
	aLinkPol.printLinkBasedPoly();

	copiedArrPoly.reverseArrayBasedCopy(aArrPoly);
	cout << "\naCopy = ";
	copiedArrPoly.printArrayBasedPoly();

	copiedLinkPol.reverseLinkBasedCopy(aLinkPol);
	cout << "\naCopy = ";
	copiedLinkPol.printLinkBasedPoly();

	for (int i = 0; i < maxExpo; i++) {
		cout << "\n\nAfter inserting " << i + 1 << "X^" << i;

		aArrPoly.insertArrayBasedTerm(i + 1, i);
		cout << "\na= ";
		aArrPoly.printArrayBasedPoly();

		aLinkPol.insertLinkBasedTerm(i + 1, i);
		cout << "\na= ";
		aLinkPol.printLinkBasedPoly();

		cout << "\n\nAfter removing X^" << i << " terms";

		aArrPoly.removeArrayBasedTerm(i);
		cout << "\na= ";
		aArrPoly.printArrayBasedPoly();

		aLinkPol.removeLinkBasedTerm(i);
		cout << "\na= ";
		aLinkPol.printLinkBasedPoly();

		cout << "\n\nAfter reverse coping";

		copiedArrPoly.reverseArrayBasedCopy(aArrPoly);
		cout << "\naCopy = ";
		copiedArrPoly.printArrayBasedPoly();

		copiedLinkPol.reverseLinkBasedCopy(aLinkPol);
		cout << "\naCopy = ";
		copiedLinkPol.printLinkBasedPoly();
	}
	cout << "\n";
}
// ================ Question 2 Ends Here ==================

// ================ Question 3 Begins Here ==================

void displayBag(ArrayBag<string>& bag)
{
	cout << "The bag contains " << bag.getCurrentSize() << " items: ";
	vector<string> bagItems = bag.toVector();
	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
	{
		cout << bagItems[i] << " ";
	}  // end for

	cout << endl;
}  // end displayBag

void bagTester(ArrayBag<string>& bag)
{
	string items[] = { "5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "5E", "5E" };
	string otherItems[] = { "1A", "5E", "3C", "2B", "4D" };


	cout << endl << "After adding 10 items to the bag: " << endl;

	for (int i = 0; i < 10; i++)
		bag.add(items[i]);

	displayBag(bag);

	for (int i = 0; i < 5; i++)
	{
		bag.remove(otherItems[i]);
		cout << endl << "After removing " << otherItems[i] << endl;
		displayBag(bag);
	}
} // end bagTester

void displayBag(LinkedBag<string>* bagPtr)
{
	cout << "The bag contains " << bagPtr->getCurrentSize() << " items: ";
	vector<string> bagItems = bagPtr->toVector();

	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
	{
		cout << bagItems[i] << " ";
	}  // end for

	cout << endl;
}  // end displayBag

void bagTester(LinkedBag<string>* bagPtr)
{
	string items[] = { "5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "5E", "5E" };
	string otherItems[] = { "1A", "5E", "3C", "2B", "4D" };

	cout << endl << "After adding 10 items to the bag" << endl;

	for (int i = 0; i < 10; i++)
		bagPtr->add(items[i]);

	displayBag(bagPtr);

	for (int i = 0; i < 5; i++)
	{
		bagPtr->remove(otherItems[i]);
		cout << endl << "After removing " << otherItems[i] << endl;
		displayBag(bagPtr);
	}
}  // end bagTester

void doQ3()
{
	char userChoice = ' ';

	while (toupper(userChoice) != 'X') {
		cout << "Enter 'A' to test the array-based implementation\n"
			<< " 'L' to test the link-based implementation or 'X' to exit: ";
		cin >> userChoice;

		if (toupper(userChoice) == 'A')
		{
			ArrayBag<string> bag;
			cout << endl << "Testing the Array-Based Bag:" << endl;
			cout << endl << "The initial bag is empty." << endl;
			bagTester(bag);
		}
		else
		{
			LinkedBag<string>* bagPtr = nullptr;
			bagPtr = new LinkedBag<string>();
			cout << "Testing the Link-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bagPtr);
			delete bagPtr;
			bagPtr = nullptr;
		}  // end if

		cout << endl << "All done!\n\n" << endl;
	}
}

// ================ Question 3 Ends Here ==================

// ============== Main Program Begins Here ================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1) {
		cout << endl;
		cout << "1. Recursive functions" << endl;
		cout << "2. Polynomial functions" << endl;
		cout << "3. Bag remove functions" << endl;
		input("Enter Question Number( 1 ~ 3 ) or 0 to Exit:", sNum);

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
		}
	}
}

// ============== Main Program Ends Here ================
