#pragma once

class NConjunct
{
  public:
    NConjunct(size_t n);
    void clear();
    void negateValue(size_t num);
    void printMainValues() const;
    const bool containsConj(const NConjunct& rhs) const;
    void eraseConj(const NConjunct& rhs);
    void constructValue(size_t number, size_t shiftNum);
    void printCircuit(std::ostream& os) const;
    std::string stringCircuit() const;
    const size_t elementsNum() const;
    const size_t depth() const;

    void setDim(const size_t newDim);
    void addPrecompiledConj(const std::pair<size_t, size_t> newConj);
    void setBalancedWireNum(const size_t newWireNum);
    void setMainValue(const size_t index, bool val);

    const size_t dim() const;
    const bool mainValue(const size_t index, const bool val) const;



//  private:
    size_t m_dim;
    size_t m_balancedWireNum;
    std::vector<bool> m_mainValues;
    std::vector<std::pair<size_t, size_t>> m_precompiledConjs;
};

