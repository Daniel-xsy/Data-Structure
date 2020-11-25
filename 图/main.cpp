#include"graph.h"
#include"Queue.h"
#include"Tree.h"

int main(void)
{
	ALGraph G;

	InitDNGraph(&G);
	CreateDNGraph(&G);
	PrintDNGraph(G);
	DFSTraverse(G);
	BFSTraverse(G);
	DestroyDNGraph(&G);
	return 0;
}