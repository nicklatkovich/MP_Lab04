#include <iostream>
#include <algorithm>
#include <string>
#include "Matrix.h"

enum eDirections {
	LEFT,
	TOP,
	LEFT_TOP,
	UNDEFINED,
};

unsigned int LCS_Recursion(std::string& x, std::string& y, unsigned int x_length, unsigned int y_length) {
	if (x_length > 0 && y_length > 0) {
		if (x[x_length - 1] == y[y_length - 1]) {
			return 1u + LCS_Recursion(x, y, x_length - 1, y_length - 1);
		}
		else {
			return std::max(
				LCS_Recursion(x, y, x_length, y_length - 1),
				LCS_Recursion(x, y, x_length - 1, y_length)
			);
		}
	}
	return 0;
}

unsigned int LCS_Recursion(std::string& x, std::string& y) {
	return LCS_Recursion(x, y, x.length(), y.length());
}

void LCS_DynamicGetContent(std::string& x, Matrix<eDirections>& direction_matrix, unsigned int n, unsigned int i, unsigned int j, std::string& result) {
	if ((i > 0 && j > 0 && n > 0)) {
		if (direction_matrix.Get(i, j) == LEFT_TOP) {
			LCS_DynamicGetContent(x, direction_matrix, n - 1, i - 1, j - 1, result);
			result[n - 1] = x[i - 1];
			result[n] = 0;
		}
		else if (direction_matrix.Get(i, j) == TOP) {
			LCS_DynamicGetContent(x, direction_matrix, n, i - 1, j, result);
		}
		else {
			LCS_DynamicGetContent(x, direction_matrix, n, i, j - 1, result);
		}
	}
}

std::string LCS_Dynamic(std::string& x, std::string& y) {
	Matrix<unsigned int> matrix(x.length() + 1, y.length() + 1, 0);
	Matrix<eDirections> direction_matrix(x.length() + 1, y.length() + 1, UNDEFINED);
	for (unsigned int i = 1; i <= x.length(); i++) {
		for (unsigned int j = 1; j <= y.length(); j++) {
			if (x[i - 1] == y[j - 1]) {
				matrix.Set(i, j, matrix.Get(i - 1, j - 1) + 1);
				direction_matrix.Set(i, j, LEFT_TOP);
			}
			else if (matrix.Get(i - 1, j) >= matrix.Get(i, j - 1)) {
				matrix.Set(i, j, matrix.Get(i - 1, j));
				direction_matrix.Set(i, j, TOP);
			}
			else {
				matrix.Set(i, j, matrix.Get(i, j - 1));
				direction_matrix.Set(i, j, LEFT);
			}
		}
	}
	unsigned int length = matrix.Get(x.length(), y.length());
	std::string result;
	for (unsigned int i = 0; i <= length; i++) {
		result.push_back('\0');
	}
	LCS_DynamicGetContent(x, direction_matrix, length, x.length(), y.length(), result);
	return result;
}

int main() {
	std::string s1 = "TBHDSAV";
	std::string s2 = "KIBYSV";
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	std::cout << "LCS = " << LCS_Dynamic(s1, s2) << std::endl;

#ifdef _DEBUG
	getchar();
#endif

}
