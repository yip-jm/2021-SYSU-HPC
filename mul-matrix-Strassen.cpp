/*
 * @Author: ye_jm
 * @Date: 2021.09.16
 * @E-mail: yejm6@mail2.sysu.edu.cn
 */

#include<bits/stdc++.h>
using namespace std;
#define random(x) rand()%(x)
int o=0;

void createMatrix(int m, int **M){
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            srand(time(0)+o);
            M[i][j] = random(100);
            o++;
        }
    }
}

void printMatrix(int m, int **matrix){
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void mul_GEMM(int n,int **leftM, int **rigM, int **resM){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                resM[i][j] += leftM[i][k]*rigM[k][j];
            }
        }
    }
}

void addMatrix(int n,int **leftM,int **rigM, int **resM){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            resM[i][j] = leftM[i][j]+rigM[i][j];
        }
    }
}

void subMatrix(int n,int **leftM,int **rigM, int **resM){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            resM[i][j] = leftM[i][j]-rigM[i][j];
        }
    }
}

void mul_Stassen(int m, int **Ma, int **Mb, int **Mc){
    int **Ma11 = new int *[m/2];
    int **Ma12 = new int *[m/2];
    int **Ma21 = new int *[m/2];
    int **Ma22 = new int *[m/2];

    int **Mb11 = new int *[m/2];
    int **Mb12 = new int *[m/2];
    int **Mb21 = new int *[m/2];
    int **Mb22 = new int *[m/2];

    int **Mc11 = new int *[m/2];
    int **Mc12 = new int *[m/2];
    int **Mc21 = new int *[m/2];
    int **Mc22 = new int *[m/2];

    int **m1 = new int *[m/2];
    int **m2 = new int *[m/2];
    int **m3 = new int *[m/2];
    int **m4 = new int *[m/2];
    int **m5 = new int *[m/2];
    int **m6 = new int *[m/2];
    int **m7 = new int *[m/2];
    int **mt1 = new int *[m/2];
    int **mt2 = new int *[m/2];

    for(int i=0;i<m;i++){
        Ma11[i] = new int [m/2];
        Ma12[i] = new int [m/2];
        Ma21[i] = new int [m/2];
        Ma22[i] = new int [m/2];

        Mb11[i] = new int [m/2];
        Mb12[i] = new int [m/2];
        Mb21[i] = new int [m/2];
        Mb22[i] = new int [m/2];
        
        Mc11[i] = new int [m/2];
        Mc12[i] = new int [m/2];
        Mc21[i] = new int [m/2];
        Mc22[i] = new int [m/2];

        m1[i] = new int [m/2];
        m2[i] = new int [m/2];
        m3[i] = new int [m/2];
        m4[i] = new int [m/2];
        m5[i] = new int [m/2];
        m6[i] = new int [m/2];
        m7[i] = new int [m/2];
        mt1[i] = new int [m/2];
        mt2[i] = new int [m/2];
    }
    
    //Matrix Block
    for(int i=0;i<m/2;i++){
        for(int j=0;j<m/2;j++){
            Ma11[i][j] = Ma[i][j];
            Ma12[i][j] = Ma[i][j+m/2];
            Ma21[i][j] = Ma[i+m/2][j];
            Ma22[i][j] = Ma[i+m/2][j+m/2];
            
            Mb11[i][j] = Mb[i][j];
            Mb12[i][j] = Mb[i][j+m/2];
            Mb21[i][j] = Mb[i+m/2][j];
            Mb22[i][j] = Mb[i+m/2][j+m/2];
        }
    }

    //M1 = (A11+A22)(B11+B22)
    addMatrix(m/2, Ma11, Ma22, mt1);
    addMatrix(m/2, Mb11, Mb22, mt2);
    mul_GEMM(m/2, mt1, mt2, m1);

    //M2 = (A21+A22)B11
    addMatrix(m/2, Ma21, Ma22, mt1);
    mul_GEMM(m/2, mt1, Mb11, m2);

    //M3 = A11(B12-B22)
    subMatrix(m/2, Mb12, Mb22, mt2);
    mul_GEMM(m/2, Ma11, mt2, m3);

    //M4 = A22(B21-B11)
    subMatrix(m/2, Mb21, Mb11, mt2);
    mul_GEMM(m/2, Ma22, mt2, m4);

    //M5 = (A11+A12)B22
    addMatrix(m/2, Ma11, Ma12, mt1);
    mul_GEMM(m/2, mt1, Mb22, m5);

    //M6 = (A21-A11)(B11+B12)
    subMatrix(m/2, Ma21, Ma11, mt1);
    addMatrix(m/2, Mb11, Mb12, mt2);
    mul_GEMM(m/2, mt1, mt2, m6);

    //M7 = (A12-A22)(B21+B22)
    subMatrix(m/2, Ma12, Ma22, mt1);
    addMatrix(m/2, Mb21, Mb22, mt2);
    mul_GEMM(m/2, mt1, mt2, m7);

    //C11 = M1+M4-M5+M7
    addMatrix(m/2, m1, m4, mt1);
    subMatrix(m/2, mt1, m5, mt2);
    addMatrix(m/2, mt2, m7, Mc11);

    //C12 = M3+M5
    addMatrix(m/2, m3, m5, Mc12);

    //C21 = M2+M4
    addMatrix(m/2, m2, m4, Mc21);

    //C22 = M1-M2+M3+M6
    subMatrix(m/2, m1, m2, mt1);
    addMatrix(m/2, mt1, m3, mt2);
    addMatrix(m/2, mt2, m6, Mc22);

    for(int i=0;i<m/2;i++){
        for(int j=0;j<m/2;j++){
            Mc[i][j] = Mc11[i][j];
            Mc[i][j+m/2] = Mc12[i][j];
            Mc[i+m/2][j] = Mc21[i][j];
            Mc[i+m/2][j+m/2] = Mc22[i][j];
        }
    }

    for(int i=0;i<m/2;i++){
        delete[] Ma11[i];   delete[] Ma12[i];
        delete[] Ma21[i];   delete[] Ma22[i];
        delete[] Mb11[i];   delete[] Mb12[i];
        delete[] Mb21[i];   delete[] Mb22[i];
        delete[] Mc11[i];   delete[] Mc12[i];
        delete[] Mc21[i];   delete[] Mc22[i];
        delete[] m1[i];     delete[] m2[i];
        delete[] m3[i];     delete[] m4[i];
        delete[] m5[i];     delete[] m6[i];
        delete[] m7[i];     delete[] mt1[i];
        delete[] mt2[i];
    }

    delete[] Ma11;      delete[] Ma12;
    delete[] Ma21;      delete[] Ma22;
    delete[] Mb11;      delete[] Mb12;
    delete[] Mb21;      delete[] Mb22;
    delete[] Mc11;      delete[] Mc12;
    delete[] Mc21;      delete[] Mc22;
    delete[] m1;        delete[] m2;
    delete[] m3;        delete[] m4;
    delete[] m5;        delete[] m6;
    delete[] m7;        delete[] mt1;
    delete[] mt2;

}   

int main(){
    cout << "TO SHOW THE SQUARE MATRICES M(*integr power of 2*)" << endl;
    cout << "please input M: ";
    int m;
    cin >> m;
    cout << endl;
    int **M1 = new int *[m];
    int **M2 = new int *[m];
    int **M3 = new int *[m];
    for(int i=0;i<m;i++){
        M1[i] = new int [m];
        M2[i] = new int [m];
        M3[i] = new int [m];
    }
    
    clock_t start, end;
    start = clock();
    
    createMatrix(m,M1);
    createMatrix(m,M2);

    printMatrix(m,M1);
    printMatrix(m,M2);

    mul_Stassen(m, M1, M2, M3);
    printMatrix(m,M3);
    end = clock();
    cout << "RUN TIME: " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;

    for(int i=0;i<m;i++){
        delete[] M1[i];
        delete[] M2[i];
        delete[] M3[i];
    }
    delete[] M1;
    delete[] M2;
    delete[] M3;

    return 0;
}