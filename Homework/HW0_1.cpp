//HW0_1
/*
1. 參考附件檔 HW0.cpp(此次作業所需的程式檔，可編譯執行，但功能並不完全)，撰寫底下的函式。
   i. printArrayForward(...)：運用疊代(iteration)的方式，將Array裡的數字順向輸出到螢幕。
   ii. printArrayBackward(...)：運用遞迴(recursion)的方式，將陣列裡的數字反向輸出到螢幕。
   iii. printListForward(...)：運用疊代(iteration)的方式，將List裡的數字順向輸出到螢幕。
   iv. printListBackward(...)：運用遞迴(recursion)的方式，將List裡的數字反向輸出到螢幕。
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX 5

struct Node
{
    int item;
    Node *next;
};

typedef Node *nodePtr;

Node *inputData(int num, nodePtr headPtr)
{
    nodePtr currentPtr = headPtr;

    nodePtr tmpPtr = (nodePtr)malloc(sizeof(Node));
    tmpPtr->item = num;
    tmpPtr->next = NULL;

    if (headPtr == NULL)
        return tmpPtr;
    else
    {
        while (currentPtr->next != NULL)
            currentPtr = currentPtr->next;

        currentPtr->next = tmpPtr;

        return headPtr;
    }
}

void printArrayForward(int A[])
{
    // add your code here

    for(int t=0;t<5;t++){
        cout << A[t] << " ";
    }
}

void printArrayBackward(int A[], int i)
{
    // add your code here

    if(i==5)
        return;
    else{
        printArrayBackward(A, i+1);
        cout << A[i] << " ";
    }
   
}

void printListForward(nodePtr ptr)
{
    // add your code here
   
    nodePtr currentPtr = ptr;
    while(currentPtr!=nullptr){
        cout << currentPtr->item << " ";
        currentPtr = currentPtr->next;
    }
}

void printListBackward(nodePtr ptr)
{
    // add your code here

    nodePtr currentPtr = ptr;
    if(currentPtr == nullptr)
        return;
    else{
        printListBackward(ptr->next);
        cout << currentPtr->item << " ";
    }
}

int main()
{
    int num;
    int A[MAX] = {0};
    nodePtr headPtr = NULL;

    printf("Input %d numbers: ", MAX);

    for (int i = 0; i < MAX; i++)
    {
        cin >> num;
        A[i] = num;
        headPtr = inputData(num, headPtr);
    }

    printf("\nArray Forward Iteratively:  ");
    printArrayForward(A);
    printf("\nArray Backward Recursively: ");
    printArrayBackward(A, 0);

    printf("\nList Forward Iteratively:  ");
    printListForward(headPtr);
    printf("\nList Backward Recursively: ");
    printListBackward(headPtr);

    printf("\n");
    return 0;
}
