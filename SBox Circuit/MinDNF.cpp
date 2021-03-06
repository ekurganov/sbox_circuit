#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>

#include "NConjunct.h"
#include "MinDNF.h"

inline size_t onesNum(size_t number, size_t n)
{
  size_t cnt = 0;

  for (size_t i = 0; i < n; ++i)
  {
    if ((number >> i) & 1)
      ++cnt;
  }

  return cnt;
}

void printBalanceCircuit(std::ostream& os, std::map<size_t, std::vector<std::string>>& inputElements, const size_t num, const std::string& resultName, bool isConj = true)
{
  size_t maxDepth = inputElements.rbegin()->first;
  std::string pairSymbol = isConj ? "&" : "|";
  
  for (const auto& itVec : inputElements)
  {
    bool pairStarted = false;
    if (itVec.first < maxDepth)
    {
      size_t cnt = 0;
      for (size_t i = 0; i < itVec.second.size(); ++i)
      {
        if (!pairStarted)
        {
          pairStarted = true;
        }
        else
        {
          os << "assign tmpWire" << num  << "[" << itVec.first + 1 << "][" << cnt << "] = " << itVec.second[i - 1] << " " << pairSymbol << " " << itVec.second[i] << ";\n";
          pairStarted = false;
          inputElements[itVec.first + 1].push_back("tmpWire" + std::to_string(num) + "[" + std::to_string(itVec.first + 1) + "][" + std::to_string(cnt) + "]");
          ++cnt;
        }
      }
      if (pairStarted)
      {
        inputElements[itVec.first + 1].push_back(itVec.second.back());
      }
    }
    else // last element, max depth
    {
      os << "assign " << resultName << " = ";
      for (const auto& it : itVec.second)
      {
        if (!pairStarted)
          pairStarted = true;
        else
          os << " " << pairSymbol << " ";
        os << it;
      }
      os << "; \n";
    }
  }
}

std::vector<std::vector<NConjunct>> readEspressoFile(std::ifstream& is, size_t& maxEls)
{
  std::string line;
  std::vector<std::string> strVec;
  size_t dim;

  while (std::getline(is, line))
  {
    strVec.push_back(std::move(line));
  }

  if (strVec.size() >= 5)
  {
    if (strVec[0].substr(0, 3) != ".i ")
      throw std::invalid_argument("Wrong input format");

    dim = std::stoi(strVec[0].substr(3));

    if (strVec[1].substr(0, 3) != ".o ")
      throw std::invalid_argument("Wrong input format");

    size_t outputDim = std::stoi(strVec[1].substr(3));
    if (dim != outputDim)
      throw std::invalid_argument("Inputs num != outputs num");
  }
  else
  {
    throw std::invalid_argument("Wrong input format");
  }

  std::vector<std::vector<NConjunct>> res(dim);
  maxEls = 0;

  for (size_t i = 3; i < strVec.size() - 1; ++i)
  {
    NConjunct nc(dim);
    std::string& str = strVec[i];
    size_t currPos = 0;
    bool outputFlag = false;
    size_t elemNum = 0;
    for (size_t cnt = 0; cnt < str.length(); ++cnt)
    {
      char c = str[cnt];
      if (c == '1')
      {
        if (!outputFlag)
        {
          nc.setMainValue(currPos, true);
          ++currPos;
          ++elemNum;
        }
        else
        {
          res[currPos].push_back(nc);
          break;
        }
      }
      else if (str[cnt] == '0')
      {
        if (!outputFlag)
        {
          nc.setMainValue(currPos, false);
        }
        ++currPos;
        ++elemNum;
      }
      else if (str[cnt] == '-')
      {
        ++currPos;
        continue;
      }
      else if (str[cnt] == ' ')
      {
        if (currPos != dim)
          throw std::runtime_error("Wrong inputs number");
        outputFlag = true;
        currPos = 0;

        if (elemNum > maxEls)
          maxEls = elemNum;
        elemNum = 0;
      }
      else
      {
        throw std::runtime_error("invalid string value:" + std::to_string(str[cnt]));
      }
    }
  }

  return res;
}

size_t printConjunctsVector(std::ostream& os, const std::vector<NConjunct>& vec, const std::string& name, size_t& tmpWireNum, const size_t incBalancedWireCnt = 0)
{
  size_t balancedWireCnt = incBalancedWireCnt;
  for (size_t i = 0; i < vec.size(); ++i)
  {
    size_t tmpMaxDepth = 0;
    const NConjunct& it = vec[i];

    for (const auto& el : it.precompiledConjs())
    {
      if (el.first > tmpMaxDepth)
        tmpMaxDepth = el.first;
    }

    if (tmpMaxDepth > 0)
      tmpMaxDepth = static_cast<size_t>(ceil(log2(tmpMaxDepth)));

    if (it.depth() == (tmpMaxDepth + static_cast<size_t>(ceil(log2(it.elementsNum())))))
    {
      if (incBalancedWireCnt == 0)
      {
        os << "assign " << name << "[" << i << "] = ";
        it.printCircuit(os);
        os << ";\n";
      }
    }
    else
    {
      std::map<size_t, std::vector<std::string>> inputEls;
      for (size_t j = 0; j < it.dim(); ++j)
      {
        if (it.mainValue(j, false) == true)
          inputEls[0].push_back("~a[" + std::to_string(j) + "]");
        else if (it.mainValue(j, true)  == true)
          inputEls[0].push_back("a[" + std::to_string(j) + "]");
      }

      for (const auto& el : it.precompiledConjs())
      {
        inputEls[el.first].push_back("commonWire" + std::to_string(el.first) + "[" + std::to_string(el.second) + "]");
      }

      os << "wire [" << (it.dim() - 1) << ":0] tmpWire" << tmpWireNum << "[" << (it.depth()) << ":0];\n";
      printBalanceCircuit(os, inputEls, tmpWireNum, name + "[" + std::to_string(incBalancedWireCnt > 0 ? balancedWireCnt : i) + "]");
      ++tmpWireNum;

      if (incBalancedWireCnt > 0)
      {
        it.setBalancedWireNum(balancedWireCnt);
        ++balancedWireCnt;
      }
    }
  }
  return balancedWireCnt;
}

void printSboxCircuitMinDNF(std::ifstream& is, std::ostream& os)
{

  size_t maxElements = 0;
  std::vector<std::vector<NConjunct>> values = readEspressoFile(is, maxElements);
  size_t dim = values.size();

  size_t startDigitsNum = (1 << (static_cast<size_t>(ceil(log2(maxElements))))) >> 1;

  std::map<size_t, std::vector<NConjunct>> commonConjuncts;

  std::map<size_t, std::vector<size_t>> sortedNumbers;
  for (size_t i = 0; i < static_cast<size_t>(1 << dim); ++i)
  {
    sortedNumbers[onesNum(i, dim)].push_back(i);
  }

  for (size_t ic = startDigitsNum; ic >= 2; --ic)
  {
    size_t commonWireNum = 0;
    for (const auto& jc : sortedNumbers.at(ic))
    {
      for (size_t kc = 0; kc < static_cast<size_t>(1 << ic); ++kc)
      {
        NConjunct nc(dim);
        nc.constructValue(jc, kc);
        size_t cnt = 0;
        std::vector<std::pair<size_t, size_t>> outputIndices;
        std::vector<std::pair<size_t, size_t>> helpIndices;
        for (size_t i = ic + 1; i <= startDigitsNum; ++i)
        {
          for (size_t j = 0; j < commonConjuncts[i].size(); ++j)
          {
            if (commonConjuncts[i][j].containsConj(nc))
            {
              NConjunct checkConj = commonConjuncts[i][j];
              checkConj.eraseConj(nc);
              checkConj.addPrecompiledConj({ic, commonWireNum});
              if (commonConjuncts[i][j].depth() == checkConj.depth())
              {
                ++cnt;
                helpIndices.push_back({i, j});
              }
            }
          }
        }
        for (size_t i = 0; i < dim; ++i)
        {
          for (size_t j = 0; j < values[i].size(); ++j)
          {
            if (values[i][j].containsConj(nc))
            {
              NConjunct checkConj = values[i][j];
              checkConj.eraseConj(nc);
              checkConj.addPrecompiledConj({ic, commonWireNum});
              if (values[i][j].depth() == checkConj.depth())
              {
                ++cnt;
                outputIndices.push_back({i, j});
              }
            }
          }
        }
        if (cnt > 1)
        {
          for (const auto& it : helpIndices)
          {
            commonConjuncts[it.first][it.second].eraseConj(nc);
            commonConjuncts[it.first][it.second].addPrecompiledConj({ic, commonWireNum});
          }
          for (const auto& it : outputIndices)
          {
            values[it.first][it.second].eraseConj(nc);
            values[it.first][it.second].addPrecompiledConj({ic, commonWireNum});
          }
          commonConjuncts[ic].push_back(nc);
          ++commonWireNum;
        }
      }
    }
  }

  os << "module sbox" << dim << "(a, z);\n";
  os << "  " << "input [" << (dim - 1) << ":0] a;\n";
  os << "  " << "output [" << (dim - 1) << ":0] z;\n\n";

  os << "// 1) common conjunction among all NConjuncts; balance if necessary\n";

  size_t tmpWireNum = 0;
  for (const auto& it : commonConjuncts)
  {
    if (!it.second.empty())
    {
      std::string name = "commonWire" + std::to_string(it.first);
      os << "wire [" << (it.second.size() - 1) << ":0] " << name << ";\n";
      printConjunctsVector(os, it.second, name, tmpWireNum);
    }
  }

  os << std::endl;

  os << "// 2) Balance individual NConjuncts if necessary\n";

  std::string name = "conjunct";
  size_t totalSize = 0;
  for (const auto& it : values)
    totalSize += it.size();
  os << "wire [" << (totalSize - 1) << ":0] " << name << ";\n";
  size_t balancedWireCnt = 1;
  for (const auto& it : values)
  {
    if (!it.empty())
    {
      balancedWireCnt = printConjunctsVector(os, it, name, tmpWireNum, balancedWireCnt);
    }
  }

  os << std::endl;
  os << "// 3) Balance result Sum of Products if necessary\n";

  for (size_t i = 0; i < dim; ++i)
  {
    size_t tmpMaxDepth = 0;
    std::map<size_t, size_t> calcSet;

    for (const auto& it : values[i])
    {
      size_t currDepth = it.depth();
      calcSet[currDepth]++;
      if (currDepth > tmpMaxDepth)
        tmpMaxDepth = currDepth;
    }

    for (size_t i = 0; i <= tmpMaxDepth; ++i)
    {
      if (i < tmpMaxDepth)
        calcSet[i + 1] += ((calcSet[i] >> 1) + (calcSet[i] & 1));
    }

    size_t totalDepth = tmpMaxDepth + static_cast<size_t>(ceil(log2(calcSet[tmpMaxDepth])));

    if (totalDepth == (tmpMaxDepth + static_cast<size_t>(ceil(log2(values[i].size())))))
    {
      os << "assign z[" << i << "] = ";
      bool first = false;
      for (const auto& it : values[i])
      {
        if (first)
          os << "|";
        else
          first = true;

        it.printCircuit(os);
      }
      os << ";\n\n";
    }
    else
    {
      std::string lastName = "z";
      std::map<size_t, std::vector<std::string>> inputEls;
      for (const auto& el : values[i])
      {
        inputEls[el.depth()].push_back(el.stringCircuit());
      }
      os << "wire [" << (values[i].size() - 1) << ":0] tmpWire" << tmpWireNum << "[" << (dim - 1) << ":0];\n";
      printBalanceCircuit(os, inputEls, tmpWireNum, lastName + "[" + std::to_string(i) + "]", false);
      os << std::endl;
      ++tmpWireNum;
    }
  }
  os << "endmodule\n";
}
