#include <stdio.h>
#include "my_types.h"
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 33554433
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
ELEMENT min_heap[MAX_ELEMENTS];
int n = 0;

void insert_min_heap(ELEMENT item, int* n);
ELEMENT delete_min_heap(int* n);


int HEAP_SORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	

    int num = right - left + 1;

    for (int i = 0; i < num; ++i) {
        insert_min_heap(data[i], &n);
    }
    for (int i = 0; i < num; ++i) {
        memcpy(&data[i], &delete_min_heap(&n), sizeof(ELEMENT));
        //data[i].key = delete_min_heap(&n);
    }
    return 1;


}


void insert_min_heap(ELEMENT item, int* n) {
    /* insert item into a max heap of current size *m */
    int i;
    i = ++(*n);
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        
    }

    while ((i != 1) && (item.key < min_heap[i / 2].key)) {
        memcpy(&min_heap[i], &min_heap[i / 2], sizeof(ELEMENT));
        //min_heap[i] = min_heap[i / 2];
        i /= 2;
    }
    memcpy(&min_heap[i], &item, sizeof(ELEMENT));
    //min_heap[i] = item;
}


ELEMENT delete_min_heap(int* n)
{
    ELEMENT item, temp;
    int child, parent;
    if (!(*n) )
    {
        
    }
    else
    {
        //item = min_heap[1];
        memcpy(&item, &min_heap[1], sizeof(ELEMENT));
        //temp = min_heap[(*n)--];
        memcpy(&temp, &min_heap[(*n)--], sizeof(ELEMENT));
        child = 2;
        parent = 1;
        while (child <= *n)
        {
            if (child < *n && min_heap[child].key > min_heap[child + 1].key) child++;
            if (temp.key < min_heap[child].key) break;
            memcpy(&min_heap[parent], &min_heap[child], sizeof(ELEMENT));
            //min_heap[parent] = min_heap[child];
            parent = child;
            child *= 2;
        }
        memcpy(&min_heap[parent], &temp, sizeof(ELEMENT));
        //min_heap[parent] = temp;

    }
    return item;
}
