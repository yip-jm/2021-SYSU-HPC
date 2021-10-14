
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

void mul_GEMM(vector<int>&M1, vector<int>&M2, vector<int>&M3){
    int m = (int)sqrt(M1.size()*M3.size()/M2.size());
    int n = (int)sqrt(M1.size()*M2.size()/M3.size());
    int k = (int)sqrt(M2.size()*M3.size()/M1.size());

    int sum =0;
    for(int i=0;i<M1.size();i++){
        for(int j=0,p=i/k*n;j<n;j++,p++){
            sum += sum += M1[p]*M2[i%k+j*k];
        }
        M3[i] = sum;
    }
}
