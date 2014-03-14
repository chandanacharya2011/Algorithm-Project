#include <vector>
#include "edge.hpp"
#include "union_find.hpp"
const int UNSEEN = 0;
const int FRINGE = 1;
const int INTREE = 2;
using namespace std;
template<typename key_type, int graph_size>
key_type mbp_kruskal(graph<key_type,graph_size> g0, int s, int t, struct edge<key_type> path[]);

template<typename key_type, int graph_size>
key_type mbp_dijkstra(graph<key_type,graph_size> g0, int s, int t, struct edge<key_type> path[]);

template<typename key_type, int graph_size>
key_type mbp_dijkstra_heap(graph<key_type,graph_size> g0, int s, int t, struct edge<key_type> path[]);

template<typename key_type,int graph_size>
void sort_edge (struct edge<key_type> edges[], int edge_num);


template<typename key_type, int graph_size>
int find_path(bool edge_flag[][graph_size + 1],struct adj_node<key_type> table[],int s,int t,edge<key_type> path[]);

//Implement
template<typename key_type, int graph_size>
key_type mbp_kruskal(graph<key_type,graph_size> g0, int s, int t, struct edge<key_type> path[])
{
	int i,j,edge_num = 0;
	bool edge_flag[graph_size + 1][graph_size + 1];
	struct adj_node<key_type>  table[graph_size + 1];
	struct edge<key_type>* edges = new edge<key_type>[graph_size * graph_size];
	struct adj_node<key_type>* temp;
	
	int degree[graph_size + 1];
	int set[graph_size + 1];

	g0.get_adj_table(table);
	for (i = 1 ; i <= graph_size ; i ++ )
		for (j = 1 ; j <= graph_size ; j ++ )
				edge_flag[i][j] = false;
	for (i = 1 ; i <= graph_size ; i ++ )
	{
		temp = table[i].adj_v;
		while (temp != NULL) 
		{
			if ((edge_flag[i][temp->name] == false) && (edge_flag[temp->name][i] == false))
			{
				edges[edge_num].v1 = i;
				edges[edge_num].v2 = temp->name;
				edges[edge_num].weight = temp->weight;
			
				edge_num ++;
				edge_flag[i][temp->name] = true;
			}
			temp = temp->adj_v;
		}
	
	}

	sort_edge<key_type,graph_size>(edges,edge_num);
	
	for (i = 1 ; i <= graph_size ; i ++ )
		for (j = 1 ; j <= graph_size ; j ++ )
				edge_flag[i][j] = false;

	for (i = 1 ; i <= graph_size ; i ++ )
		make_set(set,degree,i);
	for (i = 0 ; i < edge_num; i ++ )
		if (find(set,edges[i].v1) != find(set,edges[i].v2) )
		{
			set_union(set,degree,edges[i].v1,edges[i].v2);
			edge_flag[edges[i].v1][edges[i].v2] = true;
		}
	find_path<key_type,graph_size>(edge_flag,table,s,t,path);

	return 0;
}

template<typename key_type, int graph_size>
key_type mbp_dijkstra(graph<key_type,graph_size> g0, int s, int t, struct edge<key_type> path[])
{
	struct adj_node<key_type>  table[graph_size + 1];
	key_type v_table[graph_size + 1];
	int v_flag[graph_size + 1];
	int v_parent[graph_size + 1];
	int v_parent_weight[graph_size + 1];
	vector<int> fringe;
	int i,j;
	struct adj_node<key_type>* temp;
	vector<int>::iterator ii,max;
	g0.get_adj_table(table);
	for (i = 1; i <= graph_size ; i++) 
	{
		v_table[i] = 0;
		v_flag[i] = UNSEEN;
	}
	v_table[s] = 5001;
	v_flag[s] = FRINGE;
	fringe.reserve(graph_size + 1);
	fringe.push_back(s);

	while(!fringe.empty())
	{
		max = fringe.begin();
		for (ii = fringe.begin(); ii != fringe.end() ; ii++) 
			if (v_table[*ii] > v_table[*max]) max = ii;
		temp = table[*max].adj_v;
		while(temp != NULL)
		{
			if (v_flag[temp->name] == UNSEEN) 
			{
				v_flag[temp->name] = FRINGE;
				fringe.push_back(temp->name);
				if (v_table[*max] > temp->weight)
						v_table[temp->name] = temp->weight;
					else
						v_table[temp->name] = v_table[*max];

				v_parent[temp->name] = *max;
				v_parent_weight[temp->name] = temp->weight;
			}
			else if(v_flag[temp->name] == FRINGE)
			{
				if ((temp->weight > v_table[temp->name]) && (v_table[*max] >  v_table[temp->name]))
				{
					v_parent[temp->name] = *max;
					v_parent_weight[temp->name] = temp->weight;
					if (v_table[*max] > temp->weight)
						v_table[temp->name] = temp->weight;
					else
						v_table[temp->name] = v_table[*max];
				}	
			}
			temp = temp->adj_v;
		}
			
		v_flag[*max] = INTREE;
		fringe.erase(max);
	}
	i = t;
	while( i != s) 
	{
		cout << v_parent[i] <<","<< i <<":"<< v_parent_weight[i] <<endl;
		i = v_parent[i];
	}
	return 0;
}

template<typename key_type, int graph_size>
key_type mbp_dijkstra_heap(graph<key_type,graph_size> g0, int s, int t, struct edge<key_type> path[])
{
	
	return 0;
}

//heap sort
template<typename key_type, int graph_size>
void sort_edge (struct edge<key_type> edges[], int edge_num)
{

	heap<edge<key_type>,graph_size*graph_size,value_fun_edge<key_type>,key_type> h0;
	int i;
	for(i = 0; i < edge_num ; i++ ) h0.insert(edges[i]);
	for(i = edge_num - 1; i >= 0 ; i-- ) 
	{
		edges[i] = h0.min();
		h0.del_min();
	}
	return;
}


template<typename key_type, int graph_size>
int find_path(bool edge_flag[][graph_size + 1],struct adj_node<key_type> table[],int s,int t,edge<key_type> path[])
{
	
	struct adj_node<key_type>* temp;
	temp = table[s].adj_v;
	
	while(temp != NULL) 
	{
		if(edge_flag[s][temp->name] || edge_flag[temp->name][s] )
		{
			edge_flag[s][temp->name] = false;
			edge_flag[temp->name][s] = false;
		
			if (temp->name == t)
			{
				cout << "path edge:" << s << ","<< t <<":" << temp->weight << endl;
				return 0;
			}
			
			else if (find_path<key_type,graph_size>(edge_flag,table,temp->name,t,path) == 0)
			{
				cout << "path edge:" << s << ","<< temp->name <<":" << temp->weight << endl;
				return 0;
			}
		}
		temp = temp-> adj_v;
	}
	return 1;
}
