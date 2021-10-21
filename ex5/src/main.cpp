#include <iostream>
#include "data.h"

int main(){
  Data d;
  d.push(1);
  d.push(-1);
  d.sort();
  d.print(std::cout);
  return 0;
}
