#include "edge.hpp"
template<typename key_type, int graph_size>
key_type mbp_kruskal(graph<key_type,graph_size> g0, int s, int t, int path[]);

template<typename key_type, int graph_size>
key_type mbp_dijkstra(graph<key_type,graph_size> g0, int s, int t, int path[]);

template<typename key_type, int graph_size>
key_type mbp_dijkstra_heap(graph<key_type,graph_size> g0, int s, int t, int path[]);

template<typename key_type,int graph_size>
void sort_edge (struct edge<key_type> edges[], int edge_num);

template<typename key_type, int graph_size>
key_type mbp_kruskal(graph<key_type,graph_size> g0, int s, int t, int path[])
{
	int i,j,edge_num = 0;
	bool edge_flag[graph_size + 1][graph_size + 1];
	struct adj_node<key_type>  table[graph_size + 1];
	struct edge<key_type> edges[graph_size * graph_size];
	struct adj_node<key_type>* temp;

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
	
	for (i = 0 ; i < edge_num ; i ++ )
		std::cout << edges[i].v1 <<"," <<edges[i].v2<<":" << edges[i].weight <<std::endl;
	return 0;
}


template<typename key_type, int graph_size>
key_type mbp_dijkstra(graph<key_type,graph_size> g0, int s, int t, int path[])
{
	return 0;
}



template<typename key_type, int graph_size>
key_type mbp_dijkstra_heap(graph<key_type,graph_size> g0, int s, int t, int path[])
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
	for(i = 0; i < edge_num ; i++ ) 
	{
		edges[i] = h0.min();
		h0.del_min();
	}

/*	int i,j;
	struct edge<key_type> temp;
	for(i = 0; i < edge_num ; i++ )
		for(j = 0; j < i; j++ )
			if (edges[j].weight < edges[i].weight)
			{
				temp = edges[j];
				edges[j] = edges[i];
				edges[i] = temp;
			}
*/
	return;
}


