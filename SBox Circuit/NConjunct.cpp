#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

#include "NConjunct.h"


NConjunct::NConjunct(size_t n)
{
  m_dim = n;
  m_mainValues.resize(2 * n);
  m_balancedWireNum = 0;
}

void NConjunct::clear()
{
  for (size_t i = 0; i < m_mainValues.size(); ++i)
    m_mainValues[i] = false;
}

const bool NConjunct::containsConj(const NConjunct& rhs) const
{
  for (size_t i = 0; i < rhs.m_mainValues.size(); ++i)
  {
    if (rhs.m_mainValues[i] == true)
    {
      if (m_mainValues[i] == false)
        return false;
    }
  }
  return true;
}

void NConjunct::eraseConj(const NConjunct& rhs)
{
  for (size_t i = 0; i < rhs.m_mainValues.size(); ++i)
  {
    if (rhs.m_mainValues[i] == true)
    {
      m_mainValues[i] = false;
    }
  }
}

void NConjunct::constructValue(size_t number, size_t shiftNum)
{
  clear();

  for (size_t i = 0, shiftCnt = 0; i < m_dim; ++i)
  {
    if ((number >> i) & 1)
    {
      size_t shift = (shiftNum >> shiftCnt) & 1;
      m_mainValues[i * 2 + shift] = true;
      ++shiftCnt;
    }
  }
}

void NConjunct::printCircuit(std::ostream& os) const
{
  if (m_balancedWireNum > 0)
  {
    os << "conjunct[" << m_balancedWireNum << "]";
    return;
  }
  bool first = false;
  for (size_t i = 0; i < m_dim; ++i)
  {
    if (m_mainValues[i * 2 + 1] == true || m_mainValues[i * 2] == true)
    {
      if (first)
        os << "&";
      else
        first = true;
    }

    if (m_mainValues[i * 2 + 1] == true)
      os << "~a[" << i << "]";
    else if (m_mainValues[i * 2 ] == true)
      os << "a[" << i << "]";
  }
  for (const auto& it : m_precompiledConjs)
  {
    if (first)
      os << "&";
    else
      first = true;

    os << "commonWire" << it.first << "[" << it.second << "]";
  }
}

std::string NConjunct::stringCircuit() const
{
  std::string res;
  if (m_balancedWireNum > 0)
  {
    res += "conjunct[" + std::to_string(m_balancedWireNum) + "]";
    return res;
  }
  bool first = false;
  for (size_t i = 0; i < m_dim; ++i)
  {
    if (m_mainValues[i * 2 + 1] == true || m_mainValues[i * 2] == true)
    {
      if (first)
        res += "&";
      else
        first = true;
    }

    if (m_mainValues[i * 2 + 1] == true)
      res += "~a[" + std::to_string(i) + "]";
    else if (m_mainValues[i * 2 ] == true)
      res += "a[" + std::to_string(i) + "]";
  }
  for (const auto& it : m_precompiledConjs)
  {
    if (first)
      res += "&";
    else
      first = true;

    res += "commonWire" + std::to_string(it.first) + "[" + std::to_string(it.second) + "]";
  }
  return res;
}

const size_t NConjunct::elementsNum() const
{
  size_t res = 0;

  for (size_t i = 0; i < m_dim; ++i)
  {
    if (m_mainValues[i * 2 + 1] == true || m_mainValues[i * 2] == true)
      ++res;
  }
  return res + m_precompiledConjs.size();
}

const size_t NConjunct::depth() const
{
  std::map<size_t, size_t> inputValues;
  for (size_t i = 0; i < m_dim; ++i)
  {
    if (m_mainValues[i * 2 + 1] == true || m_mainValues[i * 2] == true)
      ++(inputValues[0]);
  }
  for (const auto& it : m_precompiledConjs)
  {
    size_t currDepth = static_cast<size_t>(ceil(log2(it.first)));
    ++(inputValues[currDepth]);
  }

  size_t maxDepth = inputValues.rbegin()->first;
  for (size_t i = 0; i <= maxDepth; ++i)
  {
    if (i < maxDepth)
      inputValues[i + 1] += ((inputValues[i] >> 1) + (inputValues[i] & 1));
  }
  return maxDepth + static_cast<size_t>(ceil(log2(inputValues[maxDepth])));
}

void NConjunct::setDim(const size_t newDim)
{
  m_dim = newDim;
}

void NConjunct::addPrecompiledConj(const std::pair<size_t, size_t> newConj)
{
  m_precompiledConjs.push_back(newConj);
}

void NConjunct::setBalancedWireNum(const size_t newWireNum) const
{
  m_balancedWireNum = newWireNum;
}

void NConjunct::setMainValue(const size_t index, bool val)
{
  size_t intIndex = 2 * index + 1;
  if (val)
    --intIndex;

  m_mainValues[intIndex] = true;
}

const size_t NConjunct::dim() const
{
  return m_dim;
}

const bool NConjunct::mainValue(const size_t index, const bool val) const
{
  size_t intIndex = 2 * index + 1;
  if (val)
    --intIndex;

  return m_mainValues[intIndex];
}

const std::vector<std::pair<size_t, size_t> >& NConjunct::precompiledConjs() const
{
  return m_precompiledConjs;
}
