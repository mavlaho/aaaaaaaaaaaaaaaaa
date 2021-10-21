#ifndef CLASS_IS_INVLUDED
#define CLASS_IS_INVLUDED

#include <vector>
#include <ostream>

class Data{
  public:
    std::size_t size() const;
    void clear();
    void sort();
    void push(int x); 
    void print(std::ostream & out ) const;
    std::vector<int> get() const { return mData; }
  private:
    std::vector<int> mData;
};

#endif 
