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


#### HW2 MulMattrix(MPI(p2p&gather)+.so)
+ p2p
```
```
+ gather
```
```
