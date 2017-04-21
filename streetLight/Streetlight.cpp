#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int *W, *D, ***EE, ***DD, ***PP;
ofstream outStream("output.txt");

int min(int, int, int &);
void printPP(int i, int j, int flag);

int main()
{
	int i, j, k;
	int flag;
	int num, start;
	string inputFile;

	cout << "input file name? ";
	cin >> inputFile;
	ifstream inStream(inputFile);

	inStream >> num;
	inStream >> start;

	W = new int[num + 1];
	D = new int[num + 1];
	EE = new int**[num + 1];
	DD = new int**[num + 1];
	PP = new int**[num + 1];
	for (i = 0; i < num + 1; i++) {
		EE[i] = new int*[num + 1];
		DD[i] = new int*[num + 1];
		PP[i] = new int*[num + 1];
	}
	for (i = 0; i < num + 1; i++) {
		for (j = 0; j < num + 1; j++) {
			EE[i][j] = new int[3];
			DD[i][j] = new int[3];
			PP[i][j] = new int[3];
		}
	}

	for (i = 1; i <= num; i++) {
		inStream >> D[i];
		inStream >> W[i];
	}
	

	EE[start][start][1] = 0;
	EE[start][start][2] = 0;

	for (i = 1; i <= num; i++) {
		if (i != start) {
			EE[i][i][1] = 9999;
			EE[i][i][2] = 9999;
		}
		DD[i][i][1] = 0;
		DD[i][i][2] = 0;
		PP[i][i][1] = 0;
		PP[i][i][2] = 0;

	}

	for (k = 1; k <= num; k++) {
		for (i = 1; i + k <= num; i++) {
			j = i + k;
			
			// Left
			EE[i][j][1] = min(EE[i + 1][j][1] + (DD[i + 1][j][1] + D[i + 1] - D[i]) * W[i],
								EE[i + 1][j][2] + (DD[i + 1][j][2] + D[j] - D[i]) * W[i], flag);
			if (flag == 0)
				DD[i][j][1] = DD[i + 1][j][1] + D[i + 1] - D[i];
			else
				DD[i][j][1] = DD[i + 1][j][2] + D[j] - D[i];
			if (flag == 0)
				PP[i][j][1] = i + 1;
			else
				PP[i][j][1] = j;

			//Right
			EE[i][j][2] = min(EE[i][j - 1][2] + (DD[i][j - 1][2] + D[j] - D[j - 1]) * W[j],
				EE[i][j - 1][1] + (DD[i][j - 1][2] + D[j] - D[i]) * W[j], flag);
			if (flag == 0)
				DD[i][j][2] = DD[i][j - 1][2] + D[j] - D[j - 1];
			else
				DD[i][j][2] = DD[i][j - 1][1] + D[j] - D[i];
			if (flag == 0)
				PP[i][j][2] = j - 1;
			else
				PP[i][j][2] = i;

			printf("EE[%d][%d][1] = %d, EE[%d][%d][2] = %d\n", i, j, EE[i][j][1], i, j, EE[i][j][2]);
		}
	}
	int temp = min(EE[1][num][1], EE[1][num][2], flag);
	outStream << "Watt : " << temp << '\n';
	//printf("Watt : %d\n", min(EE[1][num][1], EE[1][num][2], &lflag));
	//printf("Prev Position : %d\n", lflag == 0 ? 1 : num);
	printPP(1, num, flag);

	// delete array
	for (i = 0; i < num + 1; i++) {
		for (j = 0; j < num + 1; j++) {
			delete[] EE[i][j];
			delete[] DD[i][j];
			delete[] PP[i][j];
		}
	}
	for (i = 0; i < num + 1; i++) {
		delete[] EE[i];
		delete[] DD[i];
		delete[] PP[i];
	}
	delete[] W;
	delete[] D;
	delete[] EE;
	delete[] DD;
	delete[] PP;

	return 0;
}

int min(int a, int b, int &flag) {
	if (a <= b) {
		flag = 0;
		return a;
	}
	flag = 1;
	return b;
}

void printPP(int i, int j, int flag) {
	int temp;

	if (i == j) {
		outStream << "Prev Position : " << i << '\n';
		return;
	}
	if (flag == 0) { // L
		PP[i][j][1];
		min(EE[i + 1][j][1], EE[i + 1][j][2], temp);
		printPP(i + 1, j, temp);
	}
	else { // R
		PP[i][j][2];
		min(EE[i][j - 1][1], EE[i][j - 1][2], temp);
		printPP(i, j - 1, temp);
	}

	outStream << "Prev Position : " << (flag == 0 ? i : j) << '\n';
}


/*
void printPP(int i, int j, int flag) {
	int temp;

	if (i == j) {
		outStream << "Prev Position : " << i << '\n';
		return;
	}
	if (flag == 0) { // L
		min(EE[i + 1][j][1], EE[i + 1][j][2], &temp);
		printPP(i + 1, j, temp);
	}
	else { // R
		min(EE[i][j - 1][1], EE[i][j - 1][2], &temp);
		printPP(i, j - 1, temp);
	}
	
	outStream << "Prev Position : " << (flag == 0 ? i : j) << '\n';
}
*/

/*
DD[i][j][1] = min(DD[i + 1][j][1] + D[i + 1] - D[i],
DD[i + 1][j][2] + D[j] - D[i]);
DD[i][j][2] = min(DD[i][j - 1][2] + D[j] - D[j - 1],
DD[i][j - 1][1] + D[j] - D[i]);
*/