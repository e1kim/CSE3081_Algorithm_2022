#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int l_n, r_n, card_n;
int* left, * right, * card;
FILE* fp, * ofp;


bool final_result, result;

int** check_card;

void card_init() {


	final_result = false;

	fscanf(fp, "%d ", &card_n);
	card = (int*)malloc(sizeof(int) * card_n);
	for (int i = 0; i < card_n; i++) {
		if (i == card_n - 1) fscanf(fp, "%d\n", &card[i]);
		else fscanf(fp, "%d ", &card[i]);
	}

	check_card = (int**)malloc(sizeof(int*) * (l_n + 1));
	for (int i = 0; i < l_n + 1; ++i) {
		check_card[i] = (int*)malloc(sizeof(int) * (r_n + 1));
	}

	for (int i = 0; i < l_n + 1; ++i) {
		for (int j = 0; j < r_n + 1; ++j) {
			check_card[i][j] = 0;
		}
	}

}
void free_check_card() {
	for (int i = 0; i < l_n + 1; ++i) {
		free(check_card[i]);
	}
	free(check_card);
}
int  dp(int l, int r, int index) {


	check_card[0][0] = 1;

	for (int i = 1; i <= l_n; ++i) {
		if (check_card[i - 1][0] && left[i - 1] == card[i - 1]) {
			check_card[i][0]=1;
		}

	}

	for (int i = 0; i <= r_n; ++i) {
		if (check_card[0][i - 1] && right[i - 1] == card[i - 1]) {
			check_card[0][i] = 1;
		}
	}
	int i, j;

	for (i = 1; i <= l_n; i++)
	{
		for (j = 1; j <= r_n; j++)
		{
			if (check_card[i - 1][j] && card[i + j - 1] == left[i - 1]) {
				check_card[i][j] = 1;
			}
			else if (check_card[i][j - 1] && card[i + j - 1] == right[j - 1]) {
				check_card[i][j] = 1;
			}
		}

	}
	
	if (check_card[l_n][r_n]) return 1;
	else return 0;




}
int main() {



	fp = fopen("input.txt", "r");
	ofp = fopen("output.txt", "w");


	fscanf(fp, "%d ", &l_n);
	left = (int*)malloc(sizeof(int) * l_n); // left 카드 동적할당하기

	for (int i = 0; i < l_n; i++) {
		if (i == l_n - 1) fscanf(fp, "%d\n", &left[i]);
		else fscanf(fp, "%d ", &left[i]);
	}
	fscanf(fp, "%d ", &r_n);
	right = (int*)malloc(sizeof(int) * r_n);
	for (int i = 0; i < r_n; i++) {
		if (i == r_n - 1) fscanf(fp, "%d\n", &right[i]);
		else fscanf(fp, "%d ", &right[i]);
	}

	

	card_init();
	

	fprintf(ofp,"%d", dp(0, 0, 0));

	free_check_card;
	card_init();

	fprintf(ofp,"%d", dp(0, 0, 0));
	free_check_card;
	
	free(card);
	free(right);
	free(left);
	fclose(ofp);
	fclose(fp);

}
