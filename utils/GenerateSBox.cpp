#include <iostream>
#include <vector>
#include <random>
#include <chrono>

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
    size_t n = (1 << dim);

    std::vector<size_t> pi (n);
    for (size_t i = 0; i < n; ++i)
      pi[i] = i;

    {
//      LOG_DURATION("building permutation");
      for (size_t i = n - 1; i > 0; --i)
      {
        std::uniform_int_distribution<size_t> dist(0, i);

        size_t num = dist(gen);
        std::swap(pi[num], pi[i]);
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
