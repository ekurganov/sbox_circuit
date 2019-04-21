#include "btree.h"

using namespace std;

Btree::Btree() {
	root = nullptr;
}

Btree::~Btree() {
	DestroyTree();
}

void Btree::DestroyTree(TreeNode *leaf) {
	if (leaf != nullptr) {
		DestroyTree(leaf->GetLeft());
		DestroyTree(leaf->GetRight());
		delete leaf;
	}
}

void Btree::AddNode(TreeNode *leaf, vector<vector<bool>> data, bool left){
	if (!root) {
		root = new TreeNode(data.size());
		root->SetData(data);
		root->SetLeft(nullptr);
		root->SetRight(nullptr);
		root->SetParent(nullptr);
	} else if (left) {
		TreeNode *tmp_node = new TreeNode(data.size());
		tmp_node->SetData(data);
		tmp_node->SetLeft(nullptr);
		tmp_node->SetRight(nullptr);
		tmp_node->SetParent(leaf);
		leaf->SetLeft(tmp_node);
	} else {
		TreeNode *tmp_node = new TreeNode(data.size());
		tmp_node->SetData(data);
		tmp_node->SetLeft(nullptr);
		tmp_node->SetRight(nullptr);
		tmp_node->SetParent(leaf);
		leaf->SetRight(tmp_node);
	}
}

void Btree::DestroyTree() {
	DestroyTree(root);
}

void Btree::PostorderPrint() {
	PostorderPrint(root);
	std::cout << "\n";
}

void Btree::PostorderPrint(TreeNode *leaf, int indent) {
	if (leaf != nullptr)
	{
		if (leaf->GetLeft())
			PostorderPrint(leaf->GetLeft(), indent + 4);
		if (leaf->GetRight())
			PostorderPrint(leaf->GetRight(), indent + 4);

		for (size_t i = 0; i < leaf->GetData().size(); i++) {
			if (indent)	{
				cout << setw(indent) << ' ';
			}
			cout << leaf->GetData()[i];
		}
		cout << endl;
	}
}

void Btree::BuildTree(const vector<vector<bool>>& input_data) {
	if (!root)	{
		root = new TreeNode(input_data.size());
		root->SetData(input_data);
		root->SetLeft(nullptr);
		root->SetRight(nullptr);
		root->SetParent(nullptr);
		BuildTree(root);
	} else {
		root->SetData(input_data);
		BuildTree(root);
	}
}

void Btree::BuildTree(TreeNode *leaf) {
	size_t size = leaf->GetData().size();

	vector < vector<bool>> a(size), b(size), c(size);
	for (size_t i = 0; i < size; i++) {
		a[i].resize(1 << size);
		b[i].resize(1 << size);
		c[i].resize(1 << size);
	}
	vector<bool> common(1 << size), diff1(1 << size), diff2(1 << size);

	size_t flag = 0;
	size_t place = 0;

	for (size_t i = 0; i < size; i++)	{
		a[i] = leaf->GetData()[i];
	}

	for (size_t i = 0; i < size / 2; i++, place += 2)	{
		VectorPairInfo info = FindCommons(a);
		vector<bool> &aa = a[info.num1], &bb = a[info.num2];
		if (info.common_ones == true) { // There are vectors with common ones
			if (!flag)
				flag = 1;

			common = aa & bb;
			diff1 = aa & ~common;
			diff2 = bb & ~common;

			b[place] = diff1;
			b[place + 1] = diff2;
			c[place / 2] = common;
		} else if (flag && info.num1 != info.num2) { // Otherwise all vectors are zero
			b[place] = aa;
			b[place + 1] = bb;
			
		} else {
			break;
		}
		fill(aa.begin(), aa.end(), false);
		fill(bb.begin(), bb.end(), false);
	}

	if (flag) {
		if (size & 1) {
			size_t max_weight = 0, num = 0;
			for (size_t i = 0; i < a.size(); i++) {
				size_t tmp = HamWeight(a[i]);
				if (tmp > max_weight) {
					max_weight = tmp;
					num = i;
				}
			}
			if (max_weight > 0)
				b[place] = a[num];
		}
		AddNode(leaf, b, true);
		BuildTree(leaf->GetLeft());
		AddNode(leaf, c, false);
		BuildTree(leaf->GetRight());
	}
}

size_t Btree::Complexity() {
	if (root)
		return Complexity(root);
	else
		return 0;
}

size_t Btree::Complexity(TreeNode *leaf) {
	size_t res = 0, n = leaf->GetData().size();

	if (leaf->GetLeft() == nullptr && leaf->GetRight() == nullptr) {
		for (size_t i = 0; i < n; i++)	{
			if (HamWeight(leaf->GetData()[i]) > 1)
				res += (HamWeight(leaf->GetData()[i]) - 1);
		}
		return res;
	} else {
		res += Complexity(leaf->GetLeft());
		res += Complexity(leaf->GetRight());
		for (size_t i = 0; i < n; i++) {
			res += static_cast<size_t> (HamWeight(leaf->GetData()[i]) > 0);
		}
		return res;
	}
}