CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)

add_executable(generateSbox
  GenerateSBox.cpp
)

add_executable(inOutPrint 
  PrintInputsOutputsVerilog.cpp
)

add_executable(espressoPrint
  PrintSBoxEspresso.cpp
)
