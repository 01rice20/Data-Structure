// HW4p
/*
參考附件檔 HW4.cpp，使用 link-based polynomials 來撰寫多項式加法運算。
1. 你必須撰寫 inputLinkTerms(...)，使其可以不需按照降冪的順序輸入係數，卻會按降冪的順序存入 link-based polynomials。若相同的冪次重覆輸入，則以最後輸入的係數為主。
<<注意>>輸入係數存入 link-based polynomial 時，需一次就放到定位，不可以先存入，然後使用 sorting 方法排序。
2. 你必須撰寫 addLinkBasedPoly(...)，使其可以將傳入的兩個 link-based polynomials 相加所得到的第三個 link-based polynomial 的指標回傳 。
<<注意>>輸入係數可以是負數。
*/

#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct{
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm *nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm *&polynomialTermPtr) 
{
	linkedPolynomialTerm *tmpPtr;

	while ( polynomialTermPtr != nullptr ) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
{

	// add your code here

	return;
}

void inputLinkTerms(linkedPolynomialTerm *&polyPtr, int coef, int expo)
{
	linkedPolynomialTerm *tmpPtr;

	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef ;
	tmpPtr->expo = expo;


	// add your code here 


	return;
}


void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{

	// add your code here

	return;
}

linkedPolynomialTerm *addLinkBasedPoly(linkedPolynomialTerm *aPtr, linkedPolynomialTerm *bPtr)
{
	linkedPolynomialTerm *dPtr = nullptr;


	// add your code here


	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if ( terms[0].coef == 0 ) 
		return;

	if ( terms[0].expo == 0 )
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) {
		if ( terms[i].coef == 0 ) 
			return;

		if ( terms[i].expo == 0 )
			cout << " + " << terms[i].coef;
		else
			cout << " + "<< terms[i].coef  << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm *polyPtr)
{
	linkedPolynomialTerm *termPtr =  polyPtr;

	if ( termPtr  == nullptr )
			return;

	if ( termPtr->expo == 0 )
		cout << termPtr->coef;
	else
		cout << termPtr->coef << "X^" << termPtr->expo;

	termPtr  = termPtr->nextTermPtr;
	
	while ( termPtr  != nullptr ) {
		if ( termPtr->coef == 0 ) 
			return;

		if ( termPtr->expo == 0 )
			cout << " + " << termPtr->coef;
		else
			cout << " + "<< termPtr->coef  << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;
	}
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm *aPtr, *bPtr, *dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear( a ); clear( b ); clear( d );
		clear( aPtr ); clear( bPtr ); clear( dPtr );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( a, coef, expo );
			inputLinkTerms( aPtr, coef, expo );
		}

		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\na = ";
		printLinkBasedPoly( aPtr );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( b, coef, expo );
			inputLinkTerms( bPtr, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );

		cout << "\nb = ";
		printLinkBasedPoly( bPtr );

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		
		dPtr = addLinkBasedPoly( aPtr, bPtr );
		cout << "\na + b = ";
		printLinkBasedPoly( dPtr );

		cout << "\n";
	}
	return 0;
}
 