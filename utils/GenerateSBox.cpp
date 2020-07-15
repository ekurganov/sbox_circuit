#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <unordered_set>

//#include "Profile.h"

namespace
{
  const size_t defaultDim = 4;
}

int main(int argc, char* argv[])
{
  try
  {
    size_t dim;

    if (argc > 2)
      throw std::invalid_argument("Too many arguments");
    else
      dim = (argc == 1) ? defaultDim : std::stoi(argv[1]);

    std::mt19937_64 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_t> dist(0, (1 << dim) - 1);

    std::vector<size_t> pi ((1 << dim), (1 << dim) + 1);

    {
//      LOG_DURATION("building permutation");
      std::unordered_set<size_t> usedNums;
      usedNums.reserve((1 << dim));
      size_t cnt = 0;

      while (cnt < (1 << dim))
      {
        size_t num = dist(gen);
        if (usedNums.insert(num).second)
          pi[cnt++] = num;
      }
    }

    std::cout << dim << std::endl;
    for (const auto it : pi)
      std::cout << it << " ";
    std::cout << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << "Error. " << e.what() << std::endl;
    std::cout << "Usage: ./prog [n]\n";
  }
}
