#include "btree.h"

TreeNode::TreeNode(size_t n) {
	left = nullptr;
	right = nullptr;
	data.resize(n);
	for (size_t i = 0; i < n; i++) {
		data[i].resize(1 << n);
	}
}

void TreeNode::SetData(const std::vector<std::vector<bool>>& rhs) {
	for (size_t i = 0; i < rhs.size(); i++) {
		data[i] = rhs[i];
	}
}

void TreeNode::AddNode(const std::vector<std::vector<bool>>& data, bool is_left) {
	std::unique_ptr<TreeNode> tmp_node(new TreeNode(data.size()));
	tmp_node->SetData(data);
	tmp_node->left = nullptr;
	tmp_node->right = nullptr;
	if (is_left) {
		left = std::move(tmp_node);
	}
	else {
		right = std::move(tmp_node);
	}
}

void TreeNode::PostorderPrint(int indent) {
	if (left != nullptr) {
		left->PostorderPrint(indent + 4);
	}
	if (right != nullptr) {
		right->PostorderPrint(indent + 4);
	}

	for (size_t i = 0; i < data.size(); i++) {
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		std::cout << data[i];
	}
	std::cout << std::endl;
}

void TreeNode::BuildTree() {
	size_t size = data.size();
	std::vector<std::vector<bool>> a(size), b(size), c(size);
	for (size_t i = 0; i < size; i++) {
		a[i].resize(1 << size);
		a[i] = data[i];
		b[i].resize(1 << size);
		c[i].resize(1 << size);
	}

	std::vector<bool> common(1 << size), diff1(1 << size), diff2(1 << size);
	bool flag = false;

	for (size_t i = 0, place = 0; i < (size / 2) + (size & 1); i++, place += 2) {
		VectorPairInfo info = FindCommons(a);
		std::vector<bool> &vec1 = a[info.num1], &vec2 = a[info.num2];
		if (info.common_ones > 0) {		// There are vectors with common ones
			flag = true;
			common = vec1 & vec2;
			diff1 = vec1 & ~common;
			diff2 = vec2 & ~common;
			b[place] = diff1;
			b[place + 1] = diff2;
			c[place / 2] = common;
		}
		else if (flag && info.num1 != info.num2) {
			b[place] = vec1;
			if (place + 1 < size) { // if size = 2k
				b[place + 1] = vec2;
			}
		}
		else {  // Both vectors are zero
			break;
		}
		std::fill(vec1.begin(), vec1.end(), false);
		std::fill(vec2.begin(), vec2.end(), false);
	}
	if (flag) {
		AddNode(b, true);
		left->BuildTree();
		AddNode(c, false);
		right->BuildTree();
	}
}

size_t TreeNode::Complexity() {
	size_t res = 0, n = data.size();

	if (left == nullptr && right == nullptr) {
		for (size_t i = 0; i < n; i++) {
			if (HamWeight(data[i]) > 1)
				res += (HamWeight(data[i]) - 1);
		}
		return res;
	}
	else {
		res += left->Complexity();
		res += right->Complexity();
		for (size_t i = 0; i < n; i++) {
			res += static_cast<size_t> (HamWeight(data[i]) > 0);
		}
		return res;
	}
}

void Btree::PostorderPrint() {
	if (root != nullptr) {
		root->PostorderPrint();
		std::cout << "\n";
	}
}

void Btree::BuildTree(const std::vector<std::vector<bool>>& input_data) {
	if (root == nullptr)	{
		root = std::make_unique<TreeNode>(input_data.size());
		root->left = nullptr;
		root->right = nullptr;
	} 
	root->SetData(input_data);
	root->BuildTree();
}

size_t Btree::Complexity() {
	if (root != nullptr) {
		return root->Complexity();
	}
	else {
		return 0;
	}
}
