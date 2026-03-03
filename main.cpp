#include <iostream>
#include <chrono>
#include<vector>
#include <cmath>
#include "func.h"
#include "task1.h"
using namespace std;
int main(int argc, char* argv[]) {
    if (argc < 5 || argc > 6) {
        std::cerr << "Usage: " << argv[0] << " a b n k " << std::endl; //проверь формат
        return EXIT_FAILURE;
    }
    double a = std::stoi(argv[1]);
    double b = std::stoi(argv[2]);
    int n = std::stoi(argv[3]);
    int k = std::stoi(argv[4]);



    std::vector<double> x(n);
    std::vector<double> f(n);
    
    initialize(x,f,n,k,a,b);
    //
   // printVector(x,n);
   // printVector(f,n);
    //

    std::vector<double> coef1(n+1,0.0);
    std::vector<double> coef2(n,0.0);
    /*
    //
    //testing
    //
    GetCoeficients(n,x,f,coef1);
    double point=1.556;
    
    cout<<"Coeficients "<<endl;
    printVector(coef1,n+1);
    
    cout<<"Value of function "<<k<<" at point "<<point<<" = "<<GetValue(point,a,b,n,x,coef1)<<endl;
    */

    //Посчитаем норму и замеряем время
    std::chrono::duration<double> elapsed;
    try {
        auto start = std::chrono::high_resolution_clock::now();
        GetCoeficients(n,x,f,coef1);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 0;
    }
    // time
    std::cout << "Time to find coefficients: " << elapsed.count() << " seconds" << std::endl;


/////////*НЕ эту норму минимизируем! Разобраться
    double err=0;
    for(int i=0;i<n;i++){
        err+=pow((f[i]-GetValue(x[i],a,b,n,x,coef1)),2);
    }
    err=sqrt(err/n);
    cout<<"Norm of error = "<<err<<endl;
*/
//




    
    return 0;
}