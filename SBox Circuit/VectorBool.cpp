#include "VectorBool.h"

using std::vector;

bool operator<(const VectorPairInfo& lhs, const VectorPairInfo& rhs) 
{
	if (lhs.commonOnes != rhs.commonOnes)
		return lhs.commonOnes < rhs.commonOnes;
	else if (lhs.commonOnes == 0)
		return ((lhs.num1 + lhs.num2) < (rhs.num1 + rhs.num2));

	return false;
}

vector<bool> operator& (const vector<bool>& lhs, const vector<bool>& rhs) 
{
	vector<bool> res;

	if (lhs.size() == rhs.size()) 
	{
		res.resize(lhs.size());
		for (size_t i = 0; i < lhs.size(); i++)
			res[i] = lhs[i] & rhs[i];
	}

	return res;
}

vector<bool> operator~ (const vector<bool>& rhs) 
{
	vector<bool> res(rhs.size());

	for (size_t i = 0; i < rhs.size(); i++)
		res[i] = !rhs[i];

	return res;
}

size_t hamWeight(const vector<bool>& v) 
{
	size_t res = 0;

	for (auto item : v) 
	{
		if (item == true)
			res++;
	}

	return res;
}

VectorPairInfo commonsOnesNum(const vector<bool>& lhs, const vector<bool>& rhs) 
{
	size_t res = 0, cnt1 = 0, cnt2 = 0;

	for (size_t i = 0; i < lhs.size(); i++) 
	{
		if (lhs[i] == true) 
		{
			cnt1++;
			if (rhs[i] == true) 
			{
				cnt2++;
				res++;
			}
		}
		else if (rhs[i] == true)
		{
			cnt2++;
		}
	}

	return { res, cnt1, cnt2 };
}

VectorPairInfo findCommons(const vector<vector<bool>>& arr)
{
	size_t ni = 0, nj = 0;
	VectorPairInfo ans = { 0, 0, 0 };

	for (size_t i = 0; i < arr.size(); i++)	
	{
		for (size_t j = i + 1; j < arr.size(); j++)	
		{
			VectorPairInfo tmpCnt = commonsOnesNum(arr[i], arr[j]);

			if (ans < tmpCnt) 
			{
				ans = tmpCnt;
				ni = i;
				nj = j;
			}
		}
	}

	if (ans.num1 == 0) 
		std::swap(ni, nj);

	return { ans.commonOnes, ni, nj };
}

vector<vector<bool>> readSBox2d(std::ifstream& in)
{
	size_t n;

	if (!(in >> n)) 
		throw std::invalid_argument("Empty file");

	vector<vector<bool>> res(n);

	for (size_t i = 0; i < n; i++)
		res[i].resize(1 << n);

	for (size_t tmp, i = 0; i < static_cast<size_t>(1 << n); i++) 
	{
		if (!(in >> tmp))
			throw std::invalid_argument("Wrong number of S-Box elements");

		for (size_t j = 0; j < n; j++) 
			res[j][i] = static_cast<bool> ((tmp & (1 << j)) >> j);
	}

	return res;
}

std::vector<uint16_t> readSBox1d(std::ifstream& in)
{
  size_t n;

  if (!(in >> n))
    throw std::invalid_argument("Empty file");

  std::vector<uint16_t> res(1 << n);

  for (size_t i = 0; i < static_cast<size_t>(1 << n); ++i)
  {
    if (!(in >> res[i]))
      throw std::invalid_argument("Wrong number of S-Box elements");
  }

  return res;
}
