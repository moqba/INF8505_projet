/*
** Program to find minimum spanning tree using Kruskal Algorithm with Union-Find method
** Made by - Abhishek Chand
*/

#include<stdio.h>
#include<stdlib.h>

//*************************** DEFINE AND STRUCTS *************************** //
#define TEST_KRUSKAL
#define N_VERTEX 5
#define N_EDGES 9
#define USE_CUSTOM_INSTRUCTION
typedef struct EDGE
{
	int u;
	int v;
	int w;
}Edge;

//*************************** PRIVATE VARIABLES **************************** //
int parent[N_VERTEX],rank[N_VERTEX];

Edge E[] = { 
	#include "in.data"
};

Edge REF_OUT[] = { 
	#include "refout.data"
};

Edge OUT[N_VERTEX-1]; 

//******************************* FUNCTIONS ******************************** //
void swap(Edge *x,Edge *y){
#ifdef USE_CUSTOM_INSTRUCTION
	swap_hw(x->u, y->u, x->u, y->u);
	swap_hw(x->v, y->v, x->v, y->v);
	swap_hw(x->w, y->w, x->w, y->w);
#else
	Edge temp;
	temp=*x;
	*x=*y;
	*y=temp;
#endif
}


void printMST(Edge *T,int n)
{
	int i,cost=0;
	printf("Selected Edges:\nu  v  w\n");
	for(i=0;i<n;i++)
	{
		printf("%d  %d  %d\n",T[i].u,T[i].v,T[i].w);
		cost+=T[i].w;
	}
	printf("\nCost = %d",cost);
}

int partition(Edge *A,int beg,int end)
{
	int i,p=beg,pivot=A[end].w; // The pivot is always the last one
	for(i=beg;i<end;i++) // Partitioning is theta(n)
	{
		if(A[i].w<=pivot)
		{
			swap(&A[i],&A[p]);
			p++;
		}
	}
	swap(&A[end],&A[p]);
	return p;
}

void quicksort(Edge *A,int beg,int end){
	int q;
	if(beg>=end)
		return;
	q=partition(A,beg,end);
	quicksort(A,beg,q-1);
	quicksort(A,q+1,end);
}

int find(int u, int *p){
	int i=0,A[N_VERTEX];
	while(u!=parent[u]){
		A[i]=u;
		u=parent[u];
		i++;
	}
	i--;
	while(i>=0){
		parent[A[i]]=u;
		i--;
	}
	return u;
}

void unionbyrank(int u, int v)
{
	int x,y;
	x=find(u, parent);
	y=find(v, parent);
	if(rank[x]<rank[y])
		parent[x]=y;
	else if(rank[y]<rank[x])
		parent[y]=x;
	else
	{
		parent[x]=y;
		rank[y]++;
	}
}

void Kruskal(Edge *E,int n,int e, Edge *T)
{
	for(int i=1;i<N_VERTEX+1;i++)
	{
		parent[i]=i;
		rank[i]=0;
	}
	
	int i,j,x,y,u,v;
	quicksort(E,0,e-1);
	j=0;
	for(i=0;i<e;i++)
	{
		if(j==n-1)
			break;
		u=E[i].u;
		v=E[i].v;
		x=find(u, parent);
		y=find(v, parent);
		if(x!=y)
		{
			T[j]=E[i];
			unionbyrank(x,y);
			j++;
		}
	}
}

int run_kruskal(){ 
	Kruskal(E, N_VERTEX, N_EDGES, OUT);

	int n_errors=0;
  	for (int i=0; i<(N_VERTEX-1); i++) {
		if (
			OUT[i].u != REF_OUT[i].u 
			|| OUT[i].v != REF_OUT[i].v 
			|| OUT[i].w != REF_OUT[i].w) {
			n_errors++;
		}
	}
	if (n_errors==0) {
		printf("OK (nr=%d)\n",sizeof(REF_OUT)/sizeof(Edge));
	}
	else {
		printf("ERROR (nr=%d)\n",n_errors);
	}
	return n_errors;
}

#ifdef TEST_KRUSKAL

int main(){ 
	return run_kruskal();
}
#endif
