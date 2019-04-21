#include <iostream>

#include "vector_bool.h"
#include "btree.h"

int main(int argc, char* argv[])
{
	try {
		std::string input_path = (argc == 1) ? def_input_path : std::string(argv[2]);
		if (argc > 2) {
			std::cout << "Usage: <exec name> <input file path>\n";
			throw std::invalid_argument("Too lot arguments");
		}
		std::ifstream data_in(input_path);
		if (!data_in) {
			throw std::runtime_error("Cannot open input file " + input_path);
		}
		std::vector<std::vector<bool>> input_data = ReadSBox(data_in);

		for (size_t i = 0; i < input_data.size(); i++) {
			std::cout << "input_data[" << i << "]" << std::endl;
			std::cout << input_data[i] << std::endl;
		}
		Btree tree;
		tree.BuildTree(input_data);
		tree.PostorderPrint();
		std::cout << "Complexity = " << tree.Complexity() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
