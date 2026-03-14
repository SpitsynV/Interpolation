#include "func.h"
#include <cmath>
#include <vector>
#include <iostream>



void printVector(const std::vector<double>& vec, const int m) {
    for (int i = 0; i < m; ++i) {
        std::cout << std::setw(10) << std::setprecision(3) << std::scientific << vec[i] << " ";
    }
    std::cout << std::endl;
}
void initialize(std::vector<double>&x, std::vector<double>&f, int n, int k, double a, double b){
    //задать массивы точек приближения и значения в них
    double h=(b-a)/(n-1);
    for (int i=0;i<n;i++){//равномерно на отрезке
        x[i]=a+h*i;
        f[i]=GetExactValue(x[i],k);
    }

  
  
    //нули многочленов Чебышева
    //требую массив длины n+2 с учетом x_0=a, x_n+1=b 
    /*
    x[0] = a;
    x[n+1] = b;
    f[0]=GetExactValue(x[0],k);
    f[n+1]=GetExactValue(x[n+1],k);
    for (int i=1;i<=n;i++){
        x[i]=(a+b)/2+(b-a)*cos( M_PI*(2*i-1)/(2*n)); 
        f[i]=GetExactValue(x[i],k);
    }
    */
}

