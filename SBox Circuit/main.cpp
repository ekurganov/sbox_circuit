#include <iostream>

#include "VectorBool.h"
#include "BTree.h"
#include "Profile.h"

namespace 
{
	const std::string defInputPath = "input.txt";
	const size_t maxPrintThreshold = 5;
}

int main(int argc, char* argv[]) 
{
	try 
	{
		std::string inputPath = (argc == 1) ? defInputPath : std::string(argv[1]);

		if (argc > 2) 
		{
			std::cout << "Usage: <exec name> <input file path>\n";
			throw std::invalid_argument("Too lot arguments");
		}

		std::ifstream dataIn(inputPath);
		if (!dataIn)
			throw std::runtime_error("Cannot open input file " + inputPath);

		std::vector<std::vector<bool>> inputData = readSBox(dataIn);

		if (inputData.size() <= maxPrintThreshold) 
		{
			for (size_t i = 0; i < inputData.size(); i++) 
			{
				std::cout << "inputData[" << i << "]" << std::endl;
				std::cout << inputData[i] << std::endl;
			}
		}

		Btree tree;
		{
			LOG_DURATION("Build tree");
			tree.buildTree(inputData);
		}

		if (inputData.size() <= maxPrintThreshold)
			tree.postorderPrint();

		std::cout << "Complexity = " << tree.complexity() << std::endl;
		std::cout << "Depth = " << tree.depth() << std::endl;

		tree.handleLeafs();

		std::cout << tree.printCircuit();
	}
	catch (const std::exception& e) 
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
