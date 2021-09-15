/*
 * @Author: ye_jm
 * @Date: 2021.09.14
 * @E-mail: yejm6@mail2.sysu.edu.cn
 */


#include<bits/stdc++.h>
#define random(x) rand()%(x)
using namespace std;

int main(){
    int m,n,k;
    cout << "TO SHOW THE M*N， N*K matrices " << endl;
    cout << "please input M N K" << endl;
    cin >> m >> n >> k;
    cout << endl;

    clock_t start, end;
    start = clock();

    vector<float>M1;
    vector<float>M2;
    srand((int)time(0));

    //create two random matrices
    for(int i=0;i<m*n;i++){
        M1.push_back(random(100));
    }
    for(int i=0;i<n*k;i++){
        M2.push_back(random(100));
    }

    //show matrices
    for(int i=0;i<m*n;i++){
        cout << M1[i] << " ";
        if((i+1)%n==0)
        cout << left << endl;
    }
    cout << endl;
    for(int i=0;i<n*k;i++){
        cout << M2[i] << " ";
        if((i+1)%k==0)
        cout << left << endl;
    }
    cout << endl;

    //multiple matrices
    vector<int>res;
    int sum;
    for(int i=0;i<m*k;i++){
        sum=0;
        for(int j=0,p=i/k*n;j<n;j++,p++){
            sum += M1[p]*M2[i%k+j*k];
        }
        res.push_back(sum);
    }
    
    end = clock();

    //output the res
    for(int i=0;i<m*k;i++){
        cout << res[i] << " ";
        if((i+1)%k==0)
        cout << left << endl;
    }
    cout << endl;

    cout << "RUN TIME: " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;
}