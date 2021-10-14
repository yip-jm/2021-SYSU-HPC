#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// To Run: 
// mpicxx matrix_multi_improvement1.cpp 
// mpiexec -n 4 ./a.out 64

// Improvement 1: 
// Matrix A: different processes deal with different components, so Scatter instead of Send/Recv
// Matrix B: Shared by all processes, so Bcast instead of Send/Recv
// Matrix C: receive different components from different processes, so Gather instead of Send/Recv
// Main process should also involve in calculation

void matGene(int *A, int size, int actual_size){
    // actual size: the matrix we use may have a larger dimension than n * n
    for (int i = 0; i < actual_size; i++){
        for (int j = 0; j < actual_size; j++){
            if(i < size && j < size) A[i * actual_size + j] = rand() % 100; //A[i][j]
            else A[i * actual_size + j] = 0;
        }
    }
}

void matMulti(int *A, int *B, int*C, int row, int n){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < n; j++){
            C[i*n + j] = 0;
            for (int k = 0; k < n; k++) 
                C[i*n + j] += A[i*n + k] * B[k*n + j];
        }
    }
}

int main(int argc, char *argv[]){
    // Only Deal With Square Matrixs

    // Calculate Parameters Definition
    int n = atoi(argv[1]); // matrix dimension
    // int beginRow, endRow; // the range of rows calculating in certain process
    double beginTime, endTime; // time record
    srand(time(NULL));

    // MPI Common Head
    int my_rank = 0, comm_sz = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Status status;

    if (comm_sz == 1){ // no parallel
        // Prepare data
        int* A = new int[n * n + 2];
        int* B = new int[n * n + 2];
        int* C = new int[n * n + 2];
        int saveN = n;
        matGene(A, saveN, n);
        matGene(B, saveN, n);

        // Calculate C[i][j] & Time
        beginTime = MPI_Wtime();
        matMulti(A, B, C, n, n);
        endTime = MPI_Wtime();
        cout << "Time: " << endTime - beginTime << endl;

        // Output

        // cout << "A" << endl;
        cout << endl;
        for(int i = 0; i < saveN; i++){
            for(int j = 0; j < saveN; j++)
                cout << A[i * n + j] << " ";
            cout << endl;
        }

        cout  << endl;
        for(int i = 0; i < saveN; i++){
            for(int j = 0; j < saveN; j++)
                cout << B[i * n + j] << " ";
            cout << endl;
        }

        cout << endl;
        for(int i = 0; i < saveN; i++){
            for(int j = 0; j < saveN; j++)
                cout << C[i * n + j] << " ";
            cout << endl;
        }

        delete[] A;
        delete[] B;
        delete[] C;
    }

    else{ // parallel: main process collect the result and also involve in calculation

        int saveN = n;

        // must equal scatter: actual n is bigger than input
        if(n % comm_sz != 0){
            n -= n % comm_sz;
            n += comm_sz;
        }

        int each_row = n / comm_sz;

        // Matrixs
        int* A = new int[n * n + 2];
        int* B = new int[n * n + 2];
        int* C = new int[n * n + 2];
        // beginRow = each_row * (my_rank-1), endRow = each_row * my_rank;
        int* partA = new int[each_row * n + 2]; // A[beginRow:endRow, :]
        int* partC = new int[each_row * n + 2]; // C[beginRow:endRow, :]
        
        if (my_rank == 0){

            // Prepare data
            cout << "n = " << n << endl;
            matGene(A, saveN, n);
            matGene(B, saveN, n);  

            beginTime = MPI_Wtime();

        }

        // data distribution & calculate results & collect 

        // Send: Scatter A, Bcast whole B
        MPI_Scatter(&A[0 * n + 0], each_row * n, MPI_INT, &partA[0 * n + 0], each_row * n, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&B[0 * n + 0], n * n, MPI_INT, 0, MPI_COMM_WORLD);

        // All processes involve calculation
        matMulti(partA, B, partC, each_row, n);

        // Recv: Gather C
        MPI_Gather(&partC[0 * n + 0], each_row * n, MPI_INT, &C[0 * n + 0], each_row * n, MPI_INT, 0, MPI_COMM_WORLD);

        if (my_rank == 0){

            endTime = MPI_Wtime();
            cout << "RUN TIME: " << double(endTime - beginTime) << "s" << endl;
            // Output
            
            cout  << endl;
            for(int i = 0; i < saveN; i++){
                for(int j = 0; j < saveN; j++)
                    cout << A[i * n + j] << " ";
                cout << endl;
            }   

            cout  << endl;
            for(int i = 0; i < saveN; i++){
                for(int j = 0; j < saveN; j++)
                    cout << B[i * n + j] << " ";
                cout << endl;
            }   

            cout << endl;
            for(int i = 0; i < saveN; i++){
                for(int j = 0; j < saveN; j++)
                    cout << C[i * n + j] << " ";
                cout << endl;
            }
        
        }

        // if(my_rank != 0)
        if(true){
            delete[] A;
            delete[] B;
            delete[] C;
            delete[] partA;
            delete[] partC;
        }
        else{
            delete[] A;
            cout << "Delete A in " << my_rank << endl;
            delete[] B;
            cout << "Delete B in " << my_rank << endl;
            delete[] C;
            cout << "Delete C in " << my_rank << endl;
            delete[] partA;
            cout << "Delete partA in " << my_rank << endl;
            delete[] partC; 
            cout << "Delete partC in " << my_rank << endl;
        }

    }

    MPI_Finalize();
    return 0;
}