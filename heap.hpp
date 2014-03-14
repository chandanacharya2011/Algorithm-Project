#include<vector>
#include<algorithm>
//declartion of heap class.
using namespace std;
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
class heap{

private:
	vector<element> heap_array;
	vector<long> name_to_index;
	bool map_enable;
	void heaplize(long start_index);
	long heap_size;
	key_type key(element e1);
	long name(element e1);
public:
	heap(bool enable);
	void  insert(element e1);
	long size();
        element max();
	void del_max();
	void modify_at(long index, element new_ele);
	long get_index(long ele_name);
	element index(long index);//need to remove
};


// defination of heap class.
//Construction Fun
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
heap<element,MAX_SIZE,key_fun,name_fun,key_type>::heap(bool enable)
{
	heap_size = 0;
	heap_array.reserve(MAX_SIZE + 1);
	if(enable)
	{
		map_enable = true;
		name_to_index.reserve(MAX_SIZE + 1);
	}	
	else map_enable = false;
}


template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
key_type heap<element,MAX_SIZE,key_fun,name_fun,key_type>::key(element e1)
{
	key_fun fun;
	return  fun(e1);
}


template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
long heap<element,MAX_SIZE,key_fun,name_fun,key_type>::name(element e1)
{
	name_fun fun;
	return  fun(e1);
}


//push down the node to maintain a heap.
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
void heap<element,MAX_SIZE,key_fun,name_fun,key_type>::heaplize(long start_index)
{
	long max = start_index;
	
	if (2 * start_index <= heap_size &&  key(heap_array[start_index]) < key(heap_array[2 * start_index]))
		max = 2 * start_index;
	if (2 * start_index + 1 <= heap_size &&  key(heap_array[max]) < key(heap_array[2 * start_index + 1]))
		max = 2 * start_index + 1;
	if (start_index != max)	{
		if(map_enable)
			swap(name_to_index[name(heap_array[max])],name_to_index[name(heap_array[start_index])]);
		swap(heap_array[max],heap_array[start_index]);
		heaplize(max);
	}
	else return;
	return;
}

// insert a node into the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
void  heap<element,MAX_SIZE,key_fun,name_fun,key_type>::insert(element e1)
{
	heap_size++;
	heap_array[heap_size] = e1;
	if(map_enable) name_to_index[name(e1)] = heap_size;
	long i = heap_size;

        while( i > 1 &&  key(heap_array[i]) > key(heap_array[i/2]) ) 
		{
		if(map_enable) 
			swap(name_to_index[name(heap_array[i])],name_to_index[name(heap_array[i/2])]);
		swap(heap_array[i],heap_array[i/2]);
		i = i / 2;
		}
        return;
}

// return the size of the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
long heap<element,MAX_SIZE,key_fun,name_fun,key_type>::size()
{
	return heap_size;
}
// return the minimum element of the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
element heap<element,MAX_SIZE,key_fun,name_fun,key_type>::max()
{
	return heap_array[1];
}

//delete the minimum(also the first) element if the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
void heap<element,MAX_SIZE,key_fun,name_fun,key_type>::del_max()
{
	if (heap_size == 0) return;
	if (map_enable) name_to_index[name(heap_array[heap_size])] = 1;
	heap_array[1] = heap_array[heap_size];
	heap_size--;
	if (heap_size == 0) return;
	else heaplize(1);
	return;
}


template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
void heap<element,MAX_SIZE,key_fun,name_fun,key_type>::modify_at(long index,element new_ele)
{

        long i = index;
	heap_array[i] = new_ele;
	while( i > 1 &&  key(heap_array[i]) > key(heap_array[i/2]) ) 
		{
		if(map_enable) 
			swap(name_to_index[name(heap_array[i])],name_to_index[name(heap_array[i/2])]);
		swap(heap_array[i],heap_array[i/2]);
		i = i / 2;
		}

	heaplize(i);
	return;
}

//get index

template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
long heap<element,MAX_SIZE,key_fun,name_fun,key_type>::get_index(long ele_name)
{
	return name_to_index[ele_name];
}

//for test only, need to remove
template <typename element, long MAX_SIZE, typename key_fun, typename name_fun,typename key_type>
element heap<element,MAX_SIZE,key_fun,name_fun,key_type>::index(long index)
{
	return heap_array[index];
}
