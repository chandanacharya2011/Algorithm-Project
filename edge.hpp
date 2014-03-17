#ifndef __edge
#define __edge
template<typename key_type>
class edge
{
public:
	int v1;
	int v2;
	key_type weight;
//	edge(int v1,int v2,key_type weight);
};

/*
template<typename key_type>
edge<key_type>::edge(int v1, int v2, key_type weight)
{
	v1 = v1;
	v2 = v2;
	weight = weight;
}
*/

template<typename key_type>
class value_fun_edge
{
public:
	key_type operator()(edge<key_type> e1);
};

template<typename key_type>
key_type value_fun_edge<key_type>::operator()(edge<key_type> e1)
{
	return e1.weight;
}

//Since there no need for naming an edge , this is a dummy functor
template<typename key_type>
class name_fun_edge
{
public:
	long operator()(edge<key_type> e1);
};

template<typename key_type>
long name_fun_edge<key_type>::operator()(edge<key_type> e1)
{
	return 0;
}
#endif
