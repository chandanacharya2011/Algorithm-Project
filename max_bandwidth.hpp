#ifndef __mbp
#define __mbp

#include <vector>
#include <algorithm>
#include "edge.hpp"
#include "heap.hpp"
#include "graph.hpp"
#include "union_find.hpp"
#define UNSEEN  0
#define FRINGE  1
#define INTREE  2
#define ON_PATH  0
#define OFF_PATH  1

template<typename key_type, int graph_size>
key_type mbp_kruskal(graph<key_type,graph_size> g0, int s, int t, vector< edge<key_type> > &path);

template<typename key_type, int graph_size>
key_type mbp_dijkstra(graph<key_type,graph_size> g0, int s, int t, vector< edge<key_type> > &path);

template<typename key_type, int graph_size>
key_type mbp_dijkstra_heap(graph<key_type,graph_size> g0, int s, int t,  vector< edge<key_type> > &path);

template<typename key_type, int graph_size>
void sort_edge (edge<key_type> edges[], int edge_num);

template<typename key_type, int graph_size>
int find_path(bool edge_flag[],adj_node<key_type> table[],int s,int t,vector< edge<key_type> > &path);

template<typename key_type>
int compare (const void * a, const void * b);

//Using Kruskal to find MBP
template<typename key_type, int graph_size>
key_type mbp_kruskal(graph<key_type,graph_size> g0, int s, int t, vector< edge<key_type> > &path)
{
	int i,j,edge_num = 0;
	bool *edge_flag  =  new bool[( graph_size +1 ) * (graph_size + 1)];
	struct adj_node<key_type>  table[graph_size + 1];
	edge<key_type>* edges = new edge<key_type>[graph_size * graph_size];
	struct adj_node<key_type>* temp;
	int degree[graph_size + 1];
	int set[graph_size + 1];
	//get all the edge information from the graph.
	g0.get_adj_table(table);
	for (i = 1 ; i <= graph_size ; i ++ )
	{
		temp = table[i].adj_v;
		while (temp != NULL) 
		{
			if ((edge_flag[i * graph_size + temp->name] == false) && (edge_flag[temp->name * graph_size + i] == false))
			{
				edges[edge_num].v1 = i;
				edges[edge_num].v2 = temp->name;
				edges[edge_num].weight = temp->weight;
				edge_num ++;
				edge_flag[i * graph_size + temp->name] = true;
			}
			temp = temp->adj_v;
		}
	}
	sort_edge<key_type,graph_size>(edges,edge_num);
	for (i = 1 ; i <= graph_size ; i ++ )
		for (j = 1 ; j <= graph_size ; j ++ )
				edge_flag[i * graph_size + j] = false;
	for (i = 1 ; i <= graph_size ; i ++ )
		make_set(set,degree,i);
	for (i = 0 ; i < edge_num; i ++ )
		if (find(set,edges[i].v1) != find(set,edges[i].v2) )
		{
			set_union(set,degree,edges[i].v1,edges[i].v2);
			edge_flag[edges[i].v1 * graph_size + edges[i].v2] = true;
		}
	find_path<key_type,graph_size>(edge_flag,table,s,t,path);
	return 0;
}
//Using Dijksta to find MBP without heap.
template<typename key_type, int graph_size>
key_type mbp_dijkstra(graph<key_type,graph_size> g0, int s, int t,  vector< edge<key_type> > &path)
{
	struct adj_node<key_type>  table[graph_size + 1];
	key_type v_table[graph_size + 1];
	short v_flag[graph_size + 1];
	int v_parent[graph_size + 1];
	key_type v_parent_weight[graph_size + 1];
	vector<int> fringe;
	int i,max_v;
	time_t t1,t2,t3=0;
	struct adj_node<key_type>* temp;
	vector<int>::iterator ii,max;
	//get all the edge information from the graph.
	g0.get_adj_table(table);
	for (i = 1; i <= graph_size ; i++) 
	{
		v_table[i] = 0;
		v_flag[i] = UNSEEN;
	}
	v_table[s] = MAX_WEIGHT + 1;
	v_flag[s] = FRINGE;
	fringe.push_back(s);
	while(!fringe.empty())
	{
		max = fringe.begin();
		t1 = clock();
		for (ii = fringe.begin(); ii != fringe.end() ; ii++) 
			if  (v_table[*ii] > v_table[*max])  max = ii;
	
	//	max = std::max_element(fringe.begin(),fringe.end(),table_compare<v_table>);
		t2 = clock();
		t3 = t3 + (t2-t1);
		max_v = *max;
		fringe.erase(max);
		v_flag[max_v] = INTREE;
		temp = table[max_v].adj_v;
		while(temp != NULL)
		{
			if (v_flag[temp->name] == UNSEEN) 
			{
				v_flag[temp->name] = FRINGE;
				fringe.push_back(temp->name);
				v_table[temp->name] = std::min(v_table[max_v],temp->weight);
				v_parent[temp->name] = max_v;
				v_parent_weight[temp->name] = temp->weight;
			}
			else if(v_flag[temp->name] == FRINGE)
			{
				if ((temp->weight > v_table[temp->name]) && (v_table[max_v] >  v_table[temp->name]))
				{
					v_parent[temp->name] = max_v;
					v_parent_weight[temp->name] = temp->weight;
					v_table[temp->name] = std::min(v_table[max_v],temp->weight);
				}	
			}
			temp = temp->adj_v;
		}
		}
	
	i = t;
	edge<key_type> edge_here;
	while( i != s) 
	{
		edge_here.v1 = v_parent[i];
		edge_here.v2 = i;
		edge_here.weight = v_parent_weight[i];
		path.push_back(edge_here);
		i = v_parent[i];
	}
	std::cout <<  " find max  edges :"<< t3 << std::endl;
	return 0;
}
//Using Dijkstra to find MBP with heap.
template<typename key_type, int graph_size>
key_type mbp_dijkstra_heap(graph<key_type,graph_size> g0, int s, int t,  vector< edge<key_type> > &path)
{
	struct adj_node<key_type>  table[graph_size + 1];
	short v_flag[graph_size + 1];
	int v_parent[graph_size + 1];
	key_type v_parent_weight[graph_size + 1];
	heap<vertex<key_type>,graph_size,value_fun<key_type>,name_fun<key_type>,key_type> fringe(true);
	vertex<key_type> max,v1;
	int i;
	struct adj_node<key_type>* temp;
	g0.get_adj_table(table);
	for (i = 1; i <= graph_size ; i++) v_flag[i] = UNSEEN;
	v1 = g0.get_v(s);
	v1.set_key(MAX_WEIGHT + 1);
	v_flag[s] = FRINGE;
	fringe.insert(v1);
	while(fringe.size())
	{
		max = fringe.max();
		temp = table[max.get_name()].adj_v;
		while(temp != NULL)
		{
			if (v_flag[temp->name] == UNSEEN) 
			{
				v_flag[temp->name] = FRINGE;
				fringe.insert(g0.get_v(temp->name));
				//Relax all the path to adjacnt vertices with the max vertex.
				v1 = fringe.index(fringe.get_index(temp->name));
				v1.set_key(std::min(max.get_key(),temp->weight));
				fringe.modify_at(fringe.get_index(temp->name),v1);
				v_parent[temp->name] = max.get_name();
				v_parent_weight[temp->name] = temp->weight;
			}
			else if(v_flag[temp->name] == FRINGE)
			{
				if (temp->weight > (fringe.index(fringe.get_index(temp->name))).get_key() )
				if  (max.get_key() > (fringe.index(fringe.get_index(temp->name))).get_key()  )
				{
					v_parent[temp->name] = max.get_name();
					v_parent_weight[temp->name] = temp->weight;
					//Relax
					v1 = fringe.index(fringe.get_index(temp->name));
					v1.set_key(std::min(max.get_key(),temp->weight));
					fringe.modify_at(fringe.get_index(temp->name),v1);
				}	
			}
			temp = temp->adj_v;
		}
			
		v_flag[max.get_name()] = INTREE;
		fringe.del_max();
	}
	i = t;
	edge<key_type> edge_here;
	while( i != s) 
	{
		edge_here.v1 = v_parent[i];
		edge_here.v2 = i;
		edge_here.weight = v_parent_weight[i];
		path.push_back(edge_here);
		i = v_parent[i];
	}
	return 0;
}
//Using heap sort to sort the edges from high weight to low weight
template<typename key_type, int graph_size>
void sort_edge ( edge<key_type> edges[], int edge_num)
{

	heap<edge<key_type>,graph_size*graph_size,value_fun_edge<key_type>,name_fun_edge<key_type>,key_type> h0(false);
	int i;
	for(i = 0; i < edge_num ; i++ ) h0.insert(edges[i]);
	for(i = 0; i < edge_num ; i++ ) 
	{
		edges[i] = h0.max();
		h0.del_max();
	}

//	qsort(edges,edge_num,sizeof(edge<key_type>),compare<key_type>);
	return;
}

// Using DFS to find the path from s to t in the Maximum Spanning Tree.
template<typename key_type, int graph_size>
int find_path(bool edge_flag[],struct adj_node<key_type> table[],int s,int t,vector< edge<key_type> > &path)
{
	
	struct adj_node<key_type>* temp;
	temp = table[s].adj_v;
	edge<key_type> edge_here;
	edge_here.v1 = s;
	while(temp != NULL) 
	{
		if(edge_flag[s * graph_size + temp->name] || edge_flag[temp->name * graph_size + s] )
		{
			edge_flag[s * graph_size + temp->name] = false;
			edge_flag[temp->name * graph_size + s] = false;
		
			if (temp->name == t)
			{
				edge_here.v2 = t;
				edge_here.weight = temp->weight;

				path.push_back(edge_here);
				return ON_PATH;
			}
			else if (find_path<key_type,graph_size>(edge_flag,table,temp->name,t,path) == 0)
			{
				edge_here.v2 = temp->name;
				edge_here.weight = temp->weight;

				path.push_back(edge_here);
				return ON_PATH;
			}
		}
		temp = temp-> adj_v;
	}
	return OFF_PATH;
}


template<typename key_type>
int compare (const void * a, const void * b)
{
  return ( (*(edge<key_type>*)b).weight - (*(edge<key_type>*)a).weight );
}

#endif



