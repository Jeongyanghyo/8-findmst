#include <stdio.h>
#include <stdlib.h>
#include "findmst.h"

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	GenerateGraph(g);
	


	Quickkruskal(g);
	MinheapKruskal(g);
	free(g);
	return 0;
}
