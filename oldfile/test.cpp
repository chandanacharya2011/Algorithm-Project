#include <iostream>
#include "heap.hpp"
#include "vertex.hpp"
#include "graph.hpp"
#define KEY_TYPE double
using namespace std;


int main(){
	
	heap<vertex<KEY_TYPE>,5000,value_fun<KEY_TYPE>,name_fun<KEY_TYPE>,KEY_TYPE> h0(true);
	
	int i,j;

	graph<KEY_TYPE,1000> g1;

	vertex<KEY_TYPE> n1(1,11.2),n2(2,22),n3(3,16),n4(4,6),n5(5,126),n6(6,16),n7(7,18),n8(8,28);

	g1.add_vertex(1,11.2);
	g1.add_vertex(2,22);
	g1.add_vertex(3,16);
	g1.add_vertex(4,6);
	g1.add_vertex(5,126);
	g1.add_vertex(6,16);
	g1.add_vertex(7,18);
	g1.add_vertex(8,28);

	g1.add_edge(2,3,2.2);
	g1.add_edge(1,3,3);
	g1.add_edge(4,7,4);

	cout <<"vcount: " << g1.get_v_count() << endl;
	cout <<"ecount: " << g1.get_e_count() << endl;
	
	cout <<"2,3: " << g1.is_edge(2,3) << " wt: "<<g1.edge_weight(2,3)<<endl;
	cout <<"3,8: " << g1.is_edge(3,8) << " wt: "<< g1.edge_weight(3,8)<<endl;
	cout <<"5,8: " << g1.is_edge(5,8) << " wt: "<< g1.edge_weight(5,8)<<endl;
	cout <<"1,3: " << g1.is_edge(3,1) << " wt: "<< g1.edge_weight(3,1)<<endl;
	cout << endl;

	h0.insert(g1.get_v(1));
	h0.insert(g1.get_v(2));
	h0.insert(g1.get_v(3));
	h0.insert(g1.get_v(4));
	h0.insert(g1.get_v(5));
	h0.insert(g1.get_v(6));
	h0.insert(g1.get_v(7));
	h0.insert(g1.get_v(8));
	
	cout <<"max:"<< h0.max().get_key() << endl;
	cout <<"size:"<< h0.size() << endl;

	
	for (i=1;i<=h0.size();i++) cout << h0.index(i).get_name()<< " , "<<h0.index(i).get_key() <<endl;
	h0.modify_at(2,g1.get_v(3));
	cout << endl;
	for (i=1;i<=h0.size();i++) cout << h0.index(i).get_name()<< " , "<<h0.index(i).get_key() <<endl;
	for (i=1;i<=h0.size();i++) cout << "i: " << i << ", "<< h0.get_index(i) <<endl;

/*	for (j=1;h0.size();j++)
	{	
		h0.del_max();
		cout <<"after remove:"<< endl;
		for (i=1;i<=h0.size();i++) cout << h0.index(i).get_name()<< " , "<<h0.index(i).get_key() <<endl;
		for (i=1;i<=8;i++) cout << "i: " << i << ", "<< h0.get_index(i) <<endl;
	}
*/	
	return 0;
}
