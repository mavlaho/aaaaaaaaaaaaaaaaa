#include <iostream>
#include <fstream>
#include <stdexcept>


int main()
{
  using namespace std;

  ifstream in("text.txt");
  if(!in)
      throw runtime_error("Ne mogu otvoriti text.txt za čitanje.");

  string line;
  while(getline(in, line))
          cout << line << "\n";

  return 0;
}
