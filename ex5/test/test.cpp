#include "gtest/gtest.h"
#include "../src/data.h"
#include <vector>
 
using namespace std;

TEST(Data, size) {
    Data d;
    d.push(7);
    d.push(8);
    ASSERT_EQ(d.size(), 2); 
}

TEST(Data, sort){
    Data d;
    d.push(7);
    d.push(4);
    d.push(1);
    d.sort();
    vector<int> e{1,4,7};
    vector<int> f = d.get();
    ASSERT_EQ(e.size(), f.size());
    std::size_t i=0;
    for(auto x : e)
        ASSERT_EQ(x,f[i++]);
}


