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

void printSboxCircuitLupanovKS(const std::vector<uint16_t>& inputData, std::ostream& os, size_t n, size_t k, size_t s)
{
  size_t p = (1 << k) / s;
  size_t ss = (1 << k) - p * s;

  os << "module sbox" << n << "(a, z);\n";
  os << tabString << "input [" << (n - 1) << ":0] a;\n";
  os << tabString << "output [" << (n - 1) << ":0] z;\n";
  os << tabString << "wire [" << ((1 << (n - k)) - 1) << ":0] leftGroup[" << (n - 1) << ":0];\n";
  os << tabString << "wire [" << ((1 << k) - 1) << ":0] conj;\n";
  os << tabString << "wire [" << ((1 << (n - k)) - 1) << ":0] rightGroup;\n";
  os << tabString << "wire [" << ((1 << s) - 1) << ":0] partialFunctions[" << (p - 1) << ":0];\n";

  if (ss)
  {
    os << tabString << "wire [" << ((1 << ss) - 1) << ":0] partialFunctionsTail;\n";
  }

  os << std::endl;

  os << tabString << "genvar i;\n";

  os << std::endl;

  os << tabString << "decoder" << (n - k) << "_" << (1 << (n - k)) << " d_right_inst(.a(a[" << (n - 1) << ":" << k << "]), .z(rightGroup));\n";
  os << tabString << "decoder" << k << "_" << (1 << k) << " d_left_inst(.a(a[" << (k - 1) << ":0]), .z(conj));\n";

  os << std::endl;

  os << tabString << "for(i = 0; i < " << p << "; i = i + 1) begin\n";
  os << tabString << tabString << "all_functions_" << s << " all_f_inst(.a(conj[(i + 1) * " << s << " - 1:i * " << s << "]), .z(partialFunctions[i]));\n";
  os << tabString << "end\n";
  if (ss)
  {
    os << tabString << "all_functions_" << ss << " all_f_inst(.a(conj[" <<(1 << k) - 1 << ":" << p * s  << "]), .z(partialFunctionsTail));\n";
  }

  os << std::endl;

  for (size_t l = 0; l < n; ++l)
  {
    for (size_t i = 0; i < static_cast<size_t>(1 << (n - k)); ++i)
    {
      os << tabString << "assign leftGroup[" << l << "][" << i << "] = ";

      bool first = false;
      for (size_t j = 0; j < p; ++j)
      {
        size_t index = 0;
        for (size_t kk = 0; kk < s; ++kk)
        {
          index |= (((inputData[i * (1 << k) + j * s + kk]) >> l) & 1) << kk;
        }

        if (first)
           os << " | ";
        else
          first = true;

        os << "partialFunctions[" << j << "][" << index << "]";
      }

      if (ss)
      {
        size_t index = 0;
        for (size_t kk = 0; kk < ss; ++kk)
        {
          index |= (((inputData[i * (1 << k) + p * s + kk]) >> l) & 1) << kk;
        }

        if (first)
           os << " | ";

        os << "partialFunctionsTail[" << index << "]";
      }

      os << ";\n";
    }
  }

  os << std::endl;

  for (size_t l = 0; l < n; ++l)
  {
    os << tabString << "assign z[" << l << "] = ";

    bool first = false;
    for (size_t i = 0; i < static_cast<size_t>(1 << (n - k)); ++i)
    {
      if (first)
         os << " | ";
      else
        first = true;

      os << "(leftGroup[" << l << "][" << i << "] & rightGroup[" << i << "])";
    }

    os << ";\n";
  }

  os << "endmodule\n";
}

uint64_t complexityLupanov(size_t n, size_t k, size_t s)
{
  uint64_t res = decoderComplexity(k) + decoderComplexity(n - k); // A, B

  uint64_t p = (static_cast<uint64_t>(1) << k) / s;
  uint64_t ss = (static_cast<uint64_t>(1) << k) - p * s;


  uint64_t sorts;
  if (s < 50)
    sorts = std::min((static_cast<uint64_t>(1) << s) - s - 1, n * (static_cast<uint64_t>(1) << (n - k)) * (s - 1));
  else
    sorts = n * (static_cast<uint64_t>(1) << (n - k)) * (s - 1);
  uint64_t tmp = p * sorts;
  if (ss > 0)
  {
    if (s < 50)
      sorts = std::min((static_cast<uint64_t>(1) << ss) - ss - 1, n * (static_cast<uint64_t>(1) << (n - k)) * (ss - 1));
    else
      sorts = n * (static_cast<uint64_t>(1) << (n - k)) * (ss - 1);
    tmp += sorts;
  }
//  std::cout << "C: " << tmp << std::endl;

  res += tmp;                                                   // C

  if (ss == 0)
    --p;
  tmp = n * p * (static_cast<uint64_t>(1) << (n - k));         // D
//  std::cout << "D: " << tmp << std::endl;
  res += tmp;

  tmp = n * ((static_cast<uint64_t>(1) << (n - k + 1)) - 1);       // E
//  std::cout << "E: " << tmp << std::endl;
  res += tmp;

//  std::cout << "Res: " << res << std::endl;
//  std::cout << "~~~~~~~~~~~~~~~\n";

  return res;
}


std::pair<size_t, size_t> optimalParametersLupanov(size_t n)
{
  size_t k = 0, s = 0;
  uint64_t minComp = std::numeric_limits<uint64_t>::max();
  for (size_t i = 1; i < n - 1; ++i)
  {
    for (size_t j = 1; j < static_cast<size_t>(1 << n) - 1; ++j)
    {
      uint64_t currComp = complexityLupanov(n, i, j);
      if (currComp < minComp)
      {
        minComp = currComp;
        k = i;
        s = j;
      }
    }
  }

  return {k, s};
}

void printSboxCircuitLupanov(const std::vector<uint16_t>& inputData, std::ostream& os)
{
  size_t n = static_cast<size_t>(ceil(log2(inputData.size())));
  std::pair<size_t, size_t> skPair = optimalParametersLupanov(n);
  printSboxCircuitLupanovKS(inputData, os, n, skPair.first, skPair.second);
}
