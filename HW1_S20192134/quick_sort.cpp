#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_types.h"
int tree = 0;

void SWAP(ELEMENT* A, ELEMENT* B) {
	
	ELEMENT tmp;

	memcpy(&tmp, A, sizeof(ELEMENT));
	memcpy(A, B, sizeof(ELEMENT));
	memcpy(B, &tmp, sizeof(ELEMENT));
}

int partition(ELEMENT data[], int left, int right) {
	int i;
	int pivot = right;
	int a, b, c;

	int number = right - left + 1;


	if (number > 3) {
		a = ELEMENT_KEY(&data[left]); b = ELEMENT_KEY(&data[(left + right) / 2]); c = ELEMENT_KEY(&data[right]);
		//a = data[left].key; b = data[(left + right) / 2].key; c = data[right].key;

		if ((a <= b) && (b <= c) || (c <= b) && (b <= a)) pivot = (left + right) / 2;
		else if ((b <= a) && (a <= c) || (c <= a) && (a <= b)) pivot = left;

	}
	
	unsigned int tmp;
	SWAP(&data[right], &data[pivot]);
	
	

	int index = left;
	for (i = left; i < right; ++i) {
		if (ELEMENT_KEY(&data[i]) < ELEMENT_KEY(&data[right])) {

			SWAP(&data[index], &data[i]);
			
			index++;

		}
	}

	SWAP(&data[right], &data[index]);
	

	return index;

}
int QUICK_SORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	int p;

	if (right - left > 0) {
		p = partition(data, left, right);
		tree++;
		QUICK_SORT(data, left, p - 1);
		QUICK_SORT(data, p + 1, right);
		
	}

	
	return 1;
}

