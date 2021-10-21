add_executable("testData" test.cpp ../src/data.cpp)
target_link_libraries("testData"  gtest_main)

add_test(NAME testData COMMAND testData)
