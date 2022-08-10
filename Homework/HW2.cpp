#include <stdio.h>
#include <memory.h>
#include <iostream>
using namespace std;

#define MAX_degree 100 /*MAX degree of polynomial+1*/

typedef struct {
	int degree;
	int coef[MAX_degree];
} polynomial;

#define MAX_TERMS 20 /*size of terms array*/
typedef struct {
	int coef;
	int expo;
} polynomial_term;

polynomial_term terms[MAX_TERMS];
int avail = 0;

polynomial Zero(polynomial p)
{
	memset(&p, 0, sizeof(p));

	return p;
}

int IsZero(polynomial p)//找0多項式
{
	for (int i = 0; i <= p.degree; i++) {
		if (p.coef[i] != 0)
			return false;
	}
	return true;

}

int Lead_Exp(polynomial p)
{
	return p.degree;
}

int COMPARE(int i, int j)//大小判斷
{
	if (i > j)
		return 1;
	else if (i == j)
		return 0;
	else
		return -1;
}

int Coef(polynomial p, int expo)
{
	return p.coef[expo];
}

polynomial Attach(polynomial p, int coef, int expo)//冪次存入
{
	p.coef[expo] = coef;
	if (expo > p.degree)
		p.degree = expo;
	return p;
}

polynomial Remove(polynomial p, int expo)//冪次移除
{
	p.coef[expo] = 0;
	for (int i = p.degree; i >= 0; i--) {
		if (p.coef[i] != 0) {
			p.degree = i;
			break;
		}
	}
	return p;
}

void attach(int coef, int expo)
{
	if (avail >= MAX_TERMS)
		return;

	terms[avail].coef = coef;
	terms[avail++].expo = expo;
}

void PrintPoly1(polynomial p)
{
	for (int i = p.degree; i >= 0; i--) {
		if (p.coef[i] != 0) {
			if (p.degree == i) {
				if (i == 0)
					printf("%d", p.coef[i]);
				else
					printf("%dX^%d", p.coef[i], i);
			}
			else {
				if (i == 0)
					printf(" + %d", p.coef[i]);
				else
					printf(" + %dX^%d", p.coef[i], i);
			}
		}
	}
}

void PrintPoly2(polynomial_term t[], int start, int finish)//顯示
{
	for (int i = start; i < finish; i++) {
		for (int j = i + 1; j <= finish; j++) {
			polynomial_term temp;
			if (t[i].expo < t[j].expo) {
				temp = t[i];
				t[i] = t[j];
				t[j] = temp;
			}
		}
	}

	for (int i = start; i <= finish; i++) {
		if (t[i].expo != 0)
			printf("%dX^%d", t[i].coef, t[i].expo);
		if (t[i].expo == 0)
			printf("%d", t[i].coef);
		if (i != finish)
			printf(" + ");

	}
}

polynomial padd1(polynomial p1, polynomial p2)
{
	polynomial p3;
	int sum;

	p3.degree = 0;
	p3 = Zero(p3);

	while (!IsZero(p1) && !IsZero(p2)) {
		switch (COMPARE(Lead_Exp(p1), Lead_Exp(p2))) {
		case -1:
			p3 = Attach(p3, Coef(p2, Lead_Exp(p2)), Lead_Exp(p2));
			p2 = Remove(p2, Lead_Exp(p2));
			break;
		case  0:
			sum = Coef(p1, Lead_Exp(p1)) + Coef(p2, Lead_Exp(p2));

			if (sum)
				p3 = Attach(p3, sum, Lead_Exp(p1));

			p1 = Remove(p1, Lead_Exp(p1));
			p2 = Remove(p2, Lead_Exp(p2));
			break;
		case 1:
			p3 = Attach(p3, Coef(p1, Lead_Exp(p1)), Lead_Exp(p1));
			p1 = Remove(p1, Lead_Exp(p1));
		}
	}

	while (!IsZero(p1)) {
		p3 = Attach(p3, Coef(p1, Lead_Exp(p1)), Lead_Exp(p1));
		p1 = Remove(p1, Lead_Exp(p1));
	}
	while (!IsZero(p2)) {
		p3 = Attach(p3, Coef(p2, Lead_Exp(p2)), Lead_Exp(p2));
		p2 = Remove(p2, Lead_Exp(p2));
	}

	return p3;
}

void padd2(int starta, int finisha, int startb, int finishb, int* startd, int* finishd)
{
	int sum;

	*startd = avail;

	while (starta <= finisha && startb <= finishb) {
		switch (COMPARE(terms[starta].expo, terms[startb].expo)) {
		case -1:
			attach(terms[startb].coef, terms[startb].expo);
			startb++;
			break;
		case  0:
			sum = terms[starta].coef + terms[startb].coef;

			if (sum)
				attach(sum, terms[starta].expo);
			starta++;
			startb++;
			break;
		case 1:
			attach(terms[starta].coef, terms[starta].expo);
			starta++;
		}
	}

	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expo);
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expo);

	*finishd = avail - 1;
}

int main()
{
	polynomial a, b, d;
	int coef, expo, sum;

	int starta = 0, finisha, startb, finishb, startd, finishd;

	memset(terms, 0, sizeof(terms));

	a.degree = b.degree = d.degree = 0;

	a = Zero(a);
	b = Zero(b);
	d = Zero(d);

	while (1) {
		printf("\ninput a's coefficient and exponent: ");
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		a.coef[expo] = coef;

		if (a.degree < expo)
			a.degree = expo;

		terms[avail].coef = coef;
		terms[avail].expo = expo;
		avail++;
	}

	finisha = avail - 1;
	startb = avail;

	printf("\n\na = ");
	PrintPoly1(a);
	printf("\na = ");
	PrintPoly2(terms, starta, finisha);
	printf("\n");

	while (1) {
		printf("\ninput b's coefficient and exponent: ");
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		b.coef[expo] = coef;

		if (b.degree < expo)
			b.degree = expo;

		terms[avail].coef = coef;
		terms[avail].expo = expo;
		avail++;
	}

	finishb = avail - 1;

	printf("\n\nb = ");
	PrintPoly1(b);
	printf("\nb = ");
	PrintPoly2(terms, startb, finishb);

	/* d =a + b, where a, b, and d are polynomials */

	d = padd1(a, b);
	printf("\n\nd = ");
	PrintPoly1(d);

	padd2(starta, finisha, startb, finishb, &startd, &finishd);
	printf("\nd = ");
	PrintPoly2(terms, startd, finishd);

	return 0;
}
