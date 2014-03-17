#ifndef __GRAPH
#define __GRAPH
#include "vertex.hpp"
template<typename key_type>
struct adj_node
{
	int name;
	key_type weight;
	adj_node* adj_v;
};

//declaration
template<typename key_type,int GRAPH_SIZE>
class graph{

private:
	int v_count; 
	int e_count;
	struct adj_node<key_type> adj_table[GRAPH_SIZE + 1];
	struct vertex<key_type> v_table[GRAPH_SIZE + 1];
public:
	graph();
	int add_vertex(int index, key_type key);
//	int del_vertex(vertex<key_type> v1);
	int add_edge(int v1,int v2,key_type weight);
	bool is_edge(int v1,int v2);
	key_type edge_weight(int v1,int v2);
//	int del_edge(int v1,int v2);
	int get_v_count(); 
	int get_e_count();
	vertex<key_type> get_v(int name);
	void get_adj_table(struct adj_node<key_type> table[]);
//	int destroy_graph();
};

//defination
template<typename key_type,int GRAPH_SIZE>
graph<key_type,GRAPH_SIZE>::graph()
{
	int v_count = 0;
	int e_count = 0;
}

template<typename key_type,int GRAPH_SIZE>
int graph<key_type,GRAPH_SIZE>::get_v_count()
{
	return v_count;
}

template<typename key_type,int GRAPH_SIZE>
int graph<key_type,GRAPH_SIZE>::get_e_count()
{
	return e_count;
}

template<typename key_type,int GRAPH_SIZE>
int graph<key_type,GRAPH_SIZE>::add_vertex(int v1, key_type key)
{
	v_table[v1] = vertex<key_type>(v1,key);
	adj_table[v1].name = v1;
	adj_table[v1].adj_v = NULL;
	v_count ++;
	return 0;
}

template<typename key_type,int GRAPH_SIZE>
int graph<key_type,GRAPH_SIZE>::add_edge(int v1,int v2,key_type wt)
{
	adj_node<key_type>* node1 = new adj_node<key_type>();
	node1->name = v1;
	node1->weight = wt;
	
	adj_node<key_type>* node2 = new adj_node<key_type>();
	node2->name = v2;
	node2->weight = wt;
	
	struct adj_node<key_type>* temp;
	
	temp = adj_table[v1].adj_v;
	adj_table[v1].adj_v = node2;
	node2->adj_v = temp;

	temp = adj_table[v2].adj_v;
	adj_table[v2].adj_v = node1;
	node1->adj_v = temp;
	
	e_count++;
	return 0;
}

template<typename key_type,int GRAPH_SIZE>
bool graph<key_type,GRAPH_SIZE>::is_edge(int v1,int v2)
{
	struct adj_node<key_type>* temp;
	temp = &adj_table[v1];
//	if (v1 > GRAPH_SIZE || v2 > GRAPH_SIZE ) return false; 
	while(temp != NULL)
	{
		if (temp->name == v2) return true;
		temp = temp->adj_v;
	}
	return false;
}

template<typename key_type,int GRAPH_SIZE>
key_type graph<key_type,GRAPH_SIZE>::edge_weight(int v1,int v2)
{
	struct adj_node<key_type>* temp;
	temp = &adj_table[v1];
	while(temp != NULL)
	{
		if (temp->name == v2) return temp->weight;
		temp = temp->adj_v;
	}
	return 0;
}

template<typename key_type,int GRAPH_SIZE>
vertex<key_type> graph<key_type,GRAPH_SIZE>::get_v(int v1)
{
	return v_table[v1];
}

template<typename key_type,int GRAPH_SIZE>
void graph<key_type,GRAPH_SIZE>::get_adj_table(struct adj_node<key_type> table[])
{
	int i;
	for (i = 1 ; i <= GRAPH_SIZE; i ++)
		table[i] = adj_table[i];
	return;
}

#endif
