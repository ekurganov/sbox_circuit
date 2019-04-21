#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include "vector_bool.h"

class TreeNode {
private:
	std::vector<std::vector<bool>> data;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
public:
	TreeNode(int n = 0)
	{
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		data.resize(n);
		for (int i = 0; i < n; i++) {
			data[i].resize(1 << n);
		}
	}
	const std::vector<std::vector<bool>>& GetData() const { return data; }
	void SetData(const std::vector<std::vector<bool>>& rhs) {
		for (size_t i = 0; i < rhs.size(); i++)	{
			data[i] = rhs[i];

		}
	}
	TreeNode* GetLeft() const { return left; }
	TreeNode* GetRight() const { return right; }
	TreeNode* GetParent() const { return parent; }
	void SetLeft(TreeNode *rhs) { left = rhs; }
	void SetRight(TreeNode *rhs) { right = rhs; }
	void SetParent(TreeNode *rhs) { parent = rhs; }
};

class Btree {
public:
	Btree();
	~Btree();

	void AddNode(TreeNode *leaf, std::vector<std::vector<bool>> data, bool left);
	void DestroyTree();
	void PostorderPrint();
	void BuildTree(const std::vector<std::vector<bool>>& input_data);
	size_t Complexity();

private:
	void DestroyTree(TreeNode *leaf);
	void PostorderPrint(TreeNode *leaf, int indent = 0);
	void BuildTree(TreeNode *leaf);
	size_t Complexity(TreeNode *leaf);
	TreeNode *root;
};
