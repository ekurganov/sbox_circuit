set(SOURCES
  main.cpp
  BTree.cpp
  VectorBool.cpp
)


include_directories(
  include/
)

add_executable(sbox-circuit 
  ${SOURCES}
)
