#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#define MAX_NODE	4000000
#define MAX_EDGE	35000000



using namespace std;

typedef struct Edge {
	int from;
	int to;
	int weight;
	Edge* next;
	Edge() { from = 0, to = 0, weight = 0, next = NULL; }
	Edge(int newFrom, int newTo, int newWeight) { from = newFrom, to = newTo, weight = newWeight, next = NULL; }
} Edge;

typedef struct List {
	Edge* head;
	List() { head = NULL; }
} List;

typedef struct Heap {
	Edge heap[MAX_EDGE];
	int size;

	Heap() { size = 0; }
} Heap;


Heap h;
List* list[MAX_NODE];
int N, M;
bool st[MAX_NODE];

void insertlist(int from, int to, int weight)
{
	Edge* edge = new Edge(from, to, weight);
	
	if (list[from]->head == NULL) {
		list[from]->head = edge;
	}
	else
	{	edge->next = list[from]->head->next;
		list[from]->head->next = edge;
	}
}



void insertHeap(Heap* h, Edge edge)
{
	int idx = ++(h->size);

	while (idx != 1 && (h->heap[idx / 2].weight > edge.weight))
	{
		h->heap[idx] = h->heap[idx / 2];
		idx /= 2;
	}
	h->heap[idx] = edge;
}
Edge deleteHeap(Heap* h)
{
	Edge edge = h->heap[1];
	Edge temp = h->heap[(h->size)--];
	int parent = 1;
	int child = 2;

	while (child <= h->size)
	{
		if (child < h->size && h->heap[child].weight > h->heap[child + 1].weight)
			child++;
		if (temp.weight <= h->heap[child].weight) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return edge;
}

long long primMST(int start)
{
	long long total_weight = 0;

	Edge edge;
	h.size = 0;

	Edge* head = (Edge*)malloc(sizeof(Edge));
	head = list[start]->head;
	//printf("%d\n", list[start]->head->from);
	while (head != NULL) {
		insertHeap(&h, *head);
		head = head->next;
	}

	int k_scaned = 0;
	while (h.size != 0) {
		edge = deleteHeap(&h);

		if (!st[edge.to])
		{
			total_weight += edge.weight;
			st[edge.to] = true;
			//printf("%d\n", list[edge.to]->head->from);
			head = list[edge.to]->head;
			while (head != NULL) {
				if (!st[head->to])
					insertHeap(&h, *head);
				head = head->next;
			}

			k_scaned++;
		}
	}
	
	return total_weight;
}

int main(void)
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int i;
	
	char WHERE[128];
	char input_file_name[128];
	char output_file_name[128];

	FILE* fp_in, * fp_out, * fp ,* fp_command;
	int n_vertices, n_edges, v_from, v_to;
	
	long long weight, max_weight, total_weight;
	fp_command = fopen("commands.txt", "r");
	if (!fp_command) {
		fprintf(stderr, " Error: cannot open the command file %s.\n", "commands.txt");
		exit(-1);
	}
	fscanf(fp_command, "%s", WHERE);
	fscanf(fp_command, "%s", input_file_name);
	fscanf(fp_command, "%s", output_file_name);

	fp = fopen(input_file_name, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error: cannot open %s.\n", input_file_name);
		exit(-1);
	}
	fscanf(fp, "%d %d %lld", &n_vertices, &n_edges, &max_weight);

	fp_out = fopen(output_file_name, "w");
	if (fp_out == NULL) {
		fprintf(stderr, "Error: cannot open %s.\n", output_file_name);
		exit(-1);
	}


	//CHECK_TIME_START
	double time = clock();


	for (int i = 0; i < n_vertices; i++)//list로 adjanceny list 만들기
	{
		list[i] = new List();
	}
		

	for (i = 0; i < n_edges; ++i) {
		fscanf(fp, "%d %d %lld", &v_from, &v_to, &weight);
		
		insertlist( v_from , v_to , weight);
		insertlist( v_to , v_from , weight);
		
	}

	
	
	Edge* head;
	//자료구조 확인하기
	/*for (int i = 0; i < n_vertices; ++i) {
		printf("%d: ", i);
		Edge* temp = (Edge*)malloc(sizeof(Edge));
		temp = list[i]->head;

		while (temp != NULL) {
			printf("%d ", temp->to);
			temp = temp->next;
		}
		printf("\n");
	}*/

	long long write_weight;
	for (int i = 0; i < n_vertices; i++) st[i] = false;
	
	for (int i = 0; i < n_vertices; ++i) {
		if (st[i] == false) {
			st[i] = true;
			write_weight = primMST(i);
			printf("total weight: %lld\n", write_weight);
			fprintf(fp_out, "%lld\n", write_weight);
			
		}
	}
	printf("running time is %.5f seconds\n", (clock() - time) / CLOCKS_PER_SEC);

	//동적할당 해제하기.
	Edge* tmp;
	for (int i = 0; i < n_vertices; i++)
	{
		head = list[i]->head;
		while (head != NULL) {
			tmp = head;
			head = head->next;
			delete tmp;
		}
		delete[] list[i];
	}
	//파일 close
	fclose(fp_out);
	fclose(fp);
	fclose(fp_command);
	return 0;
}