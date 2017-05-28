#include <iostream>
#include <algorithm>
#include <string>

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

int main() {
	std::string s1 = "TBHDSAV";
	std::string s2 = "KIBYSV";
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	std::cout << "LCS = " << LCS_Recursion(s1, s2) << std::endl;

#ifdef _DEBUG
	getchar();
#endif

}
