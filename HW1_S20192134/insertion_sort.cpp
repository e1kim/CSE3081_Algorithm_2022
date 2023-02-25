#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_types.h"




int INSERTION_SORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	int i, j;
	
	ELEMENT temp;
	if (data == NULL ) return 0;

	for (i =  1; i <= right; i++)
	{
		memcpy(&temp, &data[i], sizeof(ELEMENT));
		j = i;
		while ((j > 0) && (temp.key < data[j - 1].key)) {
			memcpy(&data[j], &data[j-1], sizeof(ELEMENT));
			j--;
		}
		memcpy(&data[j], &temp, sizeof(ELEMENT));
	}
	return 1;
}