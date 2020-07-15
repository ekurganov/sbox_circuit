#include <iostream>

#include "VectorBool.h"
#include "BTree.h"
#include "Profile.h"
#include "Args.h"
#include "SimpleMethods.h"

namespace 
{
	const std::string defInputPath = "input.txt";
	const size_t maxPrintThreshold = 5;
}

int main(int argc, char* argv[]) 
{
	try 
	{
		Args args;
		args.readOpts(argc, argv);

		std::ifstream dataIn(args.inputPath_);
		if (!dataIn)
			throw std::runtime_error("Cannot open input file " + args.inputPath_);

		std::streambuf* buf;
		std::ofstream of;

		if (!args.outputPath_.empty())
		{
		  of.open(args.outputPath_);
		  buf = of.rdbuf();
		}
		else
		{
		  buf = std::cout.rdbuf();
		}
		std::ostream out(buf);

		if (args.meth_ == mNewMeth)
		{
      std::vector<std::vector<bool>> inputData = readSBox2d(dataIn);

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

  //		std::cout << "Complexity = " << tree.complexity() << std::endl;
      std::cout << "Depth = " << tree.depth() << std::endl;

      tree.printCircuit(out);
		}
		else if (args.meth_ != mMinDNF)
		{
		  std::vector<uint16_t> inputData = readSBox1d(dataIn);
		  if (args.meth_ == mSimple)
		  {
		    printSboxCircuitSimple(inputData, out);
		  }
		  else if (args.meth_ == mUpgSimple)
		  {
		    printSboxCircuitUpgSimple(inputData, out);
		  }
		  else if (args.meth_ == mShannon)
		  {
		    printSboxCircuitShannon(inputData, out);
		  }
		}
	}
	catch (const std::exception& e) 
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
