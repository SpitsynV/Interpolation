#include <iostream>
#include <chrono>
#include<vector>
#include <cmath>
#include "func.h"
#include "task1.h"
#include "error.h"
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
    double deg=4;//степень многочлена до которой ищем приближение
    //
    //printVector(x,n);
   // printVector(f,n);
    //

    std::vector<double> coef1(n+1,0.0);
    std::vector<double> coef2(n,0.0);
    
    //
    //testing
    //
    /*
    GetCoeficients(n,x,f,coef1,deg);
    double point=1.0;
    
    cout<<"Coeficients "<<endl;
    printVector(coef1,n+1);
    
    cout<<"Value of function "<<k<<" at point "<<point<<" = "<<GetValue(point,a,b,n,x,coef1,deg)<<endl;
    */

    //Посчитаем норму и замеряем время
    std::chrono::duration<double> elapsed;
    try {
        auto start = std::chrono::high_resolution_clock::now();
        GetCoeficients(n,x,f,coef1,deg);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 0;
    }
    // time
    std::cout << "Time to find coefficients: " << elapsed.count() << " seconds" << std::endl;
// Вычисляем интегральную ошибку
double err_integral = integralError(a,b,n,k,coef1,deg,20000);
std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Интегральная ошибка E_n = " << err_integral << std::endl;
/////

//
//test1 1:
//ПРОБЛЕма в тесте: начальный результат(до цикла) не сходится ни с одним из цикла. Что делать? 

/*for(int k1=0;k1<7;k1++){
    initialize(x,f,n,k1,a,b);
    GetCoeficients(n,x,f,coef1,deg);
    double err_integral = integralError(a,b,n,k1,coef1,deg,20000);
    double err_discr=discreteError(x,f,a,b,n,coef1,deg);
    std::cout << "Интегральная ошибка при k="<<k1<<" равна E_n "<< err_integral << std::endl;
    std::cout << "Дискретная ошибка при k="<<k1<<" равна D_n "<< err_discr << std::endl;

}
    */




    
    return 0;
}