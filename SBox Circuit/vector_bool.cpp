#include "vector_bool.h"

using namespace std;

vector<bool> operator& (const vector<bool>& lhs, const vector<bool>& rhs) {
	vector<bool> res;
	if (lhs.size() == rhs.size()) {
		res.resize(lhs.size());
		for (size_t i = 0; i < lhs.size(); i++) {
			res[i] = lhs[i] & rhs[i];
		}
	}
	return res;
}

vector<bool> operator~ (const vector<bool>& rhs) {
	vector<bool> res(rhs.size());
	for (size_t i = 0; i < rhs.size(); i++) {
		res[i] = !rhs[i];
	}
	return res;
}

size_t HamWeight(const vector<bool>& v) {
	size_t res = 0;
	for (auto item : v) {
		if (item == true)
			res++;
	}
	return res;
}

size_t CommonsOnesNum(const std::vector<bool>& lhs, const std::vector<bool>& rhs) {
	size_t res = 0;
	for (size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] == true && rhs[i] == true)
			res++;
	}
	return res;
}

VectorPairInfo FindCommons(const std::vector<std::vector<bool>>& arr){
	size_t max, tmp_max, n_i, n_j;
	max = tmp_max = n_i = n_j = 0;
	size_t max_weight = 0, i_w = 0, j_w = 0, tmp_weight;

	for (size_t i = 0; i < arr.size(); i++)	{
		for (size_t j = i + 1; j < arr.size(); j++)	{
			tmp_max = CommonsOnesNum(arr[i], arr[j]);
			if (tmp_max > max) {
				max = tmp_max;
				n_i = i;
				n_j = j;
			}
			tmp_weight = HamWeight(arr[i]) + HamWeight(arr[j]);
			if (tmp_weight > max_weight) {
				max_weight = tmp_weight;
				i_w = i;
				j_w = j;
			}
		}
	}
	if (max > 0) {
		return { true, n_i, n_j };
	}
	else if (max_weight > 0) {
		return { false, i_w, j_w };
	}
	return { false, 0, 0 };
}

vector<vector<bool>> ReadSBox(size_t n) {
	vector<vector<bool>> res(n);
	for (size_t i = 0; i < n; i++) {
		res[i].resize(1 << n);
	}

	for (size_t i = 0; i < static_cast<size_t> (1 << n); i++) {
		size_t tmp;
		cin >> tmp;
		for (size_t j = 0; j < n; j++) {
			res[j][i] = static_cast<bool> ((tmp & (1 << j)) >> j);
		}
	}
	return res;
}