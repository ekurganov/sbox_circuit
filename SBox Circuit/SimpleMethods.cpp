#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>

#include "SimpleMethods.h"


namespace
{
  const std::string tabString = "  ";
}

void printSboxCircuitSimple(const std::vector<uint16_t>& inputData, std::ostream& os)
{
  size_t n = static_cast<size_t>(ceil(log2(inputData.size())));

  os << "module sbox" << n << "(a, z);\n";
  os << tabString << "input [" << (n - 1) << ":0] a;\n";
  os << tabString << "output [" << (n - 1) << ":0] z;\n";
  os << tabString << "wire [" << ((1 << n) - 1) << ":0] y;\n";

  os << std::endl;

  os << tabString << "decoder" << n << "_" << (1 << n) << " d_inst(.a(a), .z(y));\n";

  os << std::endl;

  for (size_t i = 0; i < n; ++i)
  {
    bool first = false;
    os << tabString << "assign z[" << i << "] = ";
    for (size_t j = 0; j < static_cast<size_t>(1 << n); ++j)
    {
      if ((inputData[j] >> i) & 1)
      {
          if (first)
            os << " | ";
          else
            first = true;

          os << "y[" << j << "]";
      }

    }
    os << ";\n";
  }

  os << "endmodule\n";
}

void printSboxCircuitUpgSimple(const std::vector<uint16_t>& inputData, std::ostream& os)
{
  size_t n = static_cast<size_t>(ceil(log2(inputData.size())));

  os << "module sbox" << n << "(a, z);\n";
  os << tabString << "input [" << (n - 1) << ":0] a;\n";
  os << tabString << "output [" << (n - 1) << ":0] z;\n";
  os << tabString << "wire [" << ((1 << n) - 1) << ":0] y;\n";
  os << tabString << "wire [" << (n / 2) - 1 << ":0] common;\n";

  os << std::endl;

  os << tabString << "decoder" << n << "_" << (1 << n) << " d_inst(.a(a), .z(y));\n";

  os << std::endl;

  for (size_t i = 0; i < (n - 1); i += 2)
  {
    std::vector<uint16_t> v0, v1;
    v0.reserve(1 << (n - 2));
    v1.reserve(1 << (n - 2));

    bool first = false;

    os << tabString << "assign common[" << i / 2 << "] = ";

    for (size_t j = 0; j < static_cast<size_t>(1 << n); ++j)
    {
      if (((inputData[j] >> i) & 1) && ((inputData[j] >> (i + 1)) & 1))
      {
          if (first)
            os << " | ";
          else
            first = true;

          os << "y[" << j << "]";
      }
      else if ((inputData[j] >> i) & 1)
      {
        v0.push_back(j);
      }
      else if ((inputData[j] >> (i + 1)) & 1)
      {
        v1.push_back(j);
      }
    }
    os << ";\n";

    os << tabString << "assign z[" << i << "] = common[" << i / 2 << "]";
    for (const auto it : v0)
      os << " | y[" << it << "]";
    os << ";\n";

    os << tabString << "assign z[" << i + 1 << "] = common[" << i / 2 << "]";
    for (const auto it : v1)
      os << " | y[" << it << "]";
    os << ";\n";
  }

  if (n & 1)
  {
    bool first = false;
    os << tabString << "assign z[" << (n - 1) << "] = ";
    for (size_t j = 0; j < static_cast<size_t>(1 << n); ++j)
    {
      if ((inputData[j] >> (n - 1)) & 1)
      {
          if (first)
            os << " | ";
          else
            first = true;

          os << "y[" << j << "]";
      }

    }
    os << ";\n";
  }

  os << "endmodule\n";
}

