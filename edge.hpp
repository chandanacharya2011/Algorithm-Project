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
	edge(int v10,int v20,key_type weight0)
	{
		v1=v10;
		v2=v20;
		weight = weight0;
	}
	edge()
	{
		return;
	}
};

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
