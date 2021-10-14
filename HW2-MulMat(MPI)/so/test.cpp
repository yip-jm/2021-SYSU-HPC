/*
 * @Author: ye_jm
 * @Date: 2021.10.09
 * @E-mail: yejm6@mail2.sysu.edu.cn
 */

#include<bits/stdc++.h>
#include <dlfcn.h>
#include"mulmat.h"
using namespace std;
#define random(x) rand()%(x)
int o=0;

vector<int> createMatrix(int row, int col){
    vector<int>random_M;
    for(int i=0;i<row*col;i++){
        srand((int)time(0)+o);
        random_M.push_back(random(100));
        o++;
    }
    return random_M;
}

vector<int> NULLMatrix(int row, int col){
    vector<int>NULL_M;
    for(int i=0;i<row*col;i++){
        NULL_M.push_back(0);
    }
    return NULL_M;
}

void printMatrix(vector<int>&M, int row, int col){
    for(int i=0;i<row*col;i++){
        cout << M[i] << " ";
        if((i+1)%col==0)
        cout << left << endl;
    }
    cout << endl;
}

int main(){
    cout << "TO SHOW THE MATRICES M*N AND N*K" << endl;
    cout << "please input M N K: ";
    int m, n, k;
    cin >> m >> n >> k;
    cout << endl;

    vector<int>M1 = createMatrix(m,n);
    vector<int>M2 = createMatrix(n,k);
    vector<int>res = NULLMatrix(m,k);

    printMatrix(M1,m,n);
    printMatrix(M2,n,k);
    clock_t start, end;
    start = clock();
    mul_GEMM(M1,M2,res);
    printMatrix(res,m,k);
    end = clock();
    cout << "RUN TIME: " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;
    return 0;

}