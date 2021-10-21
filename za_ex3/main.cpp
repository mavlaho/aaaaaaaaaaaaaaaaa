#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/sqrt.h"

int main()
{
  using namespace std;
  double x = 0.0;
  cout << "Enter a nonnegative number: ";
  cin >> x;
  double y = Sqrt(x);
  cout << " square root = " << setprecision(12) << y << endl;
  cout << " error = " <<  setprecision(12) << std::sqrt(x) - y  << endl;
  return 0;
}
