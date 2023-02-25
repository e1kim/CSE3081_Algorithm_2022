#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_types.h"

void SWAP2(ELEMENT* A, ELEMENT* B) {

	ELEMENT tmp;

	memcpy(&tmp, A, sizeof(ELEMENT));
	memcpy(A, B, sizeof(ELEMENT));
	memcpy(B, &tmp, sizeof(ELEMENT));
}
int partition2(ELEMENT data[], int left, int right) {

	int i;
	int pivot = right;
	int a, b, c;

	int number = right - left + 1;

	if (number > 3) {
		a = ELEMENT_KEY(&data[left]); b = ELEMENT_KEY(&data[(left + right) / 2]); c = ELEMENT_KEY(&data[right]);
		
		if ((a <= b) && (b <= c) || (c <= b) && (b <= a)) pivot = (left + right) / 2;
		else if ((b <= a) && (a <= c) || (c <= a) && (a <= b)) pivot = left;
		
		
		
	}

	unsigned int tmp;
	SWAP2(&data[right], &data[pivot]);



	int index = left;
	for (i = left; i < right; ++i) {
		if (ELEMENT_KEY(&data[i]) < ELEMENT_KEY(&data[right])) {
			SWAP2(&data[index], &data[i]);
			index++;

		}
	}
	SWAP2(&data[right], &data[index]);

	return index;

}
int QUICK_SORT_OPT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	int pivot;
	int i;

	int f1, l1, f2, l2;

	f2 = left; l2 = right;
	int median = (left + right) / 2;
	while (l2 - f2 > 0) {
		pivot = partition2(data, f2, l2);


	if (pivot < median) {
		f1 = f2; l1 = pivot - 1;
		f2 = pivot + 1; l2 = l2;
	}
	else {
		f1 = pivot + 1; l1 = l2;
		f2 = f2; l2 = pivot - 1;
	}
	QUICK_SORT_OPT(data, f1, l1);



	}
	return 1;
}