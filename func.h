#ifndef FUNC_H
#define FUNC_H

#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>



inline double GetExactValue(double x, int k);
void printVector(const std::vector<double>& vec, int m);
void initialize(std::vector<double>&x, std::vector<double>&f, int n, int k, double a, double b);
double integralError(const std::vector<double>& coef, double a, double b,
                     double (*f)(double), double (*P)(double, const std::vector<double>&, double, double));
#endif
