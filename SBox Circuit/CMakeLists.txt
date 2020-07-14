CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)

set(SOURCES
  main.cpp
  BTree.cpp
  VectorBool.cpp
  SimpleMethods.cpp
)


include_directories(
  include/
)

add_executable(sbox-circuit 
  ${SOURCES}
)
