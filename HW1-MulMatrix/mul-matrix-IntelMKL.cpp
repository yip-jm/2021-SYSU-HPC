/*
 * @Author: ye_jm
 * @Date: 2021.09.18
 * @E-mail: yejm6@mail2.sysu.edu.cn
 */
//编译命令：g++ -o mul-matrix-IntelMKL mul-matrix-IntelMKL.cpp -lmkl_rt
#include<bits/stdc++.h>
#include"mkl.h"
using namespace std;
#define random(x) rand()%(x)
int o=0;

void createMatrix(float*M, int row, int col){
    for(int i=0;i<row*col;i++){
        srand((int)time(0)+o);
        M[i] = random(100);
        o++;
    }
}


void printMatrix(float *M, int row, int col){
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
    
    float *A, *B, *C;
    A = (float *)mkl_malloc(m*n*sizeof(float), 64);
    B = (float *)mkl_malloc(n*k*sizeof(float), 64);
    C = (float *)mkl_malloc(m*k*sizeof(float), 64);

    int ld1 , lda2, ld3;
    int alpha=1, beta = 0;
    int col_a = n;
    int col_b = k;
    int col_c = k;

    CBLAS_TRANSPOSE transA = CblasNoTrans;
	CBLAS_TRANSPOSE transB = CblasNoTrans;

    createMatrix(A,m,n);
    createMatrix(B,n,k);

    // printMatrix(A,m,n);
    // printMatrix(B,n,k);
    clock_t start, end;
    start = clock();
    cblas_sgemm(CblasRowMajor,transA,transB,m,k,n,alpha,A,col_a,B,col_b,beta,C,col_c);
    end = clock();

    // printMatrix(C,m,k);
    cout << "RUN TIME: " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;
    
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);    
    return 0;
}
