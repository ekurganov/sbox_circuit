#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

#include "SimpleMethods.h"

namespace
{
  const std::string tabString = "  ";
}

void printSboxCircuitShannonK(const std::vector<uint16_t>& inputData, std::ostream& os, size_t n, size_t k)
{
  os << "module sbox" << n << "(a, z);\n";
  os << tabString << "input [" << (n - 1) << ":0] a;\n";
  os << tabString << "output [" << (n - 1) << ":0] z;\n";
  os << tabString << "wire [" << ((1 << (1 << k)) - 1) << ":0] leftGroup;\n";
  os << tabString << "wire [" << ((1 << (n - k)) - 1) << ":0] rightGroup;\n";

  os << std::endl;

  os << tabString << "decoder" << (n - k) << "_" << (1 << (n - k)) << " d_inst(.a(a[" << (n - 1) << ":" << k << "]), .z(rightGroup));\n";
  os << tabString << "phi" << k << " phi_inst(.a(a[" << (k - 1) << ":0]), .z(leftGroup));\n";

  os << std::endl;

  for (size_t l = 0; l < n; ++l)
  {
    os << tabString << "assign z[" << l << "] = ";
    bool first = false;
    for (size_t i = 0; i < static_cast<size_t>(1 << (n - k)); ++i)
    {
      size_t index = 0;
      for (size_t j = 0; j < static_cast<size_t>(1 << k); ++j)
      {
        index |= (((inputData[i * (1 << k) + j]) >> l) & 1) << j;
      }

      if (first)
         os << " | ";
      else
        first = true;

      os << "rightGroup[" << i << "] & leftGroup[" << index << "]";
    }
    os << ";\n";
  }

  os << "endmodule\n";
}

size_t optimalParameterShannon(size_t n)
{
  size_t lim = std::min(static_cast<size_t>(4), n - 1);
  size_t minComp = std::numeric_limits<size_t>::max();
  size_t mk = 0;
  for (size_t k = 1; k <= lim; ++k)
  {
    size_t currComp = (1 << ((1 << k) - 1)) - (1 << k) - k - 1 + decoderComplexity(k) + decoderComplexity(n - k) + n * ((1 << (n - k + 1)) - 1);
    if (currComp < minComp)
    {
      minComp = currComp;
      mk = k;
    }
  }
  return mk;
}

void printSboxCircuitShannon(const std::vector<uint16_t>& inputData, std::ostream& os)
{
  size_t n = static_cast<size_t>(ceil(log2(inputData.size())));
  size_t s = optimalParameterShannon(n);
  printSboxCircuitShannonK(inputData, os, n, s);
}
