#pragma once

void printSboxCircuitSimple(const std::vector<uint16_t>& inputData, std::ostream& os);
void printSboxCircuitUpgSimple(const std::vector<uint16_t>& inputData, std::ostream& os);
void printSboxCircuitShannon(const std::vector<uint16_t>& inputData, std::ostream& os);
void printSboxCircuitLupanov(const std::vector<uint16_t>& inputData, std::ostream& os);

inline uint64_t decoderComplexity(size_t n)
{
  if (n == 1)
    return 0;
  else if (n == 2)
    return 4;
  else
    return decoderComplexity(n / 2) + decoderComplexity(n - (n / 2)) + (static_cast<uint64_t>(1) << n);
}
