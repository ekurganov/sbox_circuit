#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>



struct VectorPairInfo {
	size_t common_ones;
	size_t num1;
	size_t num2;
};

bool operator<(const VectorPairInfo& lhs, const VectorPairInfo& rhs);

template <typename T>
std::ostream& operator<<(std::ostream &stream, const std::vector<T>& v) {
	for (auto item : v) {
		stream << item << ' ';
	}
	stream << std::endl;
	return stream;
}

std::vector<bool> operator& (const std::vector<bool>& lhs, const std::vector<bool>& rhs);
std::vector<bool> operator~ (const std::vector<bool>& rhs);
size_t HamWeight(const std::vector<bool>& v);
VectorPairInfo CommonsOnesNum(const std::vector<bool>& lhs, const std::vector<bool>& rhs);
VectorPairInfo FindCommons(const std::vector<std::vector<bool>> &arr);

std::vector<std::vector<bool>> ReadSBox(std::ifstream& in);

