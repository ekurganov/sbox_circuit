#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include "vector_bool.h"

class Btree;

class TreeNode {
public:
	friend class Btree;
	TreeNode(size_t n = 0);
private:
	void SetData(const std::vector<std::vector<bool>>& rhs);
	void AddNode(const std::vector<std::vector<bool>>& data, bool left);
	size_t BuildTree();
	size_t Complexity();
	size_t Depth(const size_t currDepth);
	void PostorderPrint(int indent = 0);

	std::vector<std::vector<bool>> data;
	std::unique_ptr<TreeNode> left;
	std::unique_ptr<TreeNode> right;
};

class Btree {
public:
	Btree() : root(nullptr) {}
	void PostorderPrint();
	void BuildTree(const std::vector<std::vector<bool>>& input_data);
	size_t Complexity();
	size_t Depth();
private:
	std::unique_ptr<TreeNode> root;
};
