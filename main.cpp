#define VNUM  5000
#define MAX_WEIGHT  8000
#define DEGREE  6
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "edge.hpp"
#include "graph.hpp"
#include "max_bandwidth.hpp"
#define KEY_TYPE double
using namespace std;
void init_graph1(graph<KEY_TYPE,VNUM> &g0);
void init_graph2(graph<KEY_TYPE,VNUM> &g0);
void add_path(graph<KEY_TYPE,VNUM> &g0,int source,int destination);
void print_path(vector< edge<KEY_TYPE> > path);
int main(){
	time_t t1,t2;
	int start,end;
	vector< edge<KEY_TYPE> > path;
	graph<KEY_TYPE,VNUM> g1,g2;
	// Initial the graphs.
	init_graph1(g1);
	init_graph1(g2);
	// Randomly set start and end different value
	start =  (rand() % VNUM) + 1;
	do
		end =  (rand() % VNUM) + 1;
	while(start == end);

	cout << "start:" << start <<", end:" << end << endl;
	add_path(g2,start,end);
	cout << "MBP-Using KRUSKAL" << endl;
	t1 = clock();
	mbp_kruskal<KEY_TYPE,VNUM>(g2,start,end,path);
	t2 = clock();
	print_path(path);
	cout <<"Running time: "<<  t2 - t1 << endl;
	cout << endl;
	cout << "MBP-Using Dijkstra" << endl;
	t1 = clock();
	mbp_dijkstra<KEY_TYPE,VNUM>(g2,start,end,path);
	t2 = clock();
	print_path(path);
	cout <<"Running time: "<<  t2 - t1 << endl;
	cout << endl;
	cout << "MBP-Using Dijkstra with a heap" << endl;
	t1 = clock();
	mbp_dijkstra_heap<KEY_TYPE,VNUM>(g2,start,end,path);
	t2 = clock();
	print_path(path);
	cout <<"Running time: "<<  t2 - t1 << endl;
	return 0;
}
// First method to initialize the graph
// Random regular graph , not always success, need optimized algorithm
void init_graph1(graph<KEY_TYPE,VNUM> &g0)
{	
	int i,count,ran_num,ran_num1;
	int v_degree[VNUM + 1];
	for(i = 1 ; i <= VNUM ; i++)
	{
		g0.add_vertex(i,0);
		v_degree[i] = 0;
	}
	srand((unsigned)time(0));
		count = 0;
		while (count < (DEGREE * VNUM / 2)) 
		{
			ran_num = (rand() % VNUM) + 1;
			ran_num1 = (rand() % VNUM) + 1;
			if (!g0.is_edge(i,ran_num) && v_degree[ran_num] < DEGREE && v_degree[ran_num1] < DEGREE) 
			{
				g0.add_edge(ran_num1,ran_num,rand() % MAX_WEIGHT + 1);
				//cout <<"add:" << ran_num1 << " , " << ran_num << " wt: "<<g0.edge_weight(ran_num1,ran_num)<<endl;
				v_degree[ran_num] ++;
				v_degree[ran_num1] ++;
				count++;
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
			{	g0.add_edge(i,j,rand() % MAX_WEIGHT + 1);
	//			cout <<"add:" << i << " , " << j << " wt: "<<g0.edge_weight(i,j)<<endl;
			}
		}

	return;
}
// This module needs fix
void add_path(graph<KEY_TYPE,VNUM> &g0,int s,int t)
{
	int i;
	if (!g0.is_edge(s,1) && s != 1) g0.add_edge(s,1,rand() % MAX_WEIGHT + 1);
	if (!g0.is_edge(t,VNUM) && t != 1) g0.add_edge(t,VNUM,rand() % MAX_WEIGHT + 1);
	for(i = 1; i< VNUM; i++ ) 
	{
		if (!g0.is_edge(i,i+1))
		{
			g0.add_edge(i,i+1,rand() % MAX_WEIGHT + 1);
		}
	}
	return;
}


void print_path(vector< edge<KEY_TYPE> > path)
{
	vector< edge<KEY_TYPE> >::iterator ii;
	KEY_TYPE max_bandwidth = MAX_WEIGHT + 1;
	for(ii = path.begin(); ii != path.end(); ii ++ ) 
	{
		if ((*ii).weight < max_bandwidth) max_bandwidth = (*ii).weight;
	//	cout <<"v1:" << (*ii).v1 << " , v2: " << (*ii).v2 <<" ,weight:  "<< (*ii).weight << endl;
	}
	cout << "MAX_BANDWIDTH: "<< max_bandwidth<< endl;
	return;
}
