//declartion of heap class.
template <typename element, int MAX_SIZE, typename key_fun,typename key_type>
class heap{

private:
	element heap_array[MAX_SIZE + 1];
	int heaplize(int start_index);
	int swap(element& e1, element& e2);
	int heap_size;
	key_type key(element e1);
public:
	heap();
	int insert(element e1);
	int size();
        element min();
	int del_min();
	element index(int index);//need to remove
};


// defination of heap class.
template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
heap<element,MAX_SIZE,key_fun,key_type>::heap()
{
	heap_size = 0;
}

template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
key_type heap<element,MAX_SIZE,key_fun,key_type>::key(element e1)
{
	key_fun fun;
	return  fun(e1);
}



template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
int heap<element,MAX_SIZE,key_fun,key_type>::swap(element& e1,element& e2)
{
	element temp;
	temp = e1;
	e1 = e2;
	e2 = temp;
	return 0;
}
//push down the node to maintain a heap.
template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
int heap<element,MAX_SIZE,key_fun,key_type>::heaplize(int start_index)
{
	int min = start_index;
	
	if (2 * start_index <= heap_size &&  key(heap_array[start_index]) > key(heap_array[2 * start_index]))
		min = 2 * start_index;
	if (2 * start_index + 1 <= heap_size &&  key(heap_array[min]) > key(heap_array[2 * start_index + 1]))
		min = 2 * start_index + 1;
	if (start_index != min)	{
		swap(heap_array[min],heap_array[start_index]);
		heaplize(min);
	}
	else return 0;
	return 0;
}

// insert a node into the heap.
template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
int heap<element,MAX_SIZE,key_fun,key_type>::insert(element e1)
{
	heap_size++;
	heap_array[heap_size] = e1;
	
	int i = heap_size;

        while( i > 1 &&  key(heap_array[i]) < key(heap_array[i/2]) ) 
		{
		swap(heap_array[i],heap_array[i/2]);
		i = i / 2;
		}
        return 0;
}
// return the size of the heap.
template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
int heap<element,MAX_SIZE,key_fun,key_type>::size()
{
	return heap_size;
}
// return the minimum element of the heap.
template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
element heap<element,MAX_SIZE,key_fun,key_type>::min()
{
	return heap_array[1];
}

//delete the minimum(also the first) element if the heap.
template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
int heap<element,MAX_SIZE,key_fun,key_type>::del_min()
{
	if (heap_size == 0) return 1;
	heap_array[1] = heap_array[heap_size];
	heap_size--;
	if (heap_size == 0) return 0;
	else heaplize(1);
	return 0;
}


//for test only, need to remove
template <typename element, int MAX_SIZE, typename key_fun, typename key_type>
element heap<element,MAX_SIZE,key_fun,key_type>::index(int index)
{
	return heap_array[index];
}
