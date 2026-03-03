#include "func.h"
#include <cmath>
#include <vector>
#include <iostream>


inline double GetExactValue(double x, int k){
    switch(k){
        case 0:
            return 1;
        case 1:
            return x;
        case 2:
            return pow(x,2);
        case 3:
            return pow(x,3);
        case 4:
            return pow(x,4);
        case 5:
            return exp(x);
        case 6:
            return (1.0/(25*pow(x,2)+1));
        default:
            throw std::invalid_argument("Error: Wrong formula number");
    }

}
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

// Весовая функция
double weight(double x, double a, double b) {
    return 1.0 / std::sqrt((b - x) * (x - a));
}

// Вычисление интеграла методом Симпсона
double integralError(const std::vector<double>& coef, double a, double b,
                     double (*f)(double), double (*P)(double, const std::vector<double>&, double, double)) {
    int N = 10000; // число точек для квадратуры
    double h = (b - a) / N;
    double sum = 0.0;
    for (int i = 0; i <= N; ++i) {
        double x = a + i * h;
        double w = (i == 0 || i == N) ? 1.0 : (i % 2 == 0 ? 2.0 : 4.0);
        double diff = f(x) - P(x, coef, a, b);
        sum += w * diff * diff * weight(x, a, b);
    }
    return (h / 3.0) * sum;
}
