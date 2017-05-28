#include <iostream>
#include <string>
#include <time.h>

const unsigned int S1_LENGTH = 300;
const unsigned int S2_LENGTH = 250;

unsigned int DENOMINATORS[] = { 25, 20, 15, 10, 5, 2, 1 };

template <class T>
T Min(T a, T b) {
	if (a < b) {
		return a;
	}
	return b;
}

template <class T>
T Min(T a, T b, T c) {
	return Min(Min(a, b), c);
}

unsigned int LevenshteinDistanceDynamic(std::string& X, std::string& Y) {
	unsigned int** matrix = new unsigned int*[X.length() + 1];
	for (unsigned int ix = 0; ix <= X.length(); ix++) {
		matrix[ix] = new unsigned int[Y.length() + 1];
		matrix[ix][0] = ix;
	}
	for (unsigned int iy = 0; iy <= Y.length(); iy++) {
		matrix[0][iy] = iy;
	}
	for (unsigned int ix = 1; ix <= X.length(); ix++) {
		for (unsigned int iy = 1; iy <= Y.length(); iy++) {
			matrix[ix][iy] = Min(
				matrix[ix - 1][iy] + 1,
				matrix[ix][iy - 1] + 1,
				matrix[ix - 1][iy - 1] + (X[ix - 1] == Y[iy - 1] ? 0 : 1));
		}
	}
	unsigned int result = matrix[X.length()][Y.length()];
	for (unsigned int ix = 0; ix <= X.length(); ix++) {
		delete[] matrix[ix];
	}
	delete[] matrix;
	return result;
}

unsigned int LevenshteinDistanceRecursion(std::string& X, std::string& Y, unsigned int x_length, unsigned int y_length) {
	if (x_length == 0) {
		return y_length;
	}
	if (y_length == 0) {
		return x_length;
	}
	if (1 == x_length == y_length) {
		if (X == Y) {
			return 0;
		}
		else {
			return 1;
		}
	}
	unsigned int pre_x = x_length - 1;
	unsigned int pre_y = y_length - 1;
	return Min(
		LevenshteinDistanceRecursion(X, Y, pre_x, y_length) + 1,
		LevenshteinDistanceRecursion(X, Y, x_length, pre_y) + 1,
		LevenshteinDistanceRecursion(X, Y, pre_x, pre_y) + (X[pre_x] == Y[pre_y] ? 0 : 1));
}

unsigned int LevenshteinDistanceRecursion(std::string& X, std::string& Y) {
	return LevenshteinDistanceRecursion(X, Y, X.length(), Y.length());
}

char GetRandomChar() {
	return rand() % ('Z' - 'A' + 1) + 'A';
}

std::string GenerateRandomString(unsigned int length) {
	std::string result = std::string();
	for (unsigned int i = 0; i < length; i++) {
		result.push_back(GetRandomChar());
	}
	return result;
}

std::ostream& operator << (std::ostream& out, std::string& string) {
	for (unsigned int i = 0; i < string.length(); i++) {
		out << string[i];
	}
	return out;
}

std::string GetCutted(std::string& string, unsigned int size) {
	std::string result;
	for (unsigned int i = 0; i < size; i++) {
		result.push_back(string[i]);
	}
	return result;
}

int main() {
	std::string s1 = GenerateRandomString(S1_LENGTH);
	std::string s2 = GenerateRandomString(S2_LENGTH);
	for (unsigned int i = 0; i < sizeof(DENOMINATORS) / sizeof(*DENOMINATORS); i++) {
		unsigned int s1_length = S1_LENGTH / DENOMINATORS[i];
		unsigned int s2_length = S2_LENGTH / DENOMINATORS[i];
		std::string s1_cutted = GetCutted(s1, s1_length);
		std::string s2_cutted = GetCutted(s2, s2_length);
		std::cout << s1_cutted << std::endl;
		std::cout << s2_cutted << std::endl;
		time_t startTime = clock();
		unsigned int ld = LevenshteinDistanceDynamic(s1_cutted, s2_cutted);
		//unsigned int ld = LevenshteinDistanceRecursion(s1_cutted, s2_cutted);
		time_t endTime = clock();
		std::cout << "       LD = " << ld << std::endl;
		std::cout << "Used Time = " << endTime - startTime << " y.e." << std::endl;
	}

#ifdef _DEBUG
	getchar();
#endif
}
