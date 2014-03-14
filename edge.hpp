template<typename key_type>
struct edge
{
	int v1;
	int v2;
	key_type weight;
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
