#ifndef __vertex
#define __vertex
template<typename key_type>
class vertex{
private:
	key_type vertex_key;
	long vertex_name;
public:	
	vertex(long name, key_type key);
	vertex();
	key_type get_key();
	void set_key(key_type key);
	long get_name();
};

template<typename key_type>
key_type vertex<key_type>::get_key()
{
	return vertex_key;
}

template<typename key_type>
void vertex<key_type>::set_key(key_type key)
{
	vertex_key = key;
	return;
}


template<typename key_type>
long vertex<key_type>::get_name()
{
	return vertex_name;
}

template<typename key_type>
vertex<key_type>::vertex(long name, key_type key)
{
	vertex_key = key;
	vertex_name = name;
}

template<typename key_type>
vertex<key_type>::vertex()
{
	vertex_key = 0;
	vertex_name = 0;
}



template<typename key_type>
class value_fun
{
public:
	key_type operator()(vertex<key_type> e1);
};

template<typename key_type>
key_type value_fun<key_type>::operator()(vertex<key_type> e1)
{
	return e1.get_key();
}


template<typename key_type>
class name_fun
{
public:
	long operator()(vertex<key_type> e1);
};

template<typename key_type>
long name_fun<key_type>::operator()(vertex<key_type> e1)
{
	return e1.get_name();
}

#endif
