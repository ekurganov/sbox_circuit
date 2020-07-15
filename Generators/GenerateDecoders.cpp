#include <iostream>

void printDecoderModule(size_t i);

int main()
{
  for (size_t i = 4; i <= 11; ++i)
  {
    printDecoderModule(i);
  }
}

void printDecoderModule(size_t n)
{
  size_t j = n / 2;
  size_t i = n - j;

  std::cout << std::endl;

  std::cout << "module decoder" << n << "_" << (1 << n) << "(a, z);\n";
  std::cout << "  input [" << (n - 1) << ":0] a;\n";
  std::cout << "  output [" << ((1 << n) - 1) << ":0] z;\n";
  std::cout << "  wire [" << ((1 << i) - 1) << ":0] x;\n";
  std::cout << "  wire [" << ((1 << j) - 1) << ":0] y;\n";
  std::cout << "  genvar i, j;\n";

  std::cout << std::endl;

  std::cout << "  decoder" << i << "_" << (1 << i) << " d_inst1(.a(a["  
            << (i - 1) << ":0]), .z(x));\n";
  std::cout << "  decoder" << j << "_" << (1 << j) << " d_inst2(.a(a["  
            << (n - 1) << ":" << i << "]), .z(y));\n";

  std::cout << std::endl;

  std::cout << "  for(i = 0; i < " << (1 << j) << "; i = i + 1) begin\n";
  std::cout << "    for(j = 0; j < " << (1 << i) << "; j = j + 1) begin\n";
  std::cout << "      assign z[i * " << (1 << i) << " + j] = x[j] & y[i];\n";
  std::cout << "    end\n";
  std::cout << "  end\n";
  std::cout << "endmodule";

  std::cout << std::endl;
}
