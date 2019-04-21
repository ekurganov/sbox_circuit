#include <iostream>

#include "vector_bool.h"
#include "btree.h"

using namespace std;

int main()
{
	size_t dim;
	cin >> dim;
	vector<vector<bool>> input_data(dim);
	input_data = ReadSBox(dim);

	for (size_t i = 0; i < input_data.size(); i++) {
		cout << "input_data[" << i << "]" << endl;
		cout << input_data[i] << endl;
	}

	Btree tree;
	tree.BuildTree(input_data);
	tree.PostorderPrint();
	cout << "Complexity = " << tree.Complexity() << endl;
	return 0;
}
