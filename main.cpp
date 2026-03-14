#include <iostream>
#include <chrono>
#include<vector>
#include <cmath>
#include "func.h"
#include "task1.h"
#include "error.h"
#include <fstream>
#include <string>
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
    
    initialize(x,f,n,k,a,b);
    double deg=5;//  =(степень многочлена +1)  до которой ищем приближение
    //
    //printVector(x,n);
    //printVector(f,n);
    //

    std::vector<double> coef1(deg,0.0);
    std::vector<double> coef2(n,0.0);
    
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
    std::chrono::duration<double> elapsed;
    try {
        auto start = std::chrono::high_resolution_clock::now();
        GetCoeficients(n, x, f, a, b, coef1, deg);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 0;
    }
    // time
    std::cout << "Time to find coefficients: " << elapsed.count() << " seconds" << std::endl;
    //--------------------output--------------------------
        if (!outFilename.empty()) {
        std::ofstream outFile(outFilename);
        if (!outFile.is_open()) {
            std::cerr << "Cannot open file: " << outFilename << std::endl;
            return EXIT_FAILURE;
        }
                    const int plotPoints = 1000;
        double step = (b - a) / (plotPoints - 1);

        outFile << "# x exact approximation\n"; // заголовок
        for (int i = 0; i < plotPoints; ++i) {
            double x_val = a + i * step;
            double exact = GetExactValue(x_val, k);
            double approx = GetValue(x_val, a, b, n, coef1, deg);
            outFile << x_val << " " << exact << " " << approx << "\n";
        }
        outFile.close();
        std::cout << "Graph data written to " << outFilename << std::endl;
    }
    //---------------------end output-----------------
    //Usage:    ./a.out 0 5 5 6 plot_data.txt
    //          gnuplot -p -e "plot 'plot_data.txt' using 1:2 with lines title 'Exact', '' using 1:3 with lines title 'Approx'"
    //
    //или скриптом:
    //          make
    //          chmod +x run_and_plot.sh
    //          ./run_and_plot.sh 0 2 1000 2 plot_data.txt
// Вычисляем интегральную ошибку(При n=1e7 получаем большую ошибку из-за суммирования большого числа слагаемых с плав точкой
// единственный способ избежать-суммирование Кэхэна, сложно+потеря времени)
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