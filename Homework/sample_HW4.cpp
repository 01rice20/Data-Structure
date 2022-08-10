// HW4.cpp : 定義主控台應用程式的進入點。
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm* nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm*& polynomialTermPtr)
{
	linkedPolynomialTerm* tmpPtr;

	while (polynomialTermPtr != nullptr) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm t[], int coef, int expo)
{

	int j, len;

	if (t[0].coef == 0)
	{
		t[0].expo = expo;
		t[0].coef = coef;
	}
	else
	{
		for (int i = 0;;i++)
		{
			if (t[i].expo == expo)
			{
				if (coef == 0)
				{
					for (len = 0;t[len].expo != 0;len++);
					for (int u = i;u < len;u++)
					{
						t[u].expo = t[u + 1].expo;
						t[u].coef = t[u + 1].coef;
					}
					break;
				}
				else
				{
					t[i].expo = expo;
					t[i].coef = coef;
					break;
				}

			}
			if (t[i].expo == 0)
			{
				if (coef == 0)
					break;
				t[i].expo = expo;
				t[i].coef = coef;
				break;
			}
			if (expo > t[i].expo && coef != 0)
			{
				for (j = i;t[j].expo != 0;j++);   //i是第幾位遇到 j是包含i之後的個數
				for (int k = j; k > 0; k--)
				{
					t[k + i].expo = t[k + i - 1].expo;
					t[k + i].coef = t[k + i - 1].coef;

				}
				t[i].expo = expo;
				t[i].coef = coef;
				break;
			}
		}
	}
	return;
}

void inputLinkTerms(linkedPolynomialTerm*& polyPtr, int coef, int expo)
{
	linkedPolynomialTerm* tmpPtr, * nowPtr, * prePtr, *delPtr;
	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef;
	tmpPtr->expo = expo;

	nowPtr = polyPtr;
	prePtr = nullptr;
	if (coef != 0)//係數!=0
	{
		while (nowPtr != nullptr && nowPtr->expo > expo) {
			if (nowPtr->expo != expo)
			{
				prePtr = nowPtr;
				nowPtr = nowPtr->nextTermPtr;
			}
		}


		if (nowPtr != nullptr && nowPtr->expo == expo)
			tmpPtr->nextTermPtr = nowPtr->nextTermPtr;
		else
			tmpPtr->nextTermPtr = nowPtr;
		



		if (prePtr == nullptr)
			polyPtr = tmpPtr;
		else
			prePtr->nextTermPtr = tmpPtr;

	}
	else
	{
		while (nowPtr != nullptr) {
			if (nowPtr->expo == expo) {
				if (prePtr == nullptr) {
					polyPtr = nowPtr->nextTermPtr;
					delPtr = nowPtr;
					nowPtr = nowPtr->nextTermPtr;
				}
				else {
					prePtr->nextTermPtr = nowPtr->nextTermPtr;
					delPtr = nowPtr;
					nowPtr = prePtr->nextTermPtr;
				}

				delete delPtr;
			}
			else {
				prePtr = nowPtr;
				nowPtr = nowPtr->nextTermPtr;
			}
		}
	}

	return;
}


void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
	int ia = 0, ib = 0, id = 0;
	//A和B各抓一個數字，次方小的進去D，從AorB補 直到AB都放完
	while (1)
	{
		if (a[ia].expo == 0 && a[ia].coef == 0)
		{
			for (int i = ib;b[i].coef != 0;i++, id++)
				d[id] = b[i];
			break;
		}
		if (b[ib].expo == 0 && b[ib].coef == 0)
		{
			for (int i = ia;a[i].coef != 0;i++, id++)
				d[id] = a[i];
			break;
		}
		//
		if (a[ia].expo > b[ib].expo)
		{
			d[id].expo = a[ia].expo;
			d[id].coef = a[ia].coef;
			ia++;
			id++;

		}
		else if (a[ia].expo == b[ib].expo)
		{
			if (a[ia].coef + b[ib].coef != 0)
			{
				d[id].expo = a[ia].expo;
				d[id].coef = a[ia].coef + b[ib].coef;
				id++;
			}
			ia++;
			ib++;
		}
		else
		{
			d[id].expo = b[ib].expo;
			d[id].coef = b[ib].coef;
			ib++;
			id++;
		}

	}
	return;
}

linkedPolynomialTerm* addLinkBasedPoly(linkedPolynomialTerm* aPtr, linkedPolynomialTerm* bPtr)
{
	linkedPolynomialTerm* dPtr = nullptr, *dataPtr = nullptr,*savePtr;
	savePtr = new linkedPolynomialTerm;
	while (1)
	{
		if (aPtr == nullptr && bPtr != nullptr)
		{
			while (bPtr != nullptr)
			{
				savePtr = new linkedPolynomialTerm;
				savePtr->expo = bPtr->expo;
				savePtr->coef = bPtr->coef;
				savePtr->nextTermPtr = nullptr;
				if (dataPtr == nullptr)
				{
					dataPtr = savePtr;
					dPtr = dataPtr; 
				}
				else
				{
					dataPtr->nextTermPtr = savePtr;
					dataPtr = dataPtr->nextTermPtr;
				}
				/*dataPtr->nextTermPtr = savePtr;
				dataPtr = dataPtr->nextTermPtr;*/
				bPtr = bPtr->nextTermPtr;
			}
			
			break;
		}
		if (bPtr == nullptr && aPtr != nullptr)
		{
			while (aPtr != nullptr)
			{
				savePtr = new linkedPolynomialTerm;
				savePtr->expo = aPtr->expo;
				savePtr->coef = aPtr->coef;
				savePtr->nextTermPtr = nullptr;
				if (dataPtr == nullptr)
				{
					dataPtr = savePtr;
					dPtr = dataPtr;
				}
				else
				{
					dataPtr->nextTermPtr = savePtr;
					dataPtr = dataPtr->nextTermPtr;
				}
				aPtr = aPtr->nextTermPtr;
			}

			break;
		}
		if (aPtr == nullptr && bPtr == nullptr)break;
		if (aPtr -> expo > bPtr -> expo)
			{
				savePtr = new linkedPolynomialTerm;
				savePtr -> expo = aPtr->expo;
				savePtr -> coef = aPtr->coef;
				savePtr -> nextTermPtr = nullptr;
				if (dataPtr == nullptr)
				{
					dataPtr = savePtr;
					dPtr = dataPtr;
				}
				else
				{
					dataPtr->nextTermPtr = savePtr;
					dataPtr = dataPtr->nextTermPtr;
				}
				aPtr = aPtr->nextTermPtr;
				
		}
		else if (aPtr->expo == bPtr->expo)
		{
			if (aPtr->coef + bPtr->coef == 0)
			{
				aPtr = aPtr->nextTermPtr;
				bPtr = bPtr->nextTermPtr;
			}
			else
			{
				savePtr = new linkedPolynomialTerm;
				savePtr->expo = aPtr->expo;
				savePtr->coef = aPtr->coef + bPtr->coef;
				savePtr->nextTermPtr = nullptr;
				if (dataPtr == nullptr)
				{
					dataPtr = savePtr;
					dPtr = dataPtr;
				}
				else
				{
					dataPtr->nextTermPtr = savePtr;
					dataPtr = dataPtr->nextTermPtr;
				}
				aPtr = aPtr->nextTermPtr;
				bPtr = bPtr->nextTermPtr;
			}
		}
		else
		{
				savePtr = new linkedPolynomialTerm;
				savePtr->expo = bPtr->expo;
				savePtr->coef = bPtr->coef;
				savePtr->nextTermPtr = nullptr;
				if (dataPtr == nullptr)
				{
					dataPtr = savePtr;
					dPtr = dataPtr;
				}
				else
				{
					dataPtr->nextTermPtr = savePtr;
					dataPtr = dataPtr->nextTermPtr;
				}
				bPtr = bPtr->nextTermPtr;
		}
		
	}
	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
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
}

void printLinkBasedPoly(linkedPolynomialTerm* polyPtr)
{
	linkedPolynomialTerm* termPtr = polyPtr;

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
}

int main(int argc, char* argv[]) 
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm* aPtr, * bPtr, * dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear(a); clear(b); clear(d);
		clear(aPtr); clear(bPtr); clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(a, coef, expo);
			inputLinkTerms(aPtr, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\na = ";
		printLinkBasedPoly(aPtr);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(b, coef, expo);
			inputLinkTerms(bPtr, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);

		cout << "\nb = ";
		printLinkBasedPoly(bPtr);

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);

		dPtr = addLinkBasedPoly(aPtr, bPtr);
		cout << "\na + b = ";
		printLinkBasedPoly(dPtr);

		cout << "\n";
	}
	return 0;
}
