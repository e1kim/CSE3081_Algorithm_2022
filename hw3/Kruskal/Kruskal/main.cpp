#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 35000000

typedef struct  {
	int u;
	int v;
	int weight;
	
} edge;


//parent의 노드와 rank을 저장하기 위한 자료구조
struct element {
	int parent;
	int rank;
};


element* parent;
int SIZE = 0;
long long** result_print;
edge* minHeap;
long long* weightSUM;

void create_graph(int n_vertices, int n_edges) {
	int i;


	parent = (element*)malloc(sizeof(element) * (n_vertices + 1));
	minHeap = (edge*)malloc(sizeof(edge) * (n_edges + 1));
	result_print = (long long**)malloc(sizeof(long long*) * (n_vertices + 1));
	weightSUM = (long long*)malloc(sizeof(long long) * (n_vertices + 1));

	for (int i = 0; i < n_vertices+1; ++i) {
		result_print[i] = (long long*)malloc(sizeof(long long) * 2);
		parent[i].parent = i;
		parent[i].rank = 1;
		weightSUM[i] = 0;
	}
	
	
}
int Find(int i)
{
	while (parent[i].parent != i) {
		i = parent[i].parent;
	}
	return i;
}
void Union(element *parent, int i, int j, int weight)
{
	int temp = parent[i].rank + parent[j].rank;
	if (parent[i].rank > parent[j].rank)
	{
		parent[i].rank = temp;
		parent[j].parent = i;
		weightSUM[i] = weightSUM[j] + weight + weightSUM[i];

	}
	else
	{
		parent[j].rank = temp;
		parent[i].parent = j;
		weightSUM[j] = weightSUM[i] + weight + weightSUM[j];
	}
}

void insertMinheap(edge eg) {
	if (SIZE == MAX) {
		printf("heap full\n");
		return;
	}
	int i = ++SIZE;
	while ((i != 1) && (eg.weight < minHeap[i / 2].weight))
	{
		minHeap[i] = minHeap[i / 2];
		i /= 2;
	}
	minHeap[i] = eg;

}

edge deleteMinHeap() {
	int parent, child;
	edge item = minHeap[1];
	edge temp;
	
	temp = minHeap[SIZE--];
	parent = 1; child = 2;
	while (child <= SIZE)
	{
		if ((child < SIZE) && (minHeap[child].weight > minHeap[child + 1].weight)) 
			child++;
		if (temp.weight <= minHeap[child].weight) 
			break;
		minHeap[parent] = minHeap[child];
		parent = child;
		child *= 2;
	}
	minHeap[parent] = temp;
	//printf("delete %d\n", item.weight);
	return item;
}
long long kruskal_MST(int vertex_num) {
	long long total_weight = 0;
	int k_scanned = 0;
	edge temp;
	int u, v, edge_count =0;
	
	
	while (SIZE > 0 && edge_count < vertex_num - 1) {
		k_scanned++;
		
		temp = deleteMinHeap();
		
		u = Find(temp.u);
		v = Find(temp.v);
		
		if (u != v) {
			total_weight += temp.weight;
			edge_count++;
			Union(parent, u, v, temp.weight);
		}
		
	}
	printf("kscanned: %d\n", k_scanned);
	
	return total_weight;


}
int main()
{
	
	char WHERE[128];
	char input_file_name[128];
	char output_file_name[128];

	FILE* fp_in, * fp_out, * fp_command, * fp;
	int n_vertices, n_edges, v_from, v_to;
	int i, connected_cnt =0;
	long long weight, max_weight, total_weight;

	
	fp_command = fopen("commands.txt", "r");

	if (!fp_command) {
		fprintf(stderr, " Error: cannot open the command file %s.\n", "commands.txt");
		exit(-1);
	}
	
	fscanf(fp_command, "%s", WHERE);
	fscanf(fp_command, "%s", input_file_name);
	fscanf(fp_command, "%s", output_file_name);


	//commands txt end
	fp = fopen(input_file_name, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error: cannot open %s.\n", input_file_name);
		exit(-1);
	}
	printf("file name is %s\n", input_file_name);
	fscanf(fp, "%d %d %lld", &n_vertices, &n_edges, &max_weight);
	fp_out = fopen(output_file_name, "w");


	////CHECK_TIME_START
	double time = clock();

	create_graph(n_vertices, n_edges); // edge init & MALLOC

	
	for (i = 0; i < n_edges; ++i) {
		fscanf(fp, "%d %d %lld", &v_from, &v_to, &weight);
		
		
		edge temp;
		temp.u = v_from;
		temp.v = v_to;
		temp.weight = weight;
		
		insertMinheap(temp);

	}
	
	
	
	
	int graph_n = 0;
	int ver = 0;
	kruskal_MST(n_vertices);
	int rank = 0;
	for (int i = 0; i < n_vertices; ++i) {
		if (parent[i].parent == i  ) {
			
			rank = parent[i].rank;
			result_print[connected_cnt][0] = rank;
			result_print[connected_cnt][1] = weightSUM[i];
			//printf("%lld %lld \n", result_print[connected_cnt][1] , weightSUM[i]);
			connected_cnt++;
		}
	}
	printf("running time is %.5f seconds\n", (clock() - time) / CLOCKS_PER_SEC);

	fprintf(fp_out, "%d\n", connected_cnt);
	for (int i = 0; i < connected_cnt; ++i) {
		fprintf(fp_out, "%d %lld\n", result_print[i][0], result_print[i][1]);
	}


	fclose(fp_command);
	fclose(fp);
	fclose(fp_command);

	
	//malloc free
	free(parent);
	free(minHeap);
	for (int i = 0;  i < n_vertices; ++i) {
		free(result_print[i]);
	}
	free(result_print);
	free(weightSUM);
	return 0;
}