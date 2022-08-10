// Class polynomial
#include <iostream>
#include <math.h>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm
{
public:
    int coef;
    int expo;
};

class ArrayPolynomial
{
public:
    PolynomialTerm terms[MAX_TERMS];

    void clear()
    {
        for (int i = 0; i < MAX_TERMS; i++)
        {
            terms[i].coef = 0;
            terms[i].expo = 0;
        }
        return;
    }

    void inputTerms(int coef, int expo)
    {
        for (int i = 0; i < MAX_TERMS; i++)
        {
            if (expo > terms[i].expo && coef != 0)
            {
                for (int x = MAX_TERMS - 1; x > i; x--)
                {
                    terms[x].expo = terms[x - 1].expo;
                    terms[x].coef = terms[x - 1].coef;
                }
                terms[i].expo = expo;
                terms[i].coef = coef;
                break;
            }
            else if (expo == terms[i].expo)
            {
                if (coef == 0)
                {
                    for (int x = i; x < MAX_TERMS - 1; x++)
                    {
                        terms[x].expo = terms[x + 1].expo;
                        terms[x].coef = terms[x + 1].coef;
                    }
                }
                else
                {
                    terms[i].expo = expo;
                    terms[i].coef = coef;
                }
                break;
            }
        }
        return;
    }

    void addArrayBasedPoly(ArrayPolynomial &a, ArrayPolynomial &b)
    {

        int cnt = 0, j = 0;

        for (int i = 0; i < MAX_TERMS; i++)
        {
            if (a.terms[i].coef == 0 && a.terms[i].expo == 0 && b.terms[j].coef == 0 && b.terms[j].expo == 0)
                break;
            if (a.terms[i].expo == b.terms[j].expo)
            {
                if (a.terms[i].coef + b.terms[j].coef != 0)
                {
                    terms[cnt].coef = a.terms[i].coef + b.terms[j].coef;
                    terms[cnt].expo = a.terms[i].expo;
                    cnt++;
                    j++;
                }
                else
                    j++;
            }
            else if (a.terms[i].expo < b.terms[j].expo)
            {
                while (a.terms[i].expo < b.terms[j].expo)
                {
                    terms[cnt].coef = b.terms[j].coef;
                    terms[cnt].expo = b.terms[j].expo;
                    cnt++;
                    j++;
                }
                if (a.terms[i].expo == b.terms[j].expo)
                {
                    if (a.terms[i].coef + b.terms[j].coef != 0)
                    {
                        terms[cnt].coef = a.terms[i].coef + b.terms[j].coef;
                        terms[cnt].expo = a.terms[i].expo;
                        cnt++;
                        j++;
                    }
                    else
                        j++;
                }
                else if (a.terms[i].expo > b.terms[j].expo)
                {
                    terms[cnt].expo = a.terms[i].expo;
                    terms[cnt].coef = a.terms[i].coef;
                    cnt++;
                }
            }
            else if (a.terms[i].expo > b.terms[j].expo)
            {
                terms[cnt].expo = a.terms[i].expo;
                terms[cnt].coef = a.terms[i].coef;
                cnt++;
            }
        }

        return;
    }

    void reverseArrayBasedPoly()
    {
        int n;
        for (n = 0; terms[n].coef != 0; n++)
            ;
        n--;
        PolynomialTerm t;
        for (int i = 0; i < n; i++, n--)
        {
            t = terms[i];
            terms[i] = terms[n];
            terms[n] = t;
        }
        return;
    }

    void printArrayBasedPoly() 
    {
        if (terms[0].coef == 0)
            return;
        else if (terms[0].coef == 0 && terms[0].expo == 0)
            return;

        if (terms[0].expo == 0)
            cout << terms[0].coef;
        else
            cout << terms[0].coef << "X^" << terms[0].expo;

        for (int i = 1; i < MAX_TERMS; i++)
        {
            if (terms[i].coef == 0)
                return;

            if (terms[i].expo == 0)
                cout << " + " << terms[i].coef;
            else
                cout << " + " << terms[i].coef << "X^" << terms[i].expo;
        }

        return;
    }

    int compute(int x)
    {
        int ans = 0;
        for (int t = 0; terms[t].coef != 0; t++)
            ans += terms[t].coef * pow(x, terms[t].expo);

        return ans;
    }
};

class LinkedPolynomialTerm
{
public:
    int coef;
    int expo;
    LinkedPolynomialTerm *nextTermPtr; /////
};                                       /////

class LinkPolynomial
{                                             /////
public:                                         /////
    LinkedPolynomialTerm *polynomialTermPtr; /////

    void clear() /////
    {
        LinkedPolynomialTerm *tmpPtr;

        while (polynomialTermPtr != nullptr)
        {
            tmpPtr = polynomialTermPtr;
            polynomialTermPtr = polynomialTermPtr->nextTermPtr;
            delete tmpPtr;
        }
        return;
    }

    void inputLinkTerms(int coef, int expo) /////
    {
        LinkedPolynomialTerm *tmpPtr, *nowPtr=nullptr, *prePtr, *delPtr;

        tmpPtr = new LinkedPolynomialTerm;
        tmpPtr->coef = coef;
        tmpPtr->expo = expo;

        nowPtr = polynomialTermPtr;
        prePtr = nullptr;
        if (coef == 0 && expo == 0)return;
        if (coef != 0)
        {
            while (nowPtr != nullptr && nowPtr->expo > expo)
            {
                if (nowPtr->expo != expo)
                {
                    prePtr = nowPtr;
                    nowPtr = nowPtr->nextTermPtr;
                }
            }

            if (nowPtr != nullptr && nowPtr->expo == expo)
                tmpPtr->nextTermPtr = nowPtr->nextTermPtr; //*important
            else
                tmpPtr->nextTermPtr = nowPtr;

            if (prePtr == nullptr)
                polynomialTermPtr = tmpPtr;
            else
                prePtr->nextTermPtr = tmpPtr;
        }
        else
        {
            while (nowPtr != nullptr)
            {
                if (nowPtr->expo == expo)
                {
                    if (prePtr == nullptr)
                    {
                        polynomialTermPtr = nowPtr->nextTermPtr;
                        delPtr = nowPtr;
                        nowPtr = nowPtr->nextTermPtr;
                    }
                    else
                    {
                        prePtr->nextTermPtr = nowPtr->nextTermPtr;
                        delPtr = nowPtr;
                        nowPtr = prePtr->nextTermPtr;
                    }

                    delete delPtr;
                }
                else
                {
                    prePtr = nowPtr;
                    nowPtr = nowPtr->nextTermPtr;
                }
            }
        }

        return;
    }

    void addLinkBasedPoly(LinkPolynomial &aPol, LinkPolynomial &bPol) /////
    {
        LinkedPolynomialTerm *dPtr = nullptr, *tailPtr = nullptr, *newnode;

        while (aPol.polynomialTermPtr != nullptr && bPol.polynomialTermPtr != nullptr)
        {

            newnode = new LinkedPolynomialTerm;
            newnode->nextTermPtr = NULL;

            if (aPol.polynomialTermPtr->expo == bPol.polynomialTermPtr->expo)
            {
                if (aPol.polynomialTermPtr->coef + bPol.polynomialTermPtr->coef != 0)
                {
                    newnode->coef = aPol.polynomialTermPtr->coef + bPol.polynomialTermPtr->coef;
                    newnode->expo = aPol.polynomialTermPtr->expo;
                    aPol.polynomialTermPtr = aPol.polynomialTermPtr->nextTermPtr;
                    bPol.polynomialTermPtr = bPol.polynomialTermPtr->nextTermPtr;
                }
                else
                {
                    aPol.polynomialTermPtr = aPol.polynomialTermPtr->nextTermPtr;
                    bPol.polynomialTermPtr = bPol.polynomialTermPtr->nextTermPtr;
                    delete newnode;
                    continue;
                }
            }
            else if (aPol.polynomialTermPtr->expo < bPol.polynomialTermPtr->expo)
            {
                newnode->coef = bPol.polynomialTermPtr->coef;
                newnode->expo = bPol.polynomialTermPtr->expo;
                bPol.polynomialTermPtr = bPol.polynomialTermPtr->nextTermPtr;
            }
            else if (aPol.polynomialTermPtr->expo > bPol.polynomialTermPtr->expo)
            {
                newnode->expo = aPol.polynomialTermPtr->expo;
                newnode->coef = aPol.polynomialTermPtr->coef;
                aPol.polynomialTermPtr = aPol.polynomialTermPtr->nextTermPtr;
            }
            if (polynomialTermPtr == nullptr)
            {
                polynomialTermPtr = newnode;
                tailPtr = polynomialTermPtr;
            }
            else
            {
                tailPtr->nextTermPtr = newnode;
                tailPtr = tailPtr->nextTermPtr;
            }
        }
        while (aPol.polynomialTermPtr != nullptr)
        {

            newnode = new LinkedPolynomialTerm;

            newnode->coef = aPol.polynomialTermPtr->coef;
            newnode->expo = aPol.polynomialTermPtr->expo;
            newnode->nextTermPtr = NULL;
            aPol.polynomialTermPtr = aPol.polynomialTermPtr->nextTermPtr;

            if (polynomialTermPtr == nullptr)
            {
                polynomialTermPtr = newnode;
                tailPtr = newnode;
            }
            else
            {
                tailPtr->nextTermPtr = newnode;
                tailPtr = tailPtr->nextTermPtr;
            }
        }
        while (bPol.polynomialTermPtr != nullptr)
        {

            newnode = new LinkedPolynomialTerm;

            newnode->coef = bPol.polynomialTermPtr->coef;
            newnode->expo = bPol.polynomialTermPtr->expo;
            newnode->nextTermPtr = NULL;
            bPol.polynomialTermPtr = bPol.polynomialTermPtr->nextTermPtr;

            if (polynomialTermPtr == nullptr)
            {
                polynomialTermPtr = newnode;
                tailPtr = newnode;
            }
            else
            {
                tailPtr->nextTermPtr = newnode;
                tailPtr = tailPtr->nextTermPtr;
            }
        }
        return;
    }

    void reverseLinkBasedPoly() /////
    {
        LinkedPolynomialTerm *nowPtr, *prePtr, *nextPtr;
        nowPtr = polynomialTermPtr;
        if (nowPtr == nullptr)return;
        nextPtr = nowPtr->nextTermPtr;
        prePtr = NULL;
        
        //if (nowPtr == 0 || nowPtr->nextTermPtr == 0)
            //return;

        while (nextPtr != nullptr)
        {
            nowPtr->nextTermPtr = prePtr;
            prePtr = nowPtr;
            nowPtr = nextPtr;
            nextPtr = nextPtr->nextTermPtr;
        }
        nowPtr->nextTermPtr = prePtr;
        polynomialTermPtr = nowPtr;

        return;
    }

    void printLinkBasedPoly() /////
    {
        LinkedPolynomialTerm *termPtr = polynomialTermPtr; /////

        if (termPtr == nullptr)
            return;

        if (termPtr->expo == 0)
            cout << termPtr->coef;
        else
            cout << termPtr->coef << "X^" << termPtr->expo;

        termPtr = termPtr->nextTermPtr;

        while (termPtr != nullptr)
        {
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

    int compute(int x)
    {
        int ans = 0;
        while (polynomialTermPtr != nullptr)
        {
            ans += polynomialTermPtr->coef * pow(x, polynomialTermPtr->expo);
            polynomialTermPtr = polynomialTermPtr->nextTermPtr;
        }
        return ans;
    }
};

int main()
{
    ArrayPolynomial a, b, d;         /////
    LinkPolynomial aPol, bPol, dPol; /////

    int coef, expo, x;
    aPol.polynomialTermPtr = nullptr;
    bPol.polynomialTermPtr = nullptr;
    dPol.polynomialTermPtr = nullptr;
    // aPtr = bPtr = dPtr = nullptr; /////

    while (1)
    {
        a.clear();
        b.clear();
        d.clear(); /////
                   // aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr); /////

        for (int i = 0; i < MAX_TERMS; i++)
        {
            cout << "\ninput a's coefficient and exponent: ";
            cin >> coef >> expo;

            if (expo == 0 && coef == 0)
                break;

            a.inputTerms(coef, expo);         /////
            aPol.inputLinkTerms(coef, expo); /////
        }

        cout << "\n\na = ";
        a.printArrayBasedPoly(); /////
        cout << "\na = ";
        aPol.printLinkBasedPoly(); /////
        cout << "\n";

        for (int i = 0; i < MAX_TERMS; i++)
        {
            cout << "\ninput b's coefficient and exponent: ";
            cin >> coef >> expo;

            if (expo == 0 && coef == 0)
                break;

            b.inputTerms(coef, expo);         /////
            bPol.inputLinkTerms(coef, expo); /////
        }

        cout << "\n\nb = ";
        b.printArrayBasedPoly(); /////

        cout << "\nb = ";
        bPol.printLinkBasedPoly(); /////

        cout << "\n";

        // d =a + b, where a, b, and d are polynomials

        d.addArrayBasedPoly(a, b); /////
        cout << "\na + b = ";
        d.printArrayBasedPoly(); /////

        dPol.addLinkBasedPoly(aPol, bPol); /////
        cout << "\na + b = ";
        dPol.printLinkBasedPoly(); /////

        cout << "\n";

        d.reverseArrayBasedPoly(); /////
        cout << "\nreversed d = ";
        d.printArrayBasedPoly(); /////

        dPol.reverseLinkBasedPoly(); /////
        cout << "\nreversed d = ";
        dPol.printLinkBasedPoly(); /////

        cout << "\n";

        cout << "\ninput X: ";
        cin >> x;

        cout << "\nd = ";
        cout << d.compute(x); //////

        cout << "\nd = ";
        cout << dPol.compute(x); //////

        cout << "\n";

        aPol.clear();
        bPol.clear();
        dPol.clear(); /////
    }

    return 0;
}
