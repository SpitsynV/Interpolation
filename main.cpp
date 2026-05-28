#include <iostream>
#include <chrono>
#include<vector>
#include <cmath>
#include "func.h"
#include "task1.h"
#include "task2.h"
#include "error.h"
#include <fstream>
#include <string>
#include<functional>
using namespace std;
int main(int argc, char* argv[]) {
    // Проверка аргументов: теперь может быть 5 или 6
    if (argc < 5 || argc > 6) {
        std::cerr << "Usage: " << argv[0] << " a b n k [output_file]" << std::endl;
        return EXIT_FAILURE;
    }
    double a = std::stod(argv[1]);
    double b = std::stod(argv[2]);
    int n = std::stoi(argv[3]);
    int k = std::stoi(argv[4]);
    std::string outFilename;
    if (argc == 6) {
        outFilename = argv[5];
    }
    std::vector<double> x(n);
    std::vector<double> f(n);
    std::vector<double> dd(2);
    
    initialize(x,f,n,k,a,b);
    dd[0]=SecondDerivative(a,k); //!!Возможно нажо поставть в точке x[0] чтобы не было экстраполяц
    dd[1]=SecondDerivative(b,k);
    double deg=5;//  =(степень многочлена +1)  до которой ищем приближение
    //
    //printVector(x,n);
    //printVector(f,n);
    //

    std::vector<double> coef1(deg,0.0);
    std::vector<double> coef2(4*n,0.0);
    //********BASE********working ok! */
    //
    //testing
    //
    /*
    GetCoeficients(n, x, f, a, b, coef1, deg);
    double point=1.0;
    
    cout<<"Coeficients "<<endl;
    printVector(coef1,n+1);
    
    cout<<"Value of function "<<k<<" at point "<<point<<" = "<<GetValue(point,a,b,n,coef1,deg)<<endl;
    

    */
    //Посчитаем норму и замеряем время
    /*
    std::chrono::duration<double> elapsed;
    try {
        auto start = std::chrono::high_resolution_clock::now();
        GetCoeficients(n, x, f, a, b, coef1, deg);
        GetCoeficients2(n,x,f,a,b,coef2,dd);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 0;
    }

    // time
    std::cout << "Time to find coefficients: " << elapsed.count() << " seconds" << std::endl;
    //Usage:    ./a.out 0 5 5 6 plot_data.txt
    //          gnuplot -p -e "plot 'plot_data.txt' using 1:2 with lines title 'Exact', '' using 1:3 with lines title 'Approx'"
    //
    //или скриптом:
    //          make
    //          chmod +x run_and_plot.sh
    //          ./run_and_plot.sh 0 2 1000 2 plot_data.txt

auto exactFunc = [&](double xVal) {
        return GetExactValue(xVal, k);
    };
double err_integral = integralError(a, b, n, exactFunc, GetValue, coef1, deg );
std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Интегральная ошибка(1 метод) E_n = " << err_integral << std::endl;
/////
double err_max = maxAbsoluteError(a, b, exactFunc,
                         [&](double xVal){ return GetValue(xVal, a, b, n, coef1, deg); });
                         std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Макс ошибка(2 метод) C_n = " << err_max << std::endl;
*/
//***************tests*************//
//test1 1: фикс n, меняем k

for(int k1=1; k1<7; k1++){
    initialize(x,f,n,k1,a,b);
    dd[0]=SecondDerivative(a,k1);
    dd[1]=SecondDerivative(b,k1);
    GetCoeficients(n, x, f, a, b, coef1, deg);
    GetCoeficients2(n,x,f,a,b,coef2,dd);
    std::cout<<"k= "<<k1<<std::endl;
    //printVector(coef1,coef1.size());
    //printVector(coef2,coef2.size());
    
    auto exactFunc = [&](double xVal) {
        return GetExactValue(xVal, k1);
    };
    double err_integral = integralError(a, b, n, exactFunc, GetValue, coef1, deg );
    std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Интегральная ошибка(1 метод) E_n = " << err_integral << std::endl;
    /////
    double err_max = maxAbsoluteError(x[0], x[n-1], exactFunc,
                         [&](double xVal){ return GetValue2(xVal,x,n,coef2); });
    std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Макс ошибка(2 метод) C_n = " << err_max << std::endl;

}

//test 2: фикс k меняем n
/*
k=6;
for(int n1=2; n1<1000; n1*=2){
    x.resize(n1);
    f.resize(n1);
    coef1.resize(deg);                     
    coef2.resize(4 * (n1 - 1));
    initialize(x,f,n1,k,a,b);
    dd[0]=SecondDerivative(a,k);
    dd[1]=SecondDerivative(b,k);
    GetCoeficients(n1, x, f, a, b, coef1, deg);
    GetCoeficients2(n1,x,f,a,b,coef2,dd);
    std::cout<<"n= "<<n1<<std::endl;
    //printVector(coef1,coef1.size());
    //printVector(coef2,coef2.size());
    
    auto exactFunc = [&](double xVal) {
        return GetExactValue(xVal, k);
    };
    double err_integral = integralError(a, b, n1, exactFunc, GetValue, coef1, deg );
    std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Интегральная ошибка(1 метод) E_n = " << err_integral << std::endl;
    /////
    double err_max = maxAbsoluteError(a, b, exactFunc,
                         [&](double xVal){ return GetValue2(xVal,x,n,coef2); });
    std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Макс ошибка(2 метод) C_n = " << err_max << std::endl;

    }
 */
//test 3: только первый метод, фикс k,n меняем deg
/*
k=6;
deg=n;
for(int n1=2; n1<1000; n1*=2){
    deg=n;
    x.resize(n1);
    f.resize(n1);
    coef1.resize(deg);                     
    coef2.resize(4 * (n1 - 1));
    initialize(x,f,n1,k,a,b);

    GetCoeficients(n1, x, f, a, b, coef1, deg);
    std::cout<<"deg= "<<deg<<std::endl;
    //printVector(coef1,coef1.size());
    //printVector(coef2,coef2.size());
    
    auto exactFunc = [&](double xVal) {
        return GetExactValue(xVal, k);
    };
    double err_integral = integralError(a, b, n1, exactFunc, GetValue, coef1, deg );
    std::cout << std::setw(10) << std::setprecision(3) << std::scientific << "Интегральная ошибка(1 метод) E_n = " << err_integral << std::endl;
    /////
    

    }
*/
    
    return 0;
}