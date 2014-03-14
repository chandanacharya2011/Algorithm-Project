#include"union_find.hpp"
void make_set(int set[], int degree[], int v)
{
	set[v] = 0;
	degree[v] = 0;
	return;
}
// No path compression
int find(int set[],int v)
{
	int v1;
	v1 = v;
	while(set[v1] != 0) v1 = set[v1];
	return v1;
}
void set_union(int set[], int degree[],int v1,int v2)
{
	v1 = find(set,v1);
	v2 = find(set,v2);

	if (degree[v1] > degree[v2]) set[v2] = v1;
	else if  (degree[v1] < degree[v2]) set[v1] = v2;
	else
	{
		set[v1] = v2; 
		degree[v2]++;			
	}
	return;
}
