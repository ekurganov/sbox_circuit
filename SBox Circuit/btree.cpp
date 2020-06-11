#include "BTree.h"

#include <algorithm>
#include <map>

TreeNode::TreeNode(size_t n) 
{
	m_left = nullptr;
	m_right = nullptr;
	m_data.resize(n);
	m_substitution.resize(n);
	m_depths.resize(n);

	for (size_t i = 0; i < n; i++)
	{
		m_data[i].resize(1 << n);
		m_substitution[i] = n;
	}
}

void TreeNode::setData(const std::vector<std::vector<bool>>& rhs) 
{
	for (size_t i = 0; i < rhs.size(); i++) 
		m_data[i] = rhs[i];
}

void TreeNode::addNode(const std::vector<std::vector<bool>>& data, bool isLeft) 
{
	std::unique_ptr<TreeNode> tmpNode(new TreeNode(data.size()));
	tmpNode->setData(data);
	tmpNode->m_left = nullptr;
	tmpNode->m_right = nullptr;
	tmpNode->m_leafNum = -1;
	for (auto& it : m_depths)
		it = -1;

	if (isLeft) 
		m_left = std::move(tmpNode);
	else 
		m_right = std::move(tmpNode);
}

void TreeNode::postorderPrint(int indent) 
{
	if (m_left != nullptr)
		m_left->postorderPrint(indent + 4);

	if (m_right != nullptr) 
		m_right->postorderPrint(indent + 4);

	for (size_t i = 0; i < m_data.size(); i++) 
	{
		if (indent) 
			std::cout << std::setw(indent) << ' ';
		std::cout << m_data[i];
	}
	std::cout << std::endl;
}

size_t TreeNode::buildTree() 
{
	size_t size = m_data.size(), res = 0;
	std::vector<std::vector<bool>> a(size), b(size), c(size);
	for (size_t i = 0; i < size; i++) 
	{
		a[i].resize(1 << size);
		a[i] = m_data[i];
		b[i].resize(1 << size);
		c[i].resize(1 << size);
	}

	std::vector<bool> common(1 << size), diff1(1 << size), diff2(1 << size);
	bool flag = false;

	for (size_t i = 0, place = 0; i < (size / 2) + (size & 1); i++, place += 2) 
	{
		VectorPairInfo info = findCommons(a);
		std::vector<bool> &vec1 = a[info.num1], &vec2 = a[info.num2];

		if (info.commonOnes > 0) // There are vectors with common ones
		{		
			common = vec1 & vec2;
			diff1 = vec1 & ~common;
			diff2 = vec2 & ~common;

			b[place] = diff1;
			b[place + 1] = diff2;
			c[place / 2] = common;

			m_substitution[place] = info.num1;
			m_substitution[place + 1] = info.num2;

			flag = true;
			res += 2;
		}
		else if (flag && info.num1 != info.num2) 
		{
			b[place] = vec1;
			m_substitution[place] = info.num1;
			++place;

			if (place < size)  // if size = 2k
			{
				b[place] = vec2;
				m_substitution[place] = info.num2;
				++place;
			}
		}
		else   // Both vectors are zero
		{  
			for (size_t i = place; i < size; ++i)
			{
				m_substitution[i] = i;
			}
			break;
		}

		std::fill(vec1.begin(), vec1.end(), false);
		std::fill(vec2.begin(), vec2.end(), false);
	}
	if (flag) 
	{
		addNode(b, true);
		res += m_left->buildTree();

		addNode(c, false);
		res += m_right->buildTree();
	}
	else
	{
		for (size_t i = 0; i < m_data.size(); ++i) 
		{
			if (hamWeight(m_data[i]) > 1) 
				res += (hamWeight(m_data[i]) - 1);
		}
	}
	return res;
}

size_t TreeNode::complexity(size_t num)
{
	size_t res = 0, n = m_data.size();

	if (m_left == nullptr && m_right == nullptr) 
	{
		if (hamWeight(m_data[num]) > 1)
			res += (hamWeight(m_data[num]) - 1);
		return res;
	}
	else
	{
		size_t pos;
		for (size_t i = 0; i < n; ++i)
		{
			if (m_substitution[i] == num)
			{
				pos = i;
				break;
			}
		}

		res = m_left->complexity(pos);
		if ((pos & 1) == 0) 
		{
			res += m_right->complexity(pos / 2);
		}

		if (hamWeight(m_left->m_data[pos]) > 0 && hamWeight(m_right->m_data[pos / 2]) > 0)
			res += 1;
		return res;
	}
}

size_t getVectorsNum(std::vector<std::vector<bool>> vec)
{
	size_t res = 0;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		size_t cnt = 0;
		for (size_t j = 0; j < vec[i].size(); ++j)
		{
			if (vec[i][j] == true)
				++cnt;
		}
		if (cnt > 0)
			++res;
	}
	return res;
}

size_t printBalanceCircuit(const std::vector<NodeParams>& inputVec, const size_t num, const size_t ind)
{
  std::map<size_t, std::vector<std::string>> workMap;
  size_t maxDepth = 0, totalDepth;
  for (const auto& it : inputVec)
  {
    if (it.depth > maxDepth)
      maxDepth = it.depth;

    workMap[it.depth].push_back("nodes[" + std::to_string(it.num) + "][" + std::to_string(it.index) + "]");
  }
  
  //for (const auto& itVec : workMap)
  //{
  //  for (const auto& it: itVec.second)
  //    std::cout << "(" << it << ", " << itVec.first << ")\n";
  //}
  //std::cout << std::endl;

  for (const auto& itVec : workMap)
  {
    bool pairStarted = false;
    if (itVec.first < maxDepth)
    {
      size_t cnt = 0;
      for (const auto& it : itVec.second)
      {
        if (!pairStarted)
        {
          std::cout << "assign tmpWire[" << itVec.first + 1 << "][" << cnt << "] = " << it;
          pairStarted = true;
        }
        else
        {
          std::cout << " | " << it << ";\n";
          pairStarted = false;
          workMap[itVec.first + 1].push_back("tmpWire[" + std::to_string(itVec.first + 1) + "][" + std::to_string(cnt) + "]");
          ++cnt;
        }
      }
      if (pairStarted)
      {
        std::cout << ";\n";
        workMap[itVec.first + 1].push_back("tmpWire[" + std::to_string(itVec.first + 1) + "][" + std::to_string(cnt) + "]");
      }
    }
    else // last element, max depth
    {
      std::cout << "assign nodes[" << num << "][" << ind << "] = ";
      for (const auto& it : itVec.second)
      {
        if (!pairStarted)
          pairStarted = true;
        else
          std::cout << " | ";
        std::cout << it;        
      }
      std::cout << "; \n";
			totalDepth = itVec.first + static_cast<size_t>(ceil(log2(itVec.second.size())));
      std::cout << "// Total depth = " << totalDepth << std::endl;
    }
  }
	return totalDepth;
}

size_t TreeNode::printNodes(size_t vectorsNum, size_t currNum)
{
	if (m_left == nullptr && m_right == nullptr)
	{
		if (m_leafNum != -1)
			return currNum;

		m_leafNum = currNum;

		for (size_t i = 0; i < m_data.size(); ++i)
		{
			m_depths[i] = static_cast<int>(ceil(log2(hamWeight(m_data[i]))));
			std::cout << "assign nodes[" << currNum << "][" << i << "] = ";

			bool first = false;
			for (size_t j = 0; j < m_data[i].size(); ++j)
			{
				if (m_data[i][j] == true)
				{
					if (first)
						std::cout << " | ";
					else
						first = true;

					std::cout << "conj[" << j << "]";
				}
			}
			if (!first)
				std::cout << "1'b0";
			std::cout << ";\n";
		}
		std::cout << std::endl;

		return currNum + 1;
	}

	size_t nodeNum = getVectorsNum(m_data);

	if (nodeNum > vectorsNum)
	{
		size_t num = m_left->printNodes(vectorsNum, currNum);
		return m_right->printNodes(vectorsNum, num);
	}
	else if (nodeNum == vectorsNum) // This is right child
	{
		m_leafNum = currNum;

		for (size_t i = 0; i < vectorsNum; ++i)
		{
			size_t pos;
			for (size_t j = 0; j < m_data.size(); ++j)
			{
				if (m_substitution[j] == i)
				{
					pos = j;
					break;
				}
			}
//			std::cout << "assign nodes[" << currNum << "][" << i << "] = ";
			std::vector<NodeParams> paramsVec;
			m_left->getLeftSubtree(pos, vectorsNum, paramsVec);
			if (pos + static_cast<size_t>((pos & 1) == 0) < vectorsNum)
				//std::cout << " | nodes[" << m_right->m_leafNum << "][" << pos / 2 << "]";
				paramsVec.push_back({m_right->m_leafNum, pos / 2, m_right->m_depths[pos / 2]});
//			std::cout << ";\n";
			m_depths[i] = printBalanceCircuit(paramsVec, currNum, i);
		}
		for (size_t i = vectorsNum; i < m_data.size(); ++i)
			std::cout << "assign nodes[" << currNum << "][" << i << "] = 1'b0;\n";

		std::cout << std::endl;
		return currNum + 1;
	}
	else
		throw std::runtime_error("ERROR in tree");
}

void TreeNode::getLeftSubtree(size_t num, size_t vectorsNum, std::vector<NodeParams>& paramsVec)
{
	if (m_left == nullptr && m_right == nullptr)
	{
		paramsVec.push_back({m_leafNum, num, m_depths[num]});
//		std::cout << "nodes[" << m_leafNum << "][" << num << "]";
	}
	else
	{
		size_t pos;
		for (size_t i = 0; i < m_data.size(); ++i)
		{
			if (m_substitution[i] == num)
			{
				pos = i;
				break;
			}
		}
		m_left->getLeftSubtree(pos, vectorsNum, paramsVec);
		if (pos + static_cast<size_t>((pos & 1) == 0) < vectorsNum)
			paramsVec.push_back({m_right->m_leafNum, pos / 2, m_right->m_depths[pos / 2]});
//			std::cout << " | nodes[" << m_right->m_leafNum << "][" << pos / 2 << "]";
	}
}

size_t TreeNode::depth(const size_t currDepth) 
{
	if (m_left == nullptr && m_right == nullptr)
	{
		size_t maxWt = 0;
		for (const auto& vec : m_data)
		{
			size_t wt = hamWeight(vec);
			if (wt > maxWt)
				maxWt = wt;
		}
		if (maxWt > 0)
			return currDepth + static_cast<size_t>(ceil(log2(maxWt)));
		else
			return currDepth;
	}
	else
	{
		return std::max(m_left->depth(currDepth + 1), m_right->depth(currDepth + 1));
	}
}

void Btree::postorderPrint() 
{
	if (m_root != nullptr) 
	{
		m_root->postorderPrint();
		std::cout << "\n";
	}
}

void Btree::buildTree(const std::vector<std::vector<bool>>& inputData) 
{
	if (m_root == nullptr)	
	{
		m_root = std::make_unique<TreeNode>(inputData.size());
		m_root->m_left = nullptr;
		m_root->m_right = nullptr;
	} 

	m_root->setData(inputData);
	std::cout << "Build Time Complexity = " << m_root->buildTree() << std::endl;
}

size_t Btree::complexity()
{
	if (m_root != nullptr)
	{
		size_t res = 0;
		for (size_t i = 0; i < m_root->m_substitution.size(); ++i)
		{
			size_t tmp = m_root->complexity(i);
			std::cout << "complexity " << i << " = " << tmp << std::endl;
			res += tmp;
		}
		return res;
	}
	else
	{
		return 0;
  }
}

void Btree::printCircuit()
{
	if (m_root != nullptr)
	{
		size_t nodesNum = 0;
		size_t n = m_root->m_data.size();
		std::vector<size_t> vecSeq;
		for (size_t i = n; i > 0; i >>= 1)
			vecSeq.push_back(i);
		std::reverse(vecSeq.begin(), vecSeq.end());

		for (const auto num : vecSeq)
		{
			std::cout << "//-------- " << num << " --------\n";
			nodesNum = m_root->printNodes(num, nodesNum);
			//std::cout << "-------- " << num << " --------\n";
		}

		std::cout << std::endl;

		for (size_t i = 0; i < n; ++i)
			std::cout << "assign z[" << i << "] = nodes[" << nodesNum - 1 << "][" << i << "];\n";
	}
	else
	{
		return;
	}
}

size_t Btree::depth() 
{
	if (m_root != nullptr)
		return m_root->depth(0);
	else
		return 0;
}
