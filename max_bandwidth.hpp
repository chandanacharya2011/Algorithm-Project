#ifndef __mbp
#define __mbp

#include <vector>
#include <algorithm>
#include "edge.hpp"
#include "heap.hpp"
#include "graph.hpp"
#include "union_find.hpp"
#define UNSEEN  2
#define FRINGE  1
#define INTREE  0
#define ON_PATH  0
#define OFF_PATH  1

template<typename key_type, int graph_size>
void mbp_kruskal(graph<key_type,graph_size> &g0, int s, int t, vector< edge<key_type> > &path);

template<typename key_type, int graph_size>
void mbp_dijkstra(graph<key_type,graph_size> &g0, int s, int t, vector< edge<key_type> > &path);

template<typename key_type, int graph_size>
void mbp_dijkstra_heap(graph<key_type,graph_size> &g0, int s, int t,  vector< edge<key_type> > &path);

template<typename key_type, int graph_size>
int find_path(struct adj_node<key_type> edges[],int s,int t,bool v_flag[], vector< edge<key_type> > &path);

//Using Kruskal to find MBP
template<typename key_type, int graph_size>
void mbp_kruskal(graph<key_type,graph_size> &g0, int s, int t, vector< edge<key_type> > &path)
{
	int i,j,edge_num = 0;
	struct adj_node<key_type>  table[graph_size + 1];
	struct adj_node<key_type>*  tree_edges = table;
	edge<key_type> temp_e,tt;
	vector< edge<key_type> > edges;
	struct adj_node<key_type>* temp;
	int degree[graph_size + 1],set[graph_size + 1];
	//get all the edge information from the graph.
	g0.get_adj_table(table);
	edges.reserve((graph_size + 1) * (1+graph_size));
	heap<edge<key_type>,graph_size*graph_size,value_fun_edge<key_type>,name_fun_edge<key_type>,key_type> h0(false);
	for (i = 1 ; i <= graph_size; i ++ )
	{ 
		for(temp = table[i].adj_v;temp != NULL; temp = temp->adj_v)
		{
				temp_e = edge<key_type>(i,temp->name,temp->weight);
		// Here we use this code to guide the compiler generate conditonal move instruction, which can decrease the 
		// branch misprediction penalty. 
				edges[(temp->name > i) ? edge_num : 0] = temp_e;
				edge_num += (temp->name > i);
		}
	}
	for (i = 1 ; i <= edge_num; i ++ ) h0.insert(edges[i]);
	//make set for all the vertice
	for (i = 1 ; i <= graph_size ; i ++ ) make_set(set,degree,i);
	
	for (i = 1 ; i <= graph_size ; i ++ ) tree_edges[i].adj_v = NULL;
	long edge_count = 0;
	for(i = 0; i < edge_num ; i++ ) 
	{
		temp_e = h0.max();
		h0.del_max();
		if (find(set,temp_e.v1) != find(set,temp_e.v2) )
		{
			edge_count ++;
			set_union(set,degree,temp_e.v1,temp_e.v2);
			adj_node<key_type>* node1 = new adj_node<key_type>(temp_e.v1,temp_e.weight,tree_edges[temp_e.v2].adj_v);
			adj_node<key_type>* node2 = new adj_node<key_type>(temp_e.v2,temp_e.weight,tree_edges[temp_e.v1].adj_v);
			tree_edges[temp_e.v2].adj_v = node1;
			tree_edges[temp_e.v1].adj_v = node2;
		}
		if (edge_count == graph_size - 1 ) break;
	}
	bool v_flag[graph_size + 1];
	for (i = 1 ; i <= graph_size ; i ++ ) v_flag[i] = false;
	v_flag[s] = true;
	find_path<key_type,graph_size>(tree_edges,s,t,v_flag,path);
	return;
}
//Using Dijksta to find MBP without heap.
template<typename key_type, int graph_size>
void mbp_dijkstra(graph<key_type,graph_size> &g0, int s, int t,  vector< edge<key_type> > &path)
{
	struct adj_node<key_type>  table[graph_size + 1];
	key_type v_table[graph_size + 1];
	short v_flag[graph_size + 1];
	int v_parent[graph_size + 1];
	key_type v_parent_weight[graph_size + 1];
	vector<int> fringe;
	int i,max_v;
	struct adj_node<key_type>* temp;
	vector<int>::iterator ii,max,ed;
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
	while(fringe.size())
	{
		max = fringe.begin();
		ed = fringe.end();
		for (ii = fringe.begin(); ii != ed ; ii++) 
			if  ( v_table[*ii] > v_table[*max])  max = ii;
		max_v = *max;
		if (max_v == t) break;
		fringe.erase(max);
		v_flag[max_v] = INTREE;
		for(temp = table[max_v].adj_v;temp!=NULL;temp = temp->adj_v)
		{
			if (v_flag[temp->name] != INTREE) 
			{
				if (v_flag[temp->name] == UNSEEN) fringe.push_back(temp->name);
				v_flag[temp->name] = FRINGE;
				if ((temp->weight > v_table[temp->name]) && (v_table[max_v] >  v_table[temp->name]))
				{
					v_parent[temp->name] = max_v;
					v_parent_weight[temp->name] = temp->weight;
					v_table[temp->name] = std::min(v_table[max_v],temp->weight);
				}	
			}
		}
	}
	i = t;
	edge<key_type> edge_here;
	while( i != s) 
	{
		edge_here = edge<key_type>(v_parent[i],i,v_parent_weight[i]);
		path.push_back(edge_here);
		i = v_parent[i];
	}
	return;
}
//Using Dijkstra to find MBP with heap.
template<typename key_type, int graph_size>
void mbp_dijkstra_heap(graph<key_type,graph_size> &g0, int s, int t,  vector< edge<key_type> > &path)
{
	struct adj_node<key_type>  table[graph_size + 1];
	short v_flag[graph_size + 1];
	int v_parent[graph_size + 1];
	key_type v_parent_weight[graph_size + 1];
	heap<vertex<key_type>,graph_size,value_fun<key_type>,name_fun<key_type>,key_type> fringe(true);
	vertex<key_type> max,v1;
	struct adj_node<key_type>* temp;
	g0.get_adj_table(table);
	for (int i = 1; i <= graph_size ; i++) v_flag[i] = UNSEEN;
	v1 = g0.get_v(s);
	v1.set_key(MAX_WEIGHT + 1);
	v_flag[s] = FRINGE;
	fringe.insert(v1);
	while(fringe.size())
	{
		max = fringe.max();
		if (max.get_name() == t) break;
		for(temp = table[max.get_name()].adj_v;temp!=NULL;temp = temp->adj_v)
				{
			if (v_flag[temp->name] != INTREE)
			{
				if (v_flag[temp->name] == UNSEEN) fringe.insert(g0.get_v(temp->name));
				v_flag[temp->name] = FRINGE;
				if ((temp->weight > (fringe.index(fringe.get_index(temp->name))).get_key() )
				&&  (max.get_key() > (fringe.index(fringe.get_index(temp->name))).get_key() ) )
				{
					v_parent[temp->name] = max.get_name();
					v_parent_weight[temp->name] = temp->weight;
					//Relax
					v1 = fringe.index(fringe.get_index(temp->name));
					v1.set_key(std::min(max.get_key(),temp->weight));
					fringe.modify_at(fringe.get_index(temp->name),v1);
				}	
			}
		}
		v_flag[max.get_name()] = INTREE;
		fringe.del_max();
	}
	int i = t;
	edge<key_type> edge_here;
	while( i != s) 
	{
		edge_here = edge<key_type>(v_parent[i],i,v_parent_weight[i]);
		path.push_back(edge_here);
		i = v_parent[i];
	}
	return;
}
// Using DFS to find the path from s to t in the Maximum Spanning Tree.
template<typename key_type, int graph_size>
int find_path(struct adj_node<key_type> edges[],int s,int t,bool v_flag[], vector< edge<key_type> > &path){

	struct adj_node<key_type>* temp;
	temp = edges[s].adj_v;
	edge<key_type> edge_here;
	while(temp != NULL)
	{
		if ( v_flag[temp->name] == false) 
		{
			v_flag[temp->name] = true;
		
			if (temp->name == t)
			{
				edge_here = edge<key_type>(s,t,temp->weight);
				path.push_back(edge_here);
				return ON_PATH;
			}
			else if ( find_path<key_type,graph_size>(edges,temp->name,t,v_flag,path) == ON_PATH)
			{
				edge_here = edge<key_type>(s,temp->name,temp->weight);
				path.push_back(edge_here);
				return ON_PATH;
			}
		}
		temp = temp-> adj_v;
	}
	return OFF_PATH;
}
#endif
