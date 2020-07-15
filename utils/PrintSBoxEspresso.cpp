#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

namespace
{
  const std::string defaultInputDataFilename = "input.txt";
}

std::vector<uint16_t> readSBox1d(std::ifstream& in)
{
  size_t n;

  if (!(in >> n))
    throw std::invalid_argument("Empty file");

  std::vector<uint16_t> res(1 << n);

  for (size_t i = 0; i < static_cast<size_t>(1 << n); ++i)
  {
    if (!(in >> res[i]))
      throw std::invalid_argument("Wrong number of S-Box elements");
  }

  return res;
}

int main(int argc, char* argv[])
{
  std::string inputDataFilename;
  if (argc == 2)
  {
    inputDataFilename = std::string(argv[1]);
  }
  else if (argc == 1)
  {
    inputDataFilename = defaultInputDataFilename;
  }
  else
  {
    std::cout << "Too many arguments\n";
    return 0;
  }
  
  std::ifstream is (inputDataFilename);

  std::vector<uint16_t> inputData = readSBox1d(is);
  size_t n = static_cast<size_t>(ceil(log2(inputData.size())));

  std::cout << ".i " << n << std::endl;
  std::cout << ".o " << n << std::endl;

  for (size_t i = 0; i < inputData.size(); ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      std::cout << ((i >> j) & 1);
    }
    std::cout << " ";
    for (size_t j = 0; j < n; ++j)
    {
      std::cout << ((inputData[i] >> j) & 1);
    }
    std::cout << std::endl;
  }
}
