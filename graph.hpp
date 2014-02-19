
template<typename key_type>
struct adj_node
{
	
	vertex<key_type> v;
	adj_node* adj_v;

};

//declaration
template<typename key_type,int GRAPH_SIZE>
class graph{

private:
	int v_count; 
	int e_count;
	struct adj_node<key_type> v_table[GRAPH_SIZE];
	graph();
public:
	int add_vertex(key_type key);
//	int del_vertex(vertex<key_type> v1);
	int add_edge(vertex<key_type> v1,vertex<key_type> v2,key_type wt);
//	int del_edge(vertex<key_type> v1,vertex<key_type> v2);
	int get_v_count(); 
	int get_e_count();
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
int graph<key_type,GRAPH_SIZE>::add_vertex(key_type key)
{
	v_table[v_count].v = key;
	v_table[v_count].adj_v = NULL;
	v_count ++;
}

template<typename key_type,int GRAPH_SIZE>
int graph<key_type,GRAPH_SIZE>::add_edge(vertex<key_type> v1,vertex<key_type> v2,key_type wt)
{
	adj_node node1 = new adj_node();
	adj_node node2 = new adj_node();
	v1.
}


