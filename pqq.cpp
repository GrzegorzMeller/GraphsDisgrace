// Disgrace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>



int getMatrixElem(const int M[], const int& size, const int& x, const int& y) {
	return M[size*x + y];
}


void V_cartesian(const char S0[], const char S1[], int graphs_sizes[], char** CART) {
	auto k = 0;
	for (auto i = 0; i < graphs_sizes[1]; ++i) {
		for (auto j = 0; j < graphs_sizes[0]; ++j) {
			CART[k][0] = S0[j];
			CART[k][1] = S1[i];
			++k;
		}
	}
}


int connected(const int G[], const int& size, const int& i, const int& j) {
	auto value = getMatrixElem(G, size, (int)i - 48, (int)j - 48);
	if (value == 0)
		value = 9;
	return value;
}

bool isInB(char a, char b, const int set_size, char **B) {

	if (a == '9' || b == '9') {
		return false;
	}

	for (auto i = 0; i < set_size; ++i) {

		if (B[i][0] == a && B[i][1] == b) {
			return true;
		}

		//if (B[i].c_str() == pom)
		//return true;
	}
	return false;
}

int fill_disgrace(const int G0[], const int G1[], const int set_size, int graphs_sizes[], int DIS[], char** CART, char** B) {
	auto i = 0;
	auto adj = 0;
	for (auto l = 0; l < graphs_sizes[0] * graphs_sizes[1]; ++l) {
		for (auto k = 0; k < graphs_sizes[0] * graphs_sizes[1]; ++k) {
			int dis_0;
			int dis_1;
			if (CART[l][0] == CART[k][0]) {
				//DIS_DEBUG[i][0] = 0;
				dis_0 = 0;
			}
			else {
				auto con = connected(G0, graphs_sizes[0], CART[l][0], CART[k][0]);
				//DIS_DEBUG[i][0] = con;
				dis_0 = con;
			}
			if (CART[l][1] == CART[k][1]) {
				//DIS_DEBUG[i][1] = 0;
				dis_1 = 0;
			}
			else {
				auto con = connected(G1, graphs_sizes[1], CART[l][1], CART[k][1]);
				//DIS_DEBUG[i][1] = con;
				dis_1 = con;
			}
			//char a = DIS_DEBUG[i][0] + 48;
			//char b = DIS_DEBUG[i][1] + 48;
			char a = dis_0 + 48;
			char b = dis_1 + 48;
			char adjacent_string[2];
			//adjacent_string[0]= a;
			//adjacent_string[1] = b;
			if (isInB(a, b, set_size, B)) {
				DIS[i] = 1;
				adj++;
			}
			else {
				DIS[i] = 0;
			}
			++i;
		}
	}

	return adj / 2;
}

int max_degree(int DIS[], int size) {
	int degree = 0;
	int max = 0;
	int counter = 0;
	double sum = 0.0;
	for (auto i = 0; i < size*size; ++i) {
		if (DIS[i] == 1) degree++;

		if (((i + 1) % size) == 0) {
			//std::cout << "degree DIS[" << i << "]=" << degree << std::endl;
			if (degree > max)
				max = degree;
			sum += degree;
			degree = 0;
			counter++;
		}
	}
	double avg = 0.0;
	avg = sum / counter;
	std::cout << max << " " << floor(avg) << std::endl;
	return max;
}


int main()
{


	int N;
	std::cin >> N;
	for (int q = 0; q < N; ++q) {
		char** B;
		char** CART;
		//int** DIS_DEBUG;
		int r;
		std::cin >> r;
		int* graphs_sizes = new int[r];
		for (int m = 0; m < r; ++m) {
			int pom = 0;
			std::cin >> pom;
			graphs_sizes[m] = pom;
		}
		int b;
		std::cin >> b;
		//std::string* B = new std::string[b];
		B = new char*[b];
		for (int m = 0; m < b; ++m)
			B[m] = new char[2];

		for (int m = 0; m < b; ++m) {
			for (int n = 0; n < 2; ++n) {
				char pom;
				std::cin >> pom;
				B[m][n] = pom;
			}
		}
		int* G0 = new int[graphs_sizes[0] * graphs_sizes[0]];
		for (int n = 0; n < graphs_sizes[0] * graphs_sizes[0]; n++) {
			char a;
			std::cin >> a;
			G0[n] = a - 48;
		}
		int* G1 = new int[graphs_sizes[1] * graphs_sizes[1]];
		for (int n = 0; n < graphs_sizes[1] * graphs_sizes[1]; n++) {
			char a;
			std::cin >> a;
			G1[n] = a - 48;
		}
		char* S0 = new char[graphs_sizes[0]];
		for (int m = 0; m < graphs_sizes[0]; ++m) {
			S0[m] = m + 48;
		}
		char* S1 = new char[graphs_sizes[1]];
		for (int m = 0; m < graphs_sizes[1]; ++m) {
			S1[m] = m + 48;
		}

		int set_size = b; //? it was put as 3
		int* DIS = new int[(graphs_sizes[0] * graphs_sizes[1])*(graphs_sizes[0] * graphs_sizes[1])];

		CART = new char*[graphs_sizes[0] * graphs_sizes[1]];
		for (int m = 0; m < graphs_sizes[0] * graphs_sizes[1]; ++m)
			CART[m] = new char[graphs_sizes[0] * graphs_sizes[1]];

		/*DIS_DEBUG = new int*[(graphs_sizes[0] * graphs_sizes[1])*(graphs_sizes[0] * graphs_sizes[1])];
		for (int m = 0; m < ((graphs_sizes[0] * graphs_sizes[1])*(graphs_sizes[0] * graphs_sizes[1])); ++m)
			DIS_DEBUG[m] = new int[graphs_sizes[1]];*/

		V_cartesian(S0, S1, graphs_sizes, CART);
		auto adj = fill_disgrace(G0, G1, set_size, graphs_sizes, DIS, CART, B);
		std::cout << adj << " ";
		auto max = max_degree(DIS, graphs_sizes[0] * graphs_sizes[1]);



		//for (int m = 0; m < ((graphs_sizes[0] * graphs_sizes[1])*(graphs_sizes[0] * graphs_sizes[1])); ++m) {
		//	//std::cout << DIS_DEBUG[m];
		//	delete[] DIS_DEBUG[m];
		//}
		for (int m = 0; m < graphs_sizes[0] * graphs_sizes[1]; ++m) {
			delete[] CART[m];
		}
		delete[] CART;
		for (int m = 0; m < b; ++m) {
			delete[] B[m];
		}
		delete[] B;
		delete[] graphs_sizes;
		delete[] DIS;
		//delete[] DIS_DEBUG;
		delete[] G0;
		delete[] G1;
		delete[] S0;
		delete[] S1;
	}

	return 0;
}
