/*
 * @Author: ye_jm
 * @Date: 2021.09.14
 * @E-mail: yejm6@mail2.sysu.edu.cn
 */

#include<bits/stdc++.h>
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

void printMatrix(vector<int>&M, int row, int col){
    for(int i=0;i<row*col;i++){
        cout << M[i] << " ";
        if((i+1)%col==0)
        cout << left << endl;
    }
    cout << endl;
}

vector<int> mul_GEMM(vector<int>&M1, vector<int>&M2,int m,int n,int k){
    vector<int>res;
    int sum;
    for(int i=0;i<m*k;i++){
        sum=0;
        for(int j=0,p=i/k*n;j<n;j++,p++){
            sum += M1[p]*M2[i%k+j*k];
        }
        res.push_back(sum);
    }
    return res;
    
}
int main(){
    cout << "TO SHOW THE MATRICES M*N AND N*K" << endl;
    cout << "please input M N K: ";
    int m, n, k;
    cin >> m >> n >> k;
    cout << endl;

    vector<int>M1 = createMatrix(m,n);
    vector<int>M2 = createMatrix(n,k);

    // printMatrix(M1,m,n);
    // printMatrix(M2,n,k);
    clock_t start, end;
    start = clock();
    vector<int>res = mul_GEMM(M1,M2,m,n,k);
    // printMatrix(res,m,k);
    end = clock();
    cout << "RUN TIME: " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;
    return 0;
}