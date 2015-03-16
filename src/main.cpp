#include <iostream>
#include <random>
#include <memory>
#include <iterator>

#include "node.h"
#include "rbnode.h"
#include "tree.h"
#include "rbtree.h"

using namespace std;

void demo(){
	const int n = 10;
	auto tree = make_shared<RBTree>();

	default_random_engine generator;
	uniform_int<int> dist(0, 100);
	//generate tree
	for (int i = 0; i < n; i++){
		auto z = make_shared<RBNode>();
		z->key = dist(generator);
		tree->tree_insert(z);
	}
	//inorder walk
	ostream_iterator<int> out_iter(cout, " ");
	tree->inorder_walk(tree->root, out_iter);
	cout << endl;
	//search
	int k = 50;
	cout << "search: " << k << endl;
	shared_ptr<RBNode> z;
	if (z = tree->search(tree->root, k)){
		cout << "find: " << k << endl;
	}
	else{
		cout << "cannot find." << endl;
	}
	//delete
	if (z){
		cout << "delete: " << z->key << endl;
		tree->tree_delete(z);
		tree->inorder_walk(tree->root, out_iter);
		getchar();
	}
}




int main(int argc, char* argv[]){
	demo();
	return 0;
}