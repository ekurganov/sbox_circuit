#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>

#include "VectorBool.h"

class Btree;

struct NodeParams
{
	int num;
	size_t index;
	int depth;
};

class TreeNode 
{
	public:
		friend class Btree;
		TreeNode(size_t n = 0);
	private:
		void setData(const std::vector<std::vector<bool>>& rhs);
		void addNode(const std::vector<std::vector<bool>>& data, bool isLeft);
		size_t buildTree();

		size_t complexity(size_t i);
		size_t depth(const size_t currDepth);
		size_t size(size_t incSize);

		void postorderPrint(int indent = 0);
		size_t printNodes(std::ostream& os, size_t vectorsNum, size_t currNum);
		void getLeftSubtree(size_t num, size_t vectorsNum, std::vector<NodeParams>& paramsVec);

		std::vector<std::vector<bool>> m_data;
		std::vector<size_t> m_substitution;
		std::unique_ptr<TreeNode> m_left;
		std::unique_ptr<TreeNode> m_right;
		int m_leafNum;
		std::vector<int> m_depths;
};

class Btree 
{
	public:
		Btree() : m_root(nullptr) {}
		void postorderPrint();
		void buildTree(const std::vector<std::vector<bool>>& inputData);
		size_t complexity();
		size_t depth();
		void printCircuit(std::ostream& os);
		const size_t size() const;
	private:
		std::unique_ptr<TreeNode> m_root;
};
