#include <stdio.h>
#include <stdlib.h>
#include "findmst.h"
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

//그래프의 노드와 간선, 비용값을 삽입
void GenerateGraph(GraphType* g) {
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);
}

int parent[MAX_VERTICES+1];		// 부모 노드
// 초기화
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (curr < 0 || curr >= MAX_VERTICES + 1) {
		fprintf(stderr, "Error: curr index out of bounds\n");
		exit(EXIT_FAILURE);
	}
	if (parent[curr] == -1)
		return curr; // 루트
	else
		return parent[curr] = set_find(parent[curr]); // 경로 압축
}

void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}


void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

void Quickkruskal(GraphType* g)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;	// 정점 u와 정점 v의 집합 번호
	int number_of_nodes = 10;
	struct Edge e;

	set_init(g->n);				// 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Quick Based Kruscal \n");
	int i = 0;
	while (edge_accepted < (number_of_nodes - 1))	// 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d, % d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
	printf("\n");
}

void init_min_heap(MinHeap* h) {
	h->size = 0;
}

void insert_min_heap(MinHeap* h, struct Edge e) {
	int i = ++(h->size);
	while ((i != 1) && (e.weight < h->heap[i / 2].weight)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = e;
}

struct Edge delete_min_heap(MinHeap* h) {
	int parent, child;
	struct Edge item, temp;

	item = h->heap[1];
	temp = h->heap[(h->size)--];

	parent = 1;
	child = 2;
	while (child <= h->size) {
		if ((child < h->size) && (h->heap[child].weight > h->heap[child + 1].weight))
			child++;
		if (temp.weight <= h->heap[child].weight)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void MinheapKruskal(GraphType* g)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;	// 정점 u와 정점 v의 집합 번호
	int number_of_nodes = 10;
	struct Edge e;
	MinHeap heap;

	set_init(g->n);				// 집합 초기화
	init_min_heap(&heap);

	// 모든 간선을 최소 힙에 삽입
	for (int i = 0; i < g->n; i++) {
		insert_min_heap(&heap, g->edges[i]);
	}

	printf("Heap Based Kruskal \n");
	while (edge_accepted < (number_of_nodes - 1))	// 간선의 수 < (n-1)
	{
		e = delete_min_heap(&heap);
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
	}
}
