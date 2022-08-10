//HW1_2
/*
2. 參考 http://notepad.yehyeh.net/Content/DS/CH04/3.php 的 Insert Node, Delete Node和 Display Linked List，撰寫一支具有輸入和刪除功能的程式。
i. 輸入功能：使用者每輸入一個整數，便將它按照由小到大的順序插入到Linked List中，然後將Linked List節點裡的值一一display到螢幕上。
ii. 刪除功能：使用者每輸入一個整數，便將Linked List所有相同數字的節點刪除；若List中無該數字，則不處理。最後將Linked List節點裡的值一一display到螢幕上。
例如：
Input or Delete? I
Input an integer? 3
3
Input or Delete? I
Input an integer? 2
2  3
Input or Delete? I
Input an integer? 5
2  3  5
Input or Delete? I
Input an integer? 4
2  3  4  5
Input or Delete? I
Input an integer? 1
1  2  3  4  5
Input or Delete? I
Input an integer? 3
1  2  3  4  5
Input or Delete? I
Input an integer? 3
1  2  3  3  4  5
Input or Delete? D
Delete which integer? 3
1  2  4  5
Input or Delete? D
Delete which integer? 3
1  2  4  5
Input or Delete? D
Delete which integer? 1
2  4  5
Input or Delete? D
Delete which integer? 5
2  4
*/
#include <stdio.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

typedef struct node{
    int value;
    struct node* nextnode;
}Node;

void printptr(Node* headptr){
    Node* tmpptr=headptr;
    while(tmpptr!=nullptr){
        cout << tmpptr->value <<" ";
        tmpptr=tmpptr->nextnode;
    }
    cout << "\n";
}

Node* insertptr(Node* headptr, int num){
    Node* nowptr=headptr, *newptr, *preptr=nullptr;
    newptr = (Node *)malloc(sizeof(Node));
    newptr->value=num;
    newptr->nextnode=nullptr;

    while(nowptr!=nullptr && nowptr->value<num){
            preptr=nowptr;
            nowptr=nowptr->nextnode;
    }
    
    if(headptr==nullptr){
        headptr=newptr;
    }else{
        if(preptr==nullptr)
            headptr=newptr;
        else
            preptr->nextnode=newptr;
        newptr->nextnode=nowptr;
    }
    return headptr;
}
Node* deleteptr(Node* headptr, int num){
    Node* nowptr=headptr, *delptr, *preptr=nullptr;
    
    if(headptr==nullptr)
        cout << "The string is null" << "\n";
    else{
        while(nowptr!=nullptr){
            if(nowptr->value==num){
                if(preptr==nullptr){
                    headptr=nowptr->nextnode;
                }else{
                    preptr->nextnode=nowptr->nextnode;
                }
            }
            else
                preptr=nowptr;
            nowptr=nowptr->nextnode; 
        }
    }
    return headptr;
}

int main(){
    char ans;
    int num;
    Node* headptr=nullptr;
    while(1){
        cout << "Input or delete? ";
        cin >> ans;
        if(ans=='I'||ans=='i'){
            cout << "Input an integer? ";
            cin >> num;
            headptr=insertptr(headptr, num);
        }else if(ans=='D'||ans=='d'){
            cout <<"Delete which integer? ";
            cin >> num;
            headptr=deleteptr(headptr, num);
        }
        printptr(headptr);
    }
}