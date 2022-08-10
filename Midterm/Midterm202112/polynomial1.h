#include <stdio.h>
//#include "stdafx.h"
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
		clear();
	}

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputArrayBasedTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int i = 0;

		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);

		for (int j = 0; j <= i; j++) {
			if (terms[j].coef == 0) {
				//printf("success\n");
				terms[j].coef = coef;
				terms[j].expo = expo;
				return;
			}
			if (terms[j].expo == expo) {
				if (coef == 0) return;

				if (coef < terms[j].coef) {
					for (int s = i; s > j; s--) {
						terms[s] = terms[s - 1];
					}
					terms[j].coef = coef;
					terms[j].expo = expo;
					return;
				}
			}
			else if (terms[j].expo > expo) {
				if (coef == 0) return;
				for (int s = i; s > j; s--) {
					terms[s] = terms[s - 1];
				}
				terms[j].coef = coef;
				terms[j].expo = expo;
				return;
			}
		}


		// add your code here 


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


	void reverseArrayBasedCopy(ArrayPolynomial &poly)
	{
		int i = 0, s = 0;
		for (; poly.terms[i].coef != 0 && i < MAX_TERMS; i++);
		/*printf("\n %d \n", i);
		int coef[i] = {0}, expo[i] = {0};
		

		for (int j = i; j > 0; j--) {
			coef[s] = poly.terms[j - 1].coef;
			expo[s] = poly.terms[j - 1].expo;
			s++;
		}

		for (int c = 0; c < i; c++) {
			terms[c].coef = coef[c];
			terms[c].expo = expo[c];
		}*/

		return;
	}

	void insertArrayBasedTerm(int coef, int expo)
	{
		int i = 0, sum = coef;
		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);

		int j = 0;
		for (; j < i; j++) {
			if (terms[j].expo == expo) {
				terms[j].coef += coef;
				break;
			}
		}

		for (int c = j; c < i - 1; c++) {
			if (terms[c].expo == terms[c + 1].expo) {
				terms[c].coef += terms[c + 1].coef;
				for (int s = c + 1; s < i - 1; s++) {
					terms[s] = terms[s + 1];
				}
				terms[i - 1].coef = 0;
				terms[i - 1].expo = 0;
				i--;
				c--;
			}
		}

		// add yor code here

		return;
	}

	void removeArrayBasedTerm(int expo)
	{
		int i = 0;
		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);

		for (int j = 0; j < i; j++) {
			if (terms[j].expo == expo) {
				for (int c = j; c < i - 1; c++) {
					terms[c] = terms[c + 1];
				}
				terms[i-1].coef = 0;
				terms[i-1].expo = 0;
				i--;
				j--;
			}
		}
		return;

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

	void inputLinkBasedTerms(int coef, int expo)
	{
		LinkedPolynomialTerm *tmpPtr;
		LinkedPolynomialTerm* current = polynomialTermPtr;
		LinkedPolynomialTerm* prev = nullptr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = nullptr;

		if (current == nullptr) {
			if (coef == 0) return;
			polynomialTermPtr = tmpPtr;
			return;
		}
		else {
			while (current != nullptr) {
				if (current->expo == tmpPtr->expo && current->coef > tmpPtr->coef) {
					if (tmpPtr->coef == 0)return;

					if (prev == nullptr) {
						tmpPtr->nextTermPtr = current;
						polynomialTermPtr = tmpPtr;
						return;
					}
					else {
						tmpPtr->nextTermPtr = current;
						prev->nextTermPtr = tmpPtr;
						return;
					}
				}
				else if (current->expo > tmpPtr->expo) {
					if (tmpPtr->coef == 0) return;

					if (prev == nullptr) {
						tmpPtr->nextTermPtr = current;
						polynomialTermPtr = tmpPtr;
						return;
					}
					else {
						tmpPtr->nextTermPtr = current;
						prev->nextTermPtr = tmpPtr;
						return;
					}
				}
				prev = current;
				current = current->nextTermPtr;
			}
			if (tmpPtr->coef == 0) return;
			prev->nextTermPtr = tmpPtr;
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

	void reverseLinkBasedCopy(LinkedPolynomial &poly)
	{
		if (polynomialTermPtr == nullptr) return;
		LinkedPolynomialTerm* First = polynomialTermPtr;
		LinkedPolynomialTerm* current = polynomialTermPtr->nextTermPtr;
		LinkedPolynomialTerm* prev = polynomialTermPtr;

		while (current != nullptr) {
			prev->nextTermPtr = current->nextTermPtr;
			current->nextTermPtr = prev;
			First = current;
			current = prev->nextTermPtr;
		}


	}

	void insertLinkBasedTerm(int coef, int expo)
	{
		LinkedPolynomialTerm* current = polynomialTermPtr;
		LinkedPolynomialTerm* prev = nullptr;

		while (current != nullptr) {
			if (current->expo == expo) {
				current->coef += coef;
				break;
			}
			prev = current;
			current = current->nextTermPtr;
		}

		while (current != nullptr) {
			if (current->expo != current->nextTermPtr->expo) break;

			if (current->expo == current->nextTermPtr->expo) {
				current->coef += current->nextTermPtr->coef;
				current->nextTermPtr = current->nextTermPtr->nextTermPtr;
			}
		}
		// add yor code here


	}

	void removeLinkBasedTerm(int expo)
	{
		LinkedPolynomialTerm* current = polynomialTermPtr;
		LinkedPolynomialTerm* prev = nullptr;

		while (current != nullptr) {
			if (current->expo == expo) {
				if (prev == nullptr) {
					current = current->nextTermPtr;
					polynomialTermPtr = current;
				}
				else {
					prev->nextTermPtr = current->nextTermPtr;
					current = current->nextTermPtr;
				}
				continue;
			}
			prev = current;
			current = current->nextTermPtr;
		}
		return;
	}
};
