#include "BTree.h"

#include <algorithm>

TreeNode::TreeNode(size_t n) 
{
	m_left = nullptr;
	m_right = nullptr;
	m_data.resize(n);
	m_substitution.resize(n);

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

			if (place + 1 < size)  // if size = 2k
			{
				b[place + 1] = vec2;
				m_substitution[place + 1] = info.num2;
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

size_t TreeNode::handleLeafs(size_t currNum)
{
	size_t n = m_data.size();
//	std::string res;

	if (m_left == nullptr && m_right == nullptr) 
	{
		m_leafNum = currNum;

		for (size_t i = 0; i < m_data.size(); ++i)
		{
			std::cout << "assign leafs[" << currNum << "][" << i << "] = ";

			bool first = false;
			for (size_t j = 0; j < m_data[i].size(); ++j)
			{
				if (m_data[i][j] == true)
				{
					if (first)
						std::cout <<  " | ";
					else
						first = true;

					std::cout << "conj[" + std::to_string(j) + "]";
				}
			}
			if (!first)
				std::cout << "1'b0";
			std::cout << ";\n";
		}
		std::cout << std::endl;

		return currNum + 1;
	}
	else
	{
		size_t num = m_left->handleLeafs(currNum);
		return m_right->handleLeafs(num);
	}
}

std::string TreeNode::printCircuit(size_t num)
{
	size_t n = m_data.size();
	std::string res;

	if (m_left == nullptr && m_right == nullptr) 
	{

		//size_t pos;
		//for (size_t i = 0; i < n; ++i)
		//{
		//	if (m_substitution[i] == num)
		//	{
		//		pos = i;
		//		break;
		//	}
		//}

		//bool first = false;
		//res += "(";
		//for (size_t i = 0; i < m_data[num].size(); ++i)
		//{
		//	if (m_data[num][i] == true)
		//	{
		//		if (first)
		//			res += " | ";
		//		else
		//			first = true;

		//		res += "a[" + std::to_string(i) + "]";
		//	}
		//}
		//res += ")";
		res += "leafs[" + std::to_string(m_leafNum) + "][" + std::to_string(num) + "]";
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

		res += m_left->printCircuit(pos) + " | " + m_right->printCircuit(pos / 2);

//		if (hamWeight(m_left->m_data[pos]) > 0 && hamWeight(m_right->m_data[pos / 2]) > 0)
//			res += 1;
		return res;
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

void Btree::handleLeafs()
{
	if (m_root != nullptr)
		m_root->handleLeafs(0);
	else
		return;
}

std::string Btree::printCircuit()
{
	if (m_root != nullptr)
	{
		std::string res;
		for (size_t i = 0; i < m_root->m_substitution.size(); ++i)
		{
			res += "assign z[" + std::to_string(i) + "] =  " + m_root->printCircuit(i) + ";\n";
		}
		return res;
	}
	else
	{
		return {};
  }
}

size_t Btree::depth() 
{
	if (m_root != nullptr)
		return m_root->depth(0);
	else
		return 0;
}
