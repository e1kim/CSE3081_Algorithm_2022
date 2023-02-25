#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 1e9+7

void RES(int* res, int** dp, int *index, int n) {

	res[0] = 0;
	index[0] = 0;
	for (int i = 0; i < n; ++i) {
		res[i+1] = INF;
		index[i + 1] = 0;
		for (int j = 0; j <= i; ++j) {
			if (dp[j][i]) {
				if (res[i+1] > res[j] + 1) {
					res[i+1] = res[j] + 1;
					index[i + 1] = j;

				}
			}
		}
	}
}
int main() {



	int testcase;
	int n, tmp;
	int least_number;

	FILE* fp, *ofp;
	fp = fopen("input.txt", "r");
	ofp = fopen("output.txt", "w");

	int* print_arr;
	fscanf(fp, "%d\n", &testcase);
	fprintf(ofp, "%d\n", testcase); // testcase Ãâ·Â

	while (testcase--) {
		fscanf(fp, "%d\n", &n);
		char* str = (char*)malloc(sizeof(char) * (n + 1));
		fscanf(fp, "%s\n", str);
		
		printf("%s\n", str);


		int** dp = (int**)malloc(sizeof(int*) * (n ));
		int* res = (int*)malloc(sizeof(int) * (n +1 ));
		int* index = (int*)malloc(sizeof(int) * (n +1 ));
		
		for (int i = 0; i < n ; ++i) {
			dp[i] = (int*)malloc(sizeof(int) * (n));
		}

		for (int i = 0; i <n; ++i) {
			for (int j = 0; j < n; ++j) {
				dp[i][j] = 0;
			}
		}
		
		for (int i = 0; i <n; ++i) {
			dp[i][i] = 1;
			if (i !=0 && str[i - 1] == str[i]) dp[i - 1][i] = 1;
			
		}
		

		for (int i = 2; i < n; ++i) {
			for (int j = 0; i+j < n; ++j) {
				if (dp[j + 1][i + j - 1] == 1 && str[j] == str[i + j]) {
					
					dp[j][i + j] = 1;
				}
			}
		}

		
		/*for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				printf("%d ", dp[i][j]);
			}printf("\n");
		}*/

		RES(res, dp, index, n);

		

		least_number = res[n];

		
		fprintf(ofp, "%d\n", least_number);

		print_arr = (int*)malloc(sizeof(int) * (least_number + 1));
		tmp = n;
		print_arr[0] = n;
		for (int i = 1; i <= least_number; ++i) {
			print_arr[i] = index[tmp];
			tmp = index[tmp];
			
		}
		for (int i = least_number; i > 0; --i) {
			for (int j = print_arr[i]; j < print_arr[i - 1]; ++j) {
				fprintf(ofp,"%c", str[j]);
			}
			fprintf(ofp,"\n");
		}

		free(print_arr);
		free(index);
		
		for (int i = 0; i < n; ++i) {
			free(dp[i]);
		}
		free(dp);
		free(str);
	}

}