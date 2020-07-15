#include <iostream>
#include <fstream>

namespace
{
  const std::string tabString = "  ";
}

bool func(size_t digitsNum, size_t number, size_t n);
size_t getLeftPartialNum(size_t number, size_t bitsNum, size_t n);
void printAllFuncs(std::ostream& os, size_t n);

int main(int argc, char* argv[])
{
  std::streambuf * buf;
  std::ofstream of;

  if (argc == 2) 
  {
    of.open(argv[1]);
    buf = of.rdbuf();
  } 
  else if (argc == 1)
  {
    buf = std::cout.rdbuf();
  }
  else
  {
    std::cout << "Too many arguments\n";
    return 0;
  }

  std::ostream out(buf);
  for (size_t i = 2; i <= 11; ++i)
    printAllFuncs(out, i);
}

void printAllFuncs(std::ostream& os, size_t n)
{
  os << "module all_functions_" << n << "(a, z);\n";
  os << tabString << "input [" << (n - 1) << ":0] a;\n";
  os << tabString << "output [" << ((1 << n) - 1) << ":0] z;\n";

  os << std::endl;

  os << tabString << "assign z[0] = 1'b0;\n";
//  os << tabString << "assign z[" << ((1 << n) - 1) << "] = 1'b1;\n";

  os << std::endl;

  for (size_t i = 0; i < n; ++i)
  {
    os << tabString << "assign z[" << (1 << i) << "] = a[" << i << "];\n";
  }

  os << std::endl;

  for (size_t i = 2; i <= n; ++i)
  {
    for (size_t j = 0; j < (1 << n); ++j)
    {
      if (func(i, j, n))
      {
        size_t leftInd = getLeftPartialNum(j, i / 2, n);
        size_t rightInd = j - leftInd;
        os << tabString << "assign z[" << j << "] = z[" << leftInd << "] | z[" << rightInd << "];\n";
      }
    }
    os << std::endl;
  }

  os << "endmodule\n\n";
}

bool func(size_t digitsNum, size_t number, size_t n)
{
  size_t cnt = 0;

  for (size_t i = 0; i < n; ++i)
  {
    if ((number >> i) & 1)
      ++cnt;
  }
  
  return (cnt == digitsNum);
}

size_t getLeftPartialNum(size_t number, size_t bitsNum, size_t n)
{
  size_t res = 0, cnt = 0;

  for (size_t i = 0; i < n; ++i)
  {
    if ((number >> i) & 1)
    {
      res |= (1 << i);
      ++cnt;
    }
    if (cnt == bitsNum)
      break;
  }

  return res;
}
