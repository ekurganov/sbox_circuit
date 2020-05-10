
set(SOURCES
  main.cpp
  btree.cpp
  vector_bool.cpp
)


include_directories(
  include/
)

add_executable(sbox-circuit 
  ${SOURCES}
)
