#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define UP 1
#define LEFT 2
#define UP_AND_LEFT 3
int Max(int** mat, int** r, int i, int j, int score, int gap) {

	int a = mat[i - 1][j - 1] + score;
	int b = mat[i][j - 1] - gap;
	int c = mat[i - 1][j] - gap;
	
	if (a >= b && a >= c) {
		r[i][j] = UP_AND_LEFT;
		return a;
	}
	else if (b >= a && b >= c) {
		r[i][j] = LEFT;
		return b;
	}
	else {
		r[i][j] = UP;
		return c;
	}
}


int main() {
	FILE* fp, *rfp, *wfp;
	int s, f, p;
	int m, n;
	int Score; //최종점수 
	//match : s, mismatch:f , gap:p

	int** mat;
	int** r;

	fp = fopen("input.txt", "r"); //txt 파일을 읽는다.

	char rbFile[30];
	char* xstring;
	char* ystring;
	
	//char xstring[] = "ATCGGATCT";
	//char ystring[] = "ACGGACT";
	//m = 9;
	//n = 7;

	fscanf(fp, "%s\n", rbFile); //txt 파일의 맨 윗줄은 binary 파일이름이다.

	rfp = fopen(rbFile, "rb"); 
	if (rfp == NULL) {
		fprintf(stderr, "Error.\n");
		exit(-1);
	}

	fscanf(fp, "%d %d %d\n", &s, &f, &p);
	//-------------------------------------------------------------
	
	fread(&m, sizeof(int), 1, rfp);
	fread(&n, sizeof(int), 1, rfp);
	xstring = (char*)malloc(sizeof(char) * (m + 1));
	ystring = (char*)malloc(sizeof(char) * (n + 1));
	
	//-------------------------------------------------------------

	mat = (int**)malloc(sizeof(int*) * (m + 1));
	r = (int**)malloc(sizeof(int*) * (m + 1));

	for (int i = 0; i <= m; ++i) {
		mat[i] = (int*)malloc(sizeof(int) * (n + 1));
		r[i] = (int*)malloc(sizeof(int) * (n + 1));
	}
	for (int i = 0; i <= m; ++i) {
		r[i][0] = UP;
	}
	for (int j = 0; j <= n; ++j) {
		r[0][j] = LEFT;
	}

	//-------------------------------------------------------------
	
	if (xstring == NULL || xstring == NULL) {
		fprintf(stderr, "Error: cannot allocate memory for string...\n");
	}
	
	fread(xstring, sizeof(char), m, rfp);
	fread(ystring, sizeof(char), n, rfp);
	xstring[m] = '\0';
	ystring[n] = '\0';
	

	
	//-----------------------------------------------------------------
	wfp = fopen("output.txt", "w");

	for (int i = 0; i <= m; ++i) {
		mat[i][0] = -1 * p * i;
	}
	for (int j = 0; j <= n; ++j) {
		mat[0][j] = -1 * p * j;
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			

			if (xstring[i - 1] == ystring[j - 1]) {
				mat[i][j] = Max(mat, r, i, j, s, p);
			}
			else {
				mat[i][j] = Max(mat, r, i, j,  -1* f, p);
			}
		}
		
	}
	
	int ii, jj, x_gap_count, y_gap_count;
	ii = m;
	jj = n;
	
	Score = mat[ii][jj];
	int* x_= (int*)malloc(sizeof(int) * (n + m + 1));
	int* y_= (int*)malloc(sizeof(int) * (m+ n + 1));

	x_gap_count = 0;
	y_gap_count = 0;
	int length = 0;
	
	while (1) {
		if (ii == 0 && jj == 0) break;
		//printf("ii: %d jj: %d\n", ii, jj);
		if (r[ii][jj] == UP_AND_LEFT) {
			//x_[length] = xstring[ii - 1];
			//y_[length] = ystring[jj - 1];
			ii--; jj--;

		}
		else if (r[ii][jj] == LEFT) {
			x_[length] = '-';
			x_gap_count++;
			//y_[length] = ystring[jj - 1];
			jj--;
		}
		else if (r[ii][jj] == UP){
			//x_[length] = xstring[ii - 1];
			y_[length] = '-';
			y_gap_count++;
			ii--;
		}

		length++;
	}
	
	fprintf(wfp, "%d\n", Score);
	fprintf(wfp, "%d\n", length);

	fprintf(wfp, "%d\n", x_gap_count);
	for (int i = length - 1; i >= 0; i--) {
		if (x_[i] == '-') fprintf(wfp, "%d\n", length - i);
	}
	fprintf(wfp, "%d\n", y_gap_count);
	for (int i = length - 1; i >= 0; i--) {
		if (y_[i] == '-') fprintf(wfp, "%d\n", length - i);
	}
	
	/*for (int i = length - 1; i >= 0; i--) {
		printf("%c ", x_[i]);
	}
	printf("\n");
	for (int i = length - 1; i >= 0; i--) {
		printf("%c ", y_[i]);
	}
	printf("\n");*/

	free(y_);
	free(x_);
	for (int i = 0; i <= m; ++i) {
		free(r[i]);
		free(mat[i]);
	}
	free(r);
	free(mat);
	//-------------------------------------------------------------
	free(ystring);
	free(xstring);
	//-------------------------------------------------------------
	fclose(wfp);
	fclose(rfp);
	fclose(fp);




}