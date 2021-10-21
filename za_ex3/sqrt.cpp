#include "../include/sqrt.h"
#include <stdexcept>
#include <cmath>

double Sqrt(double x)
{
    if(x < 0.0)
        throw std::runtime_error("Sqrt: negative argument.");

    int n;
    double rem = std::frexp(x,&n);  // x = rem * 2^n
    n /= 2;
    double x1 = 1 << n;  // 2^(n/2) aproksimacija za korijen iz x.
    double x0 = 0.0;
    const double EPS = 1E-10;
    do{
        x0 = x1;
        x1 = (x0 + x/x0)/2;
    }
    while(std::abs(x1-x0) > EPS);
    return x1;
}
