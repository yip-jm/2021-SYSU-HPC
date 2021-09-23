/*
 * @Author: ye_jm
 * @Date: 2021.09.14
 * @E-mail: yejm6@mail2.sysu.edu.cn
 */

#include<bits/stdc++.h>
using namespace std;
#define random(x) rand()%(x)
int o=0;

void createMatrix(int row,int col, int **M){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            srand(time(0)+o);
            M[i][j] = random(100);
            o++;
        }
    }
}

void printMatrix(int row, int col, int **matrix){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void mul_ChangeOrder(int m, int n, int k, int **M1, int **M2, int **M3){
    for(int t=0;t<n;t++){
        for(int i=0;i<m;i++){
            int tmp = M1[i][t];
            for(int j=0;j<k;j++){
                M3[i][j] += tmp*M2[t][j];
            }
        }
    }
}


int main(){
    cout << "TO SHOW THE MATRICES M*N AND N*K" << endl;
    cout << "please input M N K: ";
    int m, n, k;
    cin >> m >> n >> k;
    cout << endl;

    int **M1 = new int *[m];
    int **M2 = new int *[n];
    int **M3 = new int *[m];
    for(int i=0;i<m;i++){
        M1[i] = new int [n];
        M3[i] = new int [k];
    }
    for(int i=0;i<k;i++){
        M2[i] = new int [k];
    }

    createMatrix(m,n,M1);
    createMatrix(n,k,M2);
    // printMatrix(m,n,M1);
    // printMatrix(n,k,M2);

    clock_t start, end;
    start = clock();
    mul_ChangeOrder(m,n,k,M1,M2,M3);
    // printMatrix(m,k,M3);
    end = clock();
    cout << "RUN TIME: " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;


    
}