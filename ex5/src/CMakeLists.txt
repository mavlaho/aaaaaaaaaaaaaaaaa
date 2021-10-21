add_executable(ex5prog main.cpp data.cpp)

set_target_properties(ex5prog
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )
