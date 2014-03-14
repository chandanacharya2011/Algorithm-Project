#include<vector>
#include<algorithm>
//declartion of heap class.
using namespace std;
template <typename element, long MAX_SIZE, typename key_fun,typename key_type>
class heap{

private:
	vector<element> heap_array;
	void heaplize(long start_index);
	long heap_size;
	key_type key(element e1);
public:
	heap();
	void insert(element e1);
	long size();
        element min();
	void del_min();
	element index(long index);//need to remove
};


// defination of heap class.
template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
heap<element,MAX_SIZE,key_fun,key_type>::heap()
{
	heap_size = 0;
	heap_array.reserve(MAX_SIZE + 1);
}

template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
key_type heap<element,MAX_SIZE,key_fun,key_type>::key(element e1)
{
	key_fun fun;
	return  fun(e1);
}


//push down the node to maintain a heap.
template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
void heap<element,MAX_SIZE,key_fun,key_type>::heaplize(long start_index)
{
	long min = start_index;
	
	if (2 * start_index <= heap_size &&  key(heap_array[start_index]) > key(heap_array[2 * start_index]))
		min = 2 * start_index;
	if (2 * start_index + 1 <= heap_size &&  key(heap_array[min]) > key(heap_array[2 * start_index + 1]))
		min = 2 * start_index + 1;
	if (start_index != min)	{
		swap(heap_array[min],heap_array[start_index]);
		heaplize(min);
	}
	else return;
	return;
}

// insert a node into the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
void heap<element,MAX_SIZE,key_fun,key_type>::insert(element e1)
{
	heap_size++;
	heap_array[heap_size] = e1;
	
	long i = heap_size;

        while( i > 1 &&  key(heap_array[i]) < key(heap_array[i/2]) ) 
		{
		swap(heap_array[i],heap_array[i/2]);
		i = i / 2;
		}
        return;
}
// return the size of the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
long heap<element,MAX_SIZE,key_fun,key_type>::size()
{
	return heap_size;
}
// return the minimum element of the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
element heap<element,MAX_SIZE,key_fun,key_type>::min()
{
	return heap_array[1];
}

//delete the minimum(also the first) element if the heap.
template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
void heap<element,MAX_SIZE,key_fun,key_type>::del_min()
{
	if (heap_size == 0) return;
	heap_array[1] = heap_array[heap_size];
	heap_size--;
	if (heap_size == 0) return;
	else heaplize(1);
	return;
}


//for test only, need to remove
template <typename element, long MAX_SIZE, typename key_fun, typename key_type>
element heap<element,MAX_SIZE,key_fun,key_type>::index(long index)
{
	return heap_array[index];
}
