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

const unsigned int S1_LENGTH = 300;
const unsigned int S2_LENGTH = 250;

unsigned int DENOMINATORS[] = { 25, 20, 15, 10, 5, 2, 1 };


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
		unsigned int lcs = LCS_Recursive(s1_cutted, s2_cutted);
		unsigned int lcs = LCS_Dynamic(s1_cutted, s2_cutted).length();
		time_t endTime = clock();
		std::cout << "      LCS = " << lcs << std::endl;
		std::cout << "Used Time = " << endTime - startTime << " y.e." << std::endl;
	}

#ifdef _DEBUG
	getchar();
#endif

}
