#pragma once

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

struct Edge {			// ������ ��Ÿ���� ����ü
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// ������ ����
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

typedef struct {
	struct Edge heap[2 * MAX_VERTICES];
	int size;
} MinHeap;

extern void GenerateGraph(GraphType* g);
extern void graph_init(GraphType* g);
extern void insert_edge(GraphType* g, int start, int end, int weight);
extern void Quickkruskal(GraphType* g);
extern int parent[MAX_VERTICES + 1];		// �θ� ���
extern void set_init(int n);
extern int set_find(int curr);
extern void set_union(int a, int b);
extern void MinheapKruskal(GraphType* g);