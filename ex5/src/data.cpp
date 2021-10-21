#include "data.h"   
#include <algorithm>


std::size_t Data::size() const { return mData.size();}
void Data::clear() { mData.clear(); }
void Data::sort(){ std::sort(mData.begin(), mData.end()); }
void Data::push(int x) { mData.push_back(x); }
void Data::print(std::ostream & out ) const {
  for(auto x : mData) out << x << ",";
  out << "\n";
}
