#include"two-three-tree.h"

template <class Key, class Val> 
static Val *search_help(Node<Key, Val> *node, Key key)  
{ 
	if(!node) return NULL;
	else{
		if (node->rkey==NULL){
			if(key==*(node->lkey))
				return node->lval;
			else if(key<*(node->lkey))
				return search_help(node->left, key);
			else
				return search_help(node->right,key);
		}
		else{
			if(key==*(node->lkey))
				return node->lval;
			if(key==*(node->rkey))
				return node->rval;
			if(key<*(node->lkey))
				return search_help(node->left,key);
			if(key>*(node->rkey))
				return search_help(node->right,key);
			return search_help(node->center,key);
		}
	}
} 
template <class Key, class Val> 
static Node<Key,Val> *search_helpNode(Node<Key, Val> *node, Key *key)  
{ 
	if(node->lkey!=NULL)
	if(*node->lkey==*key)
		return NULL;
	if(node->rkey!=NULL)
		if(*node->rkey==*key)
			return NULL;
	if(node->left == NULL){
		return node;
	}else{
		if(node->rkey==NULL){
			if(*key<*(node->lkey))
				return search_helpNode(node->left,key);
			else if(*key>*(node->lkey))
				return search_helpNode(node->right,key);
			return NULL;
		}
		else{
			if(*key<*(node->lkey))
				return search_helpNode(node->left,key);
			else if(*key>*(node->rkey))
				return search_helpNode(node->right,key);
			else if(*key>*(node->lkey)&&*key<*(node->rkey))
				return search_helpNode(node->center,key);
			return NULL;
		}
	}
} 

template <class Key, class Val>

Val* Tree<Key,Val>::search(Key key) const{
	return search_help(root,key);
}
template <class Key, class Val>
static Node<Key,Val> *find_Parent(Node<Key,Val> *node,Node<Key,Val> *root){
	Node<Key,Val> *cur = root;
	Node<Key,Val> *parent = NULL;
	if(node == root)
		return NULL;
	else{
	while(*(cur->lkey)!=*(node->lkey)){
		parent = cur;
		if(node->rkey == NULL){
			if(cur->rkey == NULL){
				if(*(node->lkey)<*(cur->lkey)){
					if(cur->left==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->left;
				}
				else{
					if(cur->right==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->right;
				}
			}else{
				if(*(node->lkey)<*(cur->lkey)){
					if(cur->left==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->left;
				}
				else if(*(node->lkey)>*(cur->lkey)&&*(node->lkey)<*(cur->rkey)){
					if(cur->center==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->center;
				}
				else{
					if(cur->right==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->right;
				}
			}
		}else{
			if(cur->rkey ==NULL){
				if(*(node->rkey)<*(cur->lkey)){
					if(cur->left==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->left;
				}
				else{
					if(cur->right==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->right;
				}
			}else{
				if(*(node->rkey)<*(cur->lkey)){
					if(cur->left==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->left;
				}
				else if(*(node->lkey)>*(cur->lkey)&&*(node->rkey)<*(cur->rkey)){
					if(cur->center==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->center;
				}
				else{
					if(cur->right==NULL) {
						parent = find_Parent(cur,root);
						break;
					}
					cur = cur->right;
				}
			}
		}
	}
	}
	return parent;
}

template <class Key, class Val>
int find_midkey(Node<Key,Val> *node, Key *key){
	if(*key<*(node->lkey))
		return -1;
	else if(*key>*(node->rkey))
		return 1;
	else
		return 0;
}
template <class Key, class Val>
static void split_helper(Node<Key,Val> *parent,Node<Key,Val> *lnode,Key *key, Val *val,Node<Key,Val> *rnode,Node<Key,Val> *root){
	if(parent==NULL){
		if(lnode==root){
			Node<Key,Val> *nd = new Node<Key,Val>;
			nd->rkey = NULL;
			nd->lkey = NULL;
			nd->left = NULL;
			nd->center = NULL;
			nd->right = NULL;
			nd->rkey = lnode->rkey;
			nd->lkey = lnode->lkey;
			nd->lval = lnode->lval;
			nd->left = lnode->left;
			nd->center = lnode->center;
			nd->right = lnode->right;
			root->left = nd;
			root->right = rnode;
			root->rval = NULL;
			root->rkey = NULL;
			root->lkey = key;
			root->lval = val;
			root->center = NULL;
		}else if(rnode == root){
			Node<Key,Val> *nd = new Node<Key,Val>;
			nd->rkey = NULL;
			nd->lkey = NULL;
			nd->left = NULL;
			nd->center = NULL;
			nd->right = NULL;
			nd->rkey = rnode->rkey;
			nd->lkey = rnode->lkey;
			nd->lval = rnode->lval;
			nd->left = rnode->left;
			nd->center = rnode->center;
			nd->right = rnode->right;
			root->left = lnode;
			root->right = nd;
			root->rval = NULL;
			root->center = NULL;
			root->rkey = NULL;
			root->lkey = key;
			root->lval = val;
		}
		
	}else{
		if(parent->rkey == NULL){
			if(*(key)<*(parent->lkey)){
				parent->rkey = parent->lkey;
				parent->rval = parent->lval;
				parent->center = rnode;
				parent->left = lnode;
				parent->lkey = key;
				parent->lval = val;
			}else{
				parent->center = lnode;
				parent->right = rnode;
				parent->rkey = key;
				parent->rval = val;
			}
		}else{
			Node<Key,Val> *nd = new Node<Key,Val>;
			nd->rkey = NULL;
			nd->lkey = NULL;
			nd->left = NULL;
			nd->center = NULL;
			nd->right = NULL;
			//Key *k;
			Node<Key,Val> *nparent = find_Parent(parent,root);
			//int i = find_midkey(parent,key);
			Key* tempK;
			Val* tempV;
			if(*(key)<*(parent->lkey)){
				tempK = parent->lkey;
				tempV = parent->lval;
				nd->lkey = key;
				nd->lval = val;
				nd->left = lnode;
				nd->right = rnode;
				parent->lkey = parent->rkey;
				parent->lval = parent->rval;
				parent->left = parent->center;
				parent->rkey = NULL;
				parent->rval = NULL;
				split_helper(nparent,nd,tempK,tempV,parent,root);
			}else if(*(key)>*(parent->lkey)&&*(key)<*(parent->rkey)){
				tempK = key;
				tempV = val;
				nd->lkey = parent->lkey;
				nd->lval = parent->lval;
				nd->left = parent->left;
				nd->right = lnode;
				parent->lkey = parent->rkey;
				parent->lval = parent->rval;
				parent->left = rnode;
				parent->rkey = NULL;
				parent->rval = NULL;
				split_helper(nparent,nd,tempK,tempV,parent,root);
			}else{
				tempK = parent->rkey;
				tempV = parent->rval;
				nd->lkey = key;
				nd->lval = val;
				nd->left = lnode;
				nd->right = rnode;
				parent->rkey = NULL;
				parent->rval = NULL;
				parent->right = parent->center;
				split_helper(nparent,parent,tempK,tempV,nd,root);
			}
		}
	}
}
template <class Key, class Val>
static void split(Node<Key,Val> *node, Key *key, Val *val,Node<Key,Val> *root){
	Node<Key,Val> *parent = find_Parent(node,root);
	Node<Key,Val> *nd = new Node<Key,Val>;
	nd->rkey = NULL;
	nd->lkey = NULL;
	nd->left = NULL;
	nd->center = NULL;
	nd->right = NULL;
	int i = find_midkey(node,key);
	if(i==-1){
		nd->lkey = key;
		nd->lval = val;
		Key* tempK = node->lkey;
		Val* tempV = node->lval;
		node->lkey = node->rkey;
		node->lval = node->rval;
		node->rkey = NULL;
		node->rval = NULL;
		split_helper(parent,nd,tempK,tempV,node,root);
	}else if(i==0){
		nd->lkey = node->lkey;
		nd->lval = node->lval;
		node->lkey = node->rkey;
		node->lval = node->rval;
		node->rkey = NULL;
		node->rval = NULL;
		split_helper(parent,nd,key,val,node,root);
	}else{
		nd->lkey = key;
		nd->lval = val;
		Key* tempK = node->rkey;
		Val* tempV = node->rval;
		node->rkey = NULL;
		node->rval = NULL;
		split_helper(parent,node,tempK,tempV,nd,root);
	}
}
template <class Key, class Val>
bool Tree<Key,Val>::insert(Key *key, Val *val){
	Node<Key,Val> *N = search_helpNode(root,key);
	if(root->lkey==NULL){
		root->lkey = key;
		root->lval = val;
		return true;
	}
	if(N==NULL)
		return false;
	else{
		if(N->rkey==NULL){
			if(*key<*(N->lkey)){
				N->rkey = N->lkey;
				N->rval = N->lval;
				N->lkey = key;
				N->lval = val;
			}else{
				N->rkey = key;
				N->rval = val;
			}
		}
		else
			split(N, key, val,root);
		return true;
	}
}
template <class Key, class Val>
static Node<Key,Val> *findNode(Node<Key,Val> *node,Key* key){
	if(node==NULL){
		return NULL;
	}else{
		if(node->rkey ==NULL){
			if(*(key)==*(node->lkey))
				return node;
			else if(*key<*(node->lkey))
				return findNode(node->left,key); 
			else
				return findNode(node->right,key);
		}else{
			if(*key==*(node->lkey)||*key==*(node->rkey))
				return node;
			else if(*key<*(node->lkey))
				return findNode(node->left,key);
			else if(*key>*(node->lkey)&&*key<*(node->rkey))
				return findNode(node->center,key);
			else 
				return findNode(node->right,key);
		}
	}
}
template <class Key, class Val>
static Val* removeKey(Node<Key,Val> *node,Key* key,bool *check){
	Val* result;
	if(*(key)==*(node->lkey)){
		if(node->rkey==NULL){
			*check = 1;
			result = node->lval;
		}else{
			result = node->lval;
			node->lkey = node->rkey;
			node->lval = node->rval;
			node->rkey = NULL;
			node->rval = NULL;
		}
	}else{
		result = node->rval;
		node->rkey = NULL;
		node->rval = NULL;
	}
	return result;
}
template <class Key, class Val>
static Node<Key,Val> *swap_helper(Node<Key,Val>*node){
	if(node->left == NULL){
		return node;
	}else{
		return swap_helper(node->left);
	}
}
template <class Key, class Val>
static Node<Key,Val> *swap_key(Node<Key,Val>*node,Key *key,Val *val){
	if(node->left==NULL)
		return node;
	Node<Key,Val> *nnode;
	if(node->rkey==NULL){
		nnode = swap_helper(node->right);
		node->lkey = nnode->lkey;
		node->lval = nnode->lval;
		nnode->lkey = key;
		nnode->lval = val;
	}
	else{
		if(*node->lkey==*key){
			nnode = swap_helper(node->center);
			node->lkey = nnode->lkey;
			node->lval = nnode->lval;
			nnode->lkey = key;
			nnode->lval = val;
		}
		else{
			nnode = swap_helper(node->right);
			node->rkey = nnode->lkey;
			node->rval = nnode->lval;
			nnode->lkey = key;
			nnode->lval = val;
		}
	}
		/*if(*node->lkey == *key)
			tempV = node->lval;
		else if(*node->rkey == *key)
			tempV = node->rval;*/
		/*if(node->rkey==NULL||node->rkey==key){
			if(node->rkey==NULL){
			node->lkey = node->right->lkey;
			node->lval = node->right->lval;
			node->right->lkey = tempK;
			node->right->lval = tempV;
			}else{
			node->rkey = node->right->lkey;
			node->rval = node->right->lval;
			node->right->lkey = tempK;
			node->right->lval = tempV;
			}
			return swap_key(node->right,key);
		}else{
			node->lkey = node->center->lkey;
			node->lval = node->center->lval;
			node->center->lkey = tempK;
			node->center->lval = tempV;
			return swap_key(node->center,key);
		}*/
	return nnode;
}
template <class Key, class Val>
static Node<Key,Val>* adjacent(Node<Key,Val>* node,Node<Key,Val> *root){
	//Key* k;
	Node<Key,Val> *parent = find_Parent(node,root);
	if(parent->left == node&&parent->rkey == NULL)
		return parent->right;
	else if(parent->left == node&& parent->rkey!=NULL)
		return parent->center;
	else if(parent->center == node)
		return parent->left;
	else if(parent->right == node&&parent->rkey==NULL)
		return parent->left;
	else if (parent->right==node&&parent->rkey!=NULL)
		return parent->center;
	else 
		return NULL;
}
template <class Key, class Val>
static void remove_helper(Node<Key,Val>*parent,Node<Key,Val> *node,Node<Key,Val> *root){
	//Node<Key,Val> *parent = find_Parent(node,root);
	if(parent==NULL){
		//if(root->left == node){
		Node<Key,Val> *temp = root->left;
		root->rkey = root->left->rkey;
		root->rval = root->left->rval;
		root->lkey = root->left->lkey;
		root->lval = root->left->lval;
		root->right = root->left->right;
		root->center = root->left->center;
		root->left = root->left->left;
		/*}else{
		root->left = root->right->left;
		root->right = root->right->right;
		root->center = root->right->center;
		root->rkey = root->right->rkey;
		root->rval = root->right->rval;
		root->lkey = root->right->lkey;
		root->lval = root->right->lval;
		}*/
		//delete node->left;
		delete temp;
		return;
	}
	else{
		Node<Key,Val> *adj = adjacent(node,root);
		if(adj->rkey!=NULL)
		{
			if(parent->rkey==NULL){
				if(parent->left==node){
					node->lkey = parent->lkey;
					node->lval = parent->lval;
					parent->lkey = adj->lkey;
					parent->lval = adj->lval;
					adj->lval =adj->rval;
					adj->lkey = adj->rkey;
					adj->left = adj->center;
					adj->rkey = NULL;
					adj->rval = NULL;
					node->right = adj->left;
					adj->center = NULL;
				}else{
					node->lkey = parent->lkey;
					node->lval = parent->lval;
					parent->lkey = adj->rkey;
					parent->lval = adj->rval;
					adj->rkey = NULL;
					adj->rval = NULL;
					node->right = node->left;
					node->left = adj->right;
					adj->right = adj->center;
					adj->center = NULL;
				}
			}
			else{
				if(parent->left==node){
					node->right = adj->left;
					adj->left = adj->center;
					adj->center = NULL;
					node->lkey = parent->lkey;
					node->lval = parent->lval;
					parent->lkey = adj->lkey;
					parent->lval = adj->lval;
					adj->lkey = adj->rkey;
					adj->lval = adj->rval;
					adj->rkey = NULL;
					adj->rval = NULL;
				}else if(parent->center == node){
					node->right = node->left;
					node->left = adj->right;
					adj->right = adj->center;
					adj->center = NULL;
					node->lkey = parent->lkey;
					node->lval = parent->lval;
					parent->lkey = adj->rkey;
					parent->lval = adj->rval;
					adj->rkey = NULL;
					adj->rval = NULL;
				}else if(parent->right ==node){
					node->right = node->left;
					node->left = adj->right;
					adj->right = adj->center;
					adj->center = NULL;
					node->lkey = parent->rkey;
					node->lval = parent->rval;
					parent->rkey = adj->rkey;
					parent->rval = adj->rval;
					adj->rkey = NULL;
					adj->rval = NULL;
				}
			}
		}else{
			if(parent->rkey!=NULL){
				if(parent->left == node){
					node->center = adj->left;
					node->right = adj->right;
					node->lkey = parent->lkey;
					node->lval = parent->lval;
					node->rkey = adj->lkey;
					node->rval = adj->rval;
					parent->center = NULL;
					parent->lkey = parent->rkey;
					parent->lval = parent->rval;
					parent->rkey = NULL;
					parent->rval = NULL;
					delete adj;
					parent->center = NULL;
				}else if(parent->center==node){
					adj->rkey = parent->lkey;
					adj->rval = parent->lval;
					adj->center = adj->right;
					adj->right = node->left;
					parent->lkey = parent->rkey;
					parent->lval = parent->rval;
					parent->center = NULL;
					parent->rkey = NULL;
					parent->rval = NULL;
					delete node;
					parent->center = NULL;
				}else if(parent->right==node){
					node->right = node->left;
					node->left= adj->left;
					node->center = adj->right;
					node->lkey = adj->lkey;
					node->lval = adj->lval;
					node->rkey = parent->rkey;
					node->rval = parent->rval;
					parent->center = NULL;
					parent->rkey = NULL;
					parent->rval = NULL;
					delete adj;
					parent->center = NULL;
				}

			}else{
				if(parent->left == node){
					Node<Key,Val> *pparent = find_Parent(parent,root);
					node->center = adj->left;
					node->right = adj->right;
					node->lkey = parent->lkey;
					node->lval = parent->lval;
					node->rkey = adj->lkey;
					node->rval = adj->lval;
					parent->rkey = NULL;
					parent->rval = NULL;
					parent->right = NULL;
					delete adj;
					remove_helper(pparent,parent,root);
				}else{
					Node<Key,Val> *pparent = find_Parent(parent,root);
					adj->center = adj->right;
					adj->right = node->left;
					adj->rkey = parent->lkey;
					adj->rval = parent->lval;
					parent->rkey = NULL;
					parent->rval = NULL;
					parent->right = NULL;
					delete node;
					remove_helper(pparent,parent,root);
				}
			}
		}
	}
}
template <class Key, class Val>
Val* Tree<Key,Val>::remove(Key key){
	Key *k = &key;
	Node<Key,Val> *N = findNode(root,k);
	Val *result;
	if(N==NULL)
		return NULL;
	else{
		bool c = 0;
		bool *check=&c;
		//Key* temp=NULL;
		Val* tempv = search(key);
		Node<Key,Val> *M = swap_key(N,k,tempv);

		Node<Key,Val> *parent = find_Parent(M,root);
		result = removeKey(M,k,check);
		if(*check){
			remove_helper(parent,M,root);
			//delete M;
		}
	}
	return result;
}
template <class Key, class Val>
static void print_help(Node<Key,Val> *node,ostream &os,Node<Key,Val> *root){
	if(!node) return;
	if(node->rkey!=NULL){
		print_help(node->left,os,root);
		int i = find_depth(root,node->lkey);
		for(int j = 0;j<i;j++)
			os<<"    ";
		os<<*(node->lval)<<endl;
		print_help(node->center,os,root);
		int m = find_depth(root,node->rkey);
		for(int j = 0;j<m;j++)
			os<<"    ";
		os<<*(node->rval)<<endl;
		print_help(node->right,os,root);
	}else{
		print_help(node->left,os,root);
		int l = find_depth(root,node->lkey);
		for(int j = 0;j<l;j++)
			os<<"    ";
		os<<*(node->lval)<<endl;
		print_help(node->right,os,root);
	}
}
template <class Key, class Val>
void Tree<Key,Val>::inOrderPrint(ostream &os)const{
	print_help(root,os,root);
}
template <class Key, class Val>
static int find_depth(Node<Key,Val> *root, Key *key){
	int result = 0;
	Node<Key,Val> *cur = root;
	while(1){
		if(cur->rkey!=NULL){
			if(*key==*cur->rkey||*key==*cur->lkey){
				break;
			}else if(*key<*cur->lkey){
				cur = cur->left;
			}else if(*key>*cur->rkey){
				cur = cur->right;
			}else
				cur = cur->center;
		}else{
			if(*key==*cur->lkey){
				break;
			}else if(*key<*cur->lkey){
				cur = cur->left;
			}
			else{
				cur = cur->right;
			}
		}
		result++;
	}
	return result;
}
template <class Key, class Val>
Tree<Key,Val>::Tree(){
	root = new Node<Key,Val>;
	root->center = NULL;
	root->left = NULL;
	root->right = NULL;
	root->lkey = NULL;
	root->lval = NULL;
	root->rkey = NULL;
	root->rval = NULL;
}
template <class Key, class Val>
static void removeAll(Node<Key,Val> *node){
	if(!node)
		return;
	else{
		removeAll(node->left);
		removeAll(node->center);
		removeAll(node->right);
		delete node;
	}
}
template <class Key, class Val>
static void copy_helper(Node<Key,Val> *node,Node<Key,Val> *source){
		node->lkey = source->lkey;
		node->lval = source->lval;
		node->rkey = NULL;
		node->rval = NULL;
		if(source->rkey!=NULL){
			node->rkey = source->rkey;
			node->rval = source->rval;
		}if(source->left!=NULL){
			Node <Key,Val> *lnode = new Node <Key,Val>;
			node->left = lnode;
			copy_helper(lnode,source->left);
			Node <Key,Val> *rnode = new Node <Key,Val>;
			node->right = rnode;
			copy_helper(rnode,source->right);
			if(source->center!=NULL){
				Node <Key,Val> *cnode = new Node <Key,Val>;
				node->center = cnode;
				copy_helper(cnode,source->center);
			}else{
				node->center=NULL;
			}
		}else{
			node->left=NULL;
			node->right=NULL;
			node->center=NULL;
			return;
		}
}

template <class Key, class Val>
Tree<Key,Val>::Tree(const Tree<Key,Val> &t){
	root = new Node<Key,Val>;
	root->center = NULL;
	root->left = NULL;
	root->right = NULL;
	root->lkey = NULL;
	root->lval = NULL;
	root->rkey = NULL;
	root->rval = NULL;
	copy_helper(root,t.Root());
}
template <class Key, class Val>
Tree<Key,Val> &Tree<Key,Val>::operator=(const Tree &t){
	copy_helper(root,t.Root());
	return this;
}
template <class Key, class Val>
Tree<Key,Val>::~Tree(){
	removeAll(root);
}
