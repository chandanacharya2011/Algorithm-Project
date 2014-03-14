#include <iostream>
#include <ctime>
#include <cstdlib>
#include "heap.hpp"
#include "vertex.hpp"
#include "graph.hpp"
#include "max_bandwidth.hpp"
#define KEY_TYPE double
#define VNUM 50
using namespace std;
void init_graph1(graph<KEY_TYPE,VNUM> &g0);
void init_graph2(graph<KEY_TYPE,VNUM> &g0);
void add_path(graph<KEY_TYPE,VNUM> &g0,int source,int destination);

int main(){
	struct edge<KEY_TYPE> path[VNUM];
	graph<KEY_TYPE,VNUM> g1,g2;
	init_graph1(g1);
	init_graph2(g2);
	
	add_path(g2,3,40);
	
	cout << "MBP-Using KRUSKAL" << endl;
	mbp_kruskal<KEY_TYPE,VNUM>(g2,3,40,path);
	cout << endl;
	cout << "MBP-Using Dijkstra" << endl;
	mbp_dijkstra<KEY_TYPE,VNUM>(g2,3,40,path);
	cout << endl;
	cout << "MBP-Using Dijkstra with a heap" << endl;
	return 0;
}
// First method to initialize the graph
void init_graph1(graph<KEY_TYPE,VNUM> &g0)
{	
	int i,count,ran_num;
	for(i = 1 ; i <= VNUM ; i++)
		g0.add_vertex(i,0);
	srand((unsigned)time(0));
	for (i = 1 ; i <= VNUM ; i++)
	{
		count = 0;
		while (count < 6) 
		{
			ran_num = (rand() % VNUM) + 1;
			if (!g0.is_edge(i,ran_num)) 
			{
				g0.add_edge(i,ran_num,rand() % 5000 + 1);
	//			cout <<"add:" << i << " , " << ran_num << " wt: "<<g0.edge_weight(i,ran_num)<<endl;
				count++;
			}
		}
	}
	return;
}
// Second method to initialize the graph
void init_graph2(graph<KEY_TYPE,VNUM> &g0)
{
	int i,j,ran_num;
	for(i = 1 ; i <= VNUM ; i++)
		g0.add_vertex(i,0);
	for (i = 1 ; i <= VNUM ; i++)
		for (j = i ; j <= VNUM ; j++)
		{
			ran_num = rand() % 5;
			//20% possibility
			if (ran_num == 0 && i != j) 
			{	g0.add_edge(i,j,rand() % 5000 + 1);
	//			cout <<"add:" << i << " , " << j << " wt: "<<g0.edge_weight(i,j)<<endl;
			}
		}

	return;
}
// This module needs fix
void add_path(graph<KEY_TYPE,VNUM> &g0,int s,int t)
{
	int i;
	if (!g0.is_edge(s,1) && s != 1) g0.add_edge(s,1,rand() % 5000 + 1);
	if (!g0.is_edge(t,VNUM) && t != 1) g0.add_edge(t,VNUM,rand() % 5000 + 1);
	for(i = 1; i< VNUM; i++ ) 
	{
		if (!g0.is_edge(i,i+1))
		{
			g0.add_edge(i,i+1,rand() % 5000 + 1);
		}
	
	}
	return;
}

