#include <iostream>
#include "heap.hpp"
#include "vertex.hpp"
//#include "graph.hpp"
#define KEY_TYPE double
using namespace std;


int main(){
	
	heap<vertex<KEY_TYPE>,5000,value_fun<KEY_TYPE>,KEY_TYPE> h0;
	
	int i,j;
	vertex<KEY_TYPE> n1(1,11.2),n2(2,22),n3(3,16),n4(4,6),n5(5,126),n6(6,16),n7(7,18),n8(8,28);

	h0.insert(n1);
	h0.insert(n2);
	h0.insert(n3);
	h0.insert(n4);
	h0.insert(n5);
	h0.insert(n6);
	h0.insert(n7);
	h0.insert(n8);
	
	cout <<"min:"<< h0.min().get_key() << endl;
	cout <<"size:"<< h0.size() << endl;

	
	for (i=1;i<=h0.size();i++) cout << h0.index(i).get_name()<< " , "<<h0.index(i).get_key() <<endl;
	for (j=1;h0.size();j++)
	{	
		h0.del_min();
		cout <<"after remove:"<< endl;
		for (i=1;i<=h0.size();i++) cout << h0.index(i).get_name()<< " , "<<h0.index(i).get_key() <<endl;
	}
	return 0;
}
