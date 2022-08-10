#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};

class ArrayPolynomial {
public:
	PolynomialTerm terms[MAX_TERMS];

	ArrayPolynomial()
	{
		for (int i = 0; i < MAX_TERMS; i++)
			terms[i].coef = terms[i].expo = 0;
	}

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}
	// 3 0 4 0 0 2 -3 3 3 3 4 5 6 7 0 0
	void inputTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int i = 0, t;

		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);		// 有幾項
		if (i == 0) {		// 陣列為空
			terms[0].coef = coef;
			terms[0].expo = expo;
			return;
		}

		// add your code here 
		if (coef == 0)return;
		for (t = 0; t <= i - 1; t++) {
			if (terms[t].expo < expo) {
				for (int x = i; x > t; x--) {
					terms[x].expo = terms[x - 1].expo;
					terms[x].coef = terms[x - 1].coef;
				}
				terms[t].expo = expo;
				terms[t].coef = coef;
				break;
			}
			else if (t == i - 1 && terms[t].expo > expo) {
				terms[t + 1].expo = expo;
				terms[t + 1].coef = coef;
			}
			else if(terms[t].expo == expo) {
				if (terms[t].coef + coef != 0) {
					terms[t].coef += coef;
					for (int z = t + 1; z < i - 1; z++) {
						terms[z].expo = terms[z + 1].expo;
						terms[z].coef = terms[z + 1].coef;
					}
					i--;
				}
				else {
					for (int z = t; z <= i-2; z++) {
						terms[z].expo = terms[z + 1].expo;
						terms[z].coef = terms[z + 1].coef;
					}
					terms[i - 1].expo = 0;
					terms[i - 1].coef = 0;
					i--;
				}
			}
		}
		return;
	}

	void printArrayBasedPoly()
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			cout << terms[0].coef;
		else
			cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				cout << " + " << terms[i].coef;
			else
				cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	void printArrayBasedPolyRecursively()
	{
			printArrayBasedPolyRecursively(0);
	}

	void printArrayBasedPolyRecursively(int i)
	{
		// add yor code here
		if (!terms[i].coef)return;
		if (i == 0) {
			if (terms[0].expo == 0)
				cout << terms[0].coef;
			else
				cout << terms[0].coef << "X^" << terms[0].expo;
		}
		else {
			if(terms[i].expo == 0)
				cout << " + " << terms[i].coef;
			else
				cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}
		printArrayBasedPolyRecursively(i + 1);
	}


	int computeRecursively(int x)
	{
		return computeRecursively(x, 0);
	}

	int computeRecursively(int x, int i)
	{
		// add yor code here
		int sum = 0;
		if (terms[i].coef == 0)return 0;
		sum = terms[i].coef * pow(x, terms[i].expo);
		return computeRecursively(x, i+1) + sum;
	}

	void copy(ArrayPolynomial &poly)
	{
		// add yor code here
		int i = 0;
		// PolynomialTerm copy;
		for (; poly.terms[i].coef != 0 && i < MAX_TERMS; i++);		// 有幾項
		for (int t = 0; t < i; t++) {
			terms[t].coef = poly.terms[t].coef;
			terms[t].expo = poly.terms[t].expo;
		}
	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm *polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm *tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		// add your code here 
		LinkedPolynomialTerm* tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = nullptr;

		// add your code here
		LinkedPolynomialTerm* prePtr = nullptr;
		LinkedPolynomialTerm* newPtr = polynomialTermPtr;
		if (coef == 0)return;
		if (polynomialTermPtr == nullptr)
			polynomialTermPtr = tmpPtr;
		else {
			while (newPtr->nextTermPtr != nullptr && newPtr->expo > expo) {
				prePtr = newPtr;
				newPtr = newPtr->nextTermPtr;
			}
			if (newPtr->expo < expo) {
				if (prePtr == nullptr) {
					//tmpPtr->nextTermPtr = newPtr;
					//newPtr = tmpPtr;
					polynomialTermPtr = tmpPtr;
					polynomialTermPtr->nextTermPtr = newPtr;
				}
				else {
					prePtr->nextTermPtr = tmpPtr;
					tmpPtr->nextTermPtr = newPtr;
				}
			}
			else if(newPtr->expo > expo){
				// 接在最後一項
				newPtr->nextTermPtr = tmpPtr;
			}
			else if (newPtr->expo == expo) {
				if (newPtr->coef + coef != 0) {
					newPtr->coef += coef;
					return;
				}
				else if (newPtr->coef + coef == 0) {
					if (prePtr != 0)
						prePtr->nextTermPtr = newPtr->nextTermPtr;
					else
						polynomialTermPtr = newPtr->nextTermPtr;
				}
			}
		}

		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr;

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
			if (termPtr->coef == 0)
				return;

			if (termPtr->expo == 0)
				cout << " + " << termPtr->coef;
			else
				cout << " + " << termPtr->coef << "X^" << termPtr->expo;

			termPtr = termPtr->nextTermPtr;
		}

		return;
	}

	void printLinkBasedPolyRecursively()
	{
			printLinkBasedPolyRecursively(polynomialTermPtr);
	}

	void printLinkBasedPolyRecursively(LinkedPolynomialTerm *currPtr)
	{
			// add yor code here
		if (currPtr == nullptr)return;
		if (currPtr->nextTermPtr == nullptr) {
			if (currPtr->expo == 0) {
				cout << currPtr->coef;
			}
			else {
				cout << currPtr->coef << "X^" << currPtr->expo;
			}
		}
		else {
			if (currPtr->expo == 0) {
				cout << currPtr->coef << " + ";
			}
			else {
				cout << currPtr->coef << "X^" << currPtr->expo << " + ";
			}
		}
		printLinkBasedPolyRecursively(currPtr->nextTermPtr);
	}

	int computeRecursively(int x)
	{
		return computeRecursively(x, polynomialTermPtr);
	}

	int computeRecursively(int x, LinkedPolynomialTerm *currPtr)
	{
		// add yor code here
		int sum = 0;
		if (currPtr == nullptr)return 0;
		sum = currPtr->coef * pow(x, currPtr->expo);
		return computeRecursively(x, currPtr->nextTermPtr) + sum;
	}

	void copy(LinkedPolynomial &poly)
	{
		polynomialTermPtr = poly.polynomialTermPtr;
		// add yor code here
		/*LinkedPolynomialTerm* aPtr = poly.polynomialTermPtr;
		LinkedPolynomialTerm* newPtr = new LinkedPolynomialTerm;
		if (poly.polynomialTermPtr == nullptr)return;
		while (aPtr->nextTermPtr != nullptr) {
			newPtr->coef = aPtr->coef;
			newPtr->expo = aPtr->expo;
			newPtr = newPtr->nextTermPtr;
			aPtr = aPtr->nextTermPtr;
		}
		polynomialTermPtr = newPtr;
		*/
	}
};
