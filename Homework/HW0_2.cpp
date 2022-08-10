//HW0_2
/*
2. 使用Array來存放資料，撰寫一支具有輸入數字和刪除數字功能的程式。
i. 輸入功能：使用者每輸入一個整數，便將它按照由小到大的順序插入到Array中，然後將Array裡儲存的值一一display到螢幕上。注意：必須直接插入到定位，不可插入後再來排序。
ii. 刪除功能：使用者每輸入一個整數，便將Array中所有相同數字的節點刪除；若Array中無該數字，則不處理。最後將Array裡儲存的值一一display到螢幕上。
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
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

int inputval(int val[], int len, int input){
    int i;
    for(i=0;i<len && val[i]<=input;i++);
    for(int j=len;j>i;j--)
        val[j]=val[j-1];
    val[i]=input;

    return len+1;
}

int deleteval(int val[],int len, int input){
    int i;
    for(i=0;i<len;){
        if(val[i]==input){
            for(int t=i;t<len;t++){
                val[t]=val[t+1];
            }
            len--;
        }
        else i++;
    }
    return len;
}
int display(int val[], int len){
    for(int t=0;t<len;t++){
        cout << val[t] <<" ";
    }
    cout << "\n";
}

int main(){

    char ans;
    int input, val[20], len=0;

    while(1){
        cout << "Input or delete? ";
        cin >> ans;

        if(ans == 'I' || ans == 'i'){
            cout <<"Input an integer: ";
            cin >> input;
            len=inputval(val,len, input);
        }else if (ans == 'D' || ans == 'd'){
            cout <<"Delete which integer: ";
            cin >> input;
            len=deleteval(val,len, input);
        }else if (ans == 'X' || ans == 'x'){
            break;
        }
        display(val, len);
    }

    return 0;
}