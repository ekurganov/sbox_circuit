#pragma once
#include <string>
#include <vector>

const std::string defaultInputPath = "input.txt";

enum SynthMethod {
	mSimple,
  mUpgSimple,
  mShannon,
  mLupanov,
  mMinDNF,
  mNewMeth
};

struct Args {
	SynthMethod meth_;
	std::string inputPath_;
	std::string outputPath_;

	Args() {}

	void readOpts(int argc, char *argv[]);

private:
	std::vector <std::string> m_tokens;
};


void Args::readOpts(int argc, char *argv[]) 
{
	if (argc != 3 && argc != 5 && argc != 7)
  {
		std::cout << "\nUsage: <program name> --method methName [--infile inputfile] [--outfile outputfile]\n";
		throw std::invalid_argument("Incorrect number of options");
	}

	for (int i = 1; i < argc; ++i) 
  {
		m_tokens.push_back(std::string(argv[i]));
	}

	for (size_t i = 0; i < m_tokens.size(); i += 2)
  {
		if (m_tokens[i] == "--method")
    {
      std::string methName(m_tokens[i + 1]);
      if (methName == "simple")
        meth_ = SynthMethod::mSimple;
      else if (methName == "upgSimple")
        meth_ = SynthMethod::mUpgSimple;
      else if (methName == "Shannon")
        meth_ = SynthMethod::mShannon;
      else if (methName == "Lupanov")
        meth_ = SynthMethod::mLupanov;
      else if (methName == "minDNF")
        meth_ = SynthMethod::mMinDNF;
      else if (methName == "newMethod")
        meth_ = SynthMethod::mNewMeth;
			else
				throw std::invalid_argument("Incorrect method");
		}
		else if (m_tokens[i] == "--infile")
    {
			inputPath_ = m_tokens[i + 1];
		}
		else if (m_tokens[i] == "--outfile")
    {
			outputPath_ = m_tokens[i + 1];
		}
		else 
    {
			throw std::invalid_argument("Incorrect option");
		}
	}

  if (inputPath_.empty())
    inputPath_ = defaultInputPath;
}
