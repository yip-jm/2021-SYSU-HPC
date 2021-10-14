# 2021-SYSU-HPC
高性能计算程序设计作业

*----仅供参考----*

#### HW1 MulMatrix(GEMM+STRASSEN+IntelMKL)
+ GEMM
```
for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            C[i][j] = 0;
            for(int k=0;k<n;k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
```
+ STRASSEN

  > 算法详细：[矩阵乘法的Strassen算法详解](https://www.cnblogs.com/hdk1993/p/4552534.html)  
  > [STRASSEN.cpp](/HW1-MulMatrix/mul-matrix-Strassen.cpp)

#### HW2 MulMat(MPI+.so)
+ MPI-p2p（点对点通信）  
  > [MPI_p2p.cpp](/HW2-MulMat(MPI)/mul-matrix-MPI-p2p.cpp)
+ MPI-gather
  > [MPI_gather.cpp](/HW2-MulMat(MPI)/mul-matrix-MPI-gather.cpp)
（集合通信）
+ .so文件编译（实现文件cpp+.h头文件+测试文件）  
  > [.so文件夹](./HW2-MulMat(MPI)/so)  
    >> [mulmat.h](/HW2-MulMat(MPI)/so/mulmat.h)  
    >> [mulmat.cpp](/HW2-MulMat(MPI)/so/mulmat.cpp)  
    >> [test.cpp](/HW2-MulMat(MPI)/so/test.cpp)  

