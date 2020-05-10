#include <iostream>

#include "vector_bool.h"
#include "btree.h"
#include "profile.h"

namespace {
	const std::string def_input_path = "input.txt";
	const size_t max_print_threshold = 5;
}

int main(int argc, char* argv[]) {
	try {
		std::string input_path = (argc == 1) ? def_input_path : std::string(argv[1]);
		if (argc > 2) {
			std::cout << "Usage: <exec name> <input file path>\n";
			throw std::invalid_argument("Too lot arguments");
		}
		std::ifstream data_in(input_path);
		if (!data_in) {
			throw std::runtime_error("Cannot open input file " + input_path);
		}
		std::vector<std::vector<bool>> input_data = ReadSBox(data_in);

		if (input_data.size() <= max_print_threshold) {
			for (size_t i = 0; i < input_data.size(); i++) {
				std::cout << "input_data[" << i << "]" << std::endl;
				std::cout << input_data[i] << std::endl;
			}
		}
		Btree tree;
		{
			LOG_DURATION("Build tree");
			tree.BuildTree(input_data);
		}
		if (input_data.size() <= max_print_threshold) {
			tree.PostorderPrint();
		}
		std::cout << "Complexity = " << tree.Complexity() << std::endl;
		std::cout << "Depth = " << tree.Depth() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
