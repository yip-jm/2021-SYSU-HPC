/*
 * @Author: ye_jm
 * @Date: 2021.10.09
 * @E-mail: yejm6@mail2.sysu.edu.cn
 */

// To Run: 
// mpicxx mul-matirx-MPI.cpp 
// mpiexec -n comm_sz ./a.out mat_dim
//mpirun -np comm_sz ./a.out
#include<bits/stdc++.h>
#include"mpi.h"
using namespace std;
#define random(x) rand()%(x)
int seed=0;

void createMatrix(int m, int *M){
    for(int i=0;i<m;i++){
        srand(time(0)+seed);
        M[i] = random(100);
        seed++;
    }
}
void createMatrix_add(int m,int tmp_m,int *M){
        for(int i=0;i<m*m;i++){
            srand(time(0)+seed);
            M[i] = random(100);
            seed++;
        }
        for(int i=0;i<tmp_m*m;i++){
            M[i] = 0;
        }
}

// void printMatrix(int row, int col, int **matrix){
//     for(int i=0;i<row;i++){
//         for(int j=0;j<col;j++){
//             cout << matrix[i][j] << " ";
//         }
//         cout << endl;
//     }
//     cout << endl;
// }

void mul_GEMM(int row, int m, int *leftM, int *rigM, int *resM){
    for(int i=0;i<row;i++){
        for(int j=0;j<m;j++){
            resM[i*m+j] = 0;
            for(int k=0;k<m;k++){
                resM[i*m+j] += leftM[i*m+k]*rigM[k*m+j];
            }
        }
    }
}


int main(int argc, char **argv){

    int m = atoi(argv[1]);

    //MPI init
    int comm_sz, rank;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &rank);

    double start, end;
    if(comm_sz == 1){
        //no parallel
        int *M1 = new int [m*m];
        int *M2 = new int [m*m];
        int *M3 = new int [m*m];

        createMatrix(m*m,M1);
        createMatrix(m*m,M2);

        start = MPI_Wtime();
        mul_GEMM(m,m,M1,M2,M3);
        end = MPI_Wtime();

        cout << "RUN TIME: " << double(end - start) << "s" << endl;

        delete[] M1;
        delete[] M2;
        delete[] M3;
        
    }else{
        //parallel
        int tmp_m = 0;
        if(m%comm_sz!=0){
            tmp_m = comm_sz - (m - m/comm_sz * comm_sz);
        }
        int my_task = m/comm_sz;

        int *M1 = new int [m*m+tmp_m*m];
        int *M2 = new int [m*m];
        int *M3 = new int [m*m+tmp_m*m];
        int *rec_M1 = new int [my_task*m];
        int *rec_M3 = new int [my_task*m];

        createMatrix_add(m,tmp_m,M1);
        createMatrix(m*m,M2);

        if(rank==0){
            start = MPI_Wtime();
        }

        MPI_Scatter(&M1[0], my_task*m, MPI_INT, &rec_M1[0], my_task*m, MPI_INT, 0, comm);
        MPI_Bcast(&M2[0], m*m, MPI_INT, 0, comm);

        mul_GEMM(my_task, m, rec_M1, M2, rec_M3);

        MPI_Gather(&rec_M3[0], my_task*m, MPI_INT, &M3[0], my_task*m, MPI_INT, 0, comm);

        if(rank==0){
            end = MPI_Wtime();
            cout << "RUN TIME: " << double(end - start) << "s" << endl;
        }

        if(true){
            delete[] M1;
            delete[] M2;
            delete[] M3;
            delete[] rec_M1;
            delete[] rec_M3;
        }
    }

    MPI_Finalize();
    return 0;

}
