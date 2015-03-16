//tree.cpp
#include <iostream>
#include <memory>
#include <iterator>

#include "node.h"
#include "tree.h"
//constructor
Tree::Tree(){};
//methods
void Tree::tree_insert(std::shared_ptr<Node> z){
	std::shared_ptr<Node> y;
	auto x = this->root;
	while (x){
		y = x;
		if (z->key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	z->parent = y;
	if (!y){
		this->root = z;
	}
	else if (z->key < y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}
}

void Tree::inorder_walk(std::shared_ptr<Node> x, std::ostream_iterator<int> &out_iter){
	if (x){
		inorder_walk(x->left, out_iter);
		*out_iter++ = x->key;
		inorder_walk(x->right, out_iter);
	}
}

std::shared_ptr<Node> Tree::search(std::shared_ptr<Node> x, int k){
	if (!x){
		return nullptr;
	}
	else if (x->key == k){
		return x;
	}
	else if (k < x->key){
		return search(x->left, k);
	}
	else{
		return search(x->right, k);
	}
}

std::shared_ptr<Node> Tree::minimum(std::shared_ptr<Node> x){
	while (x->left){
		x = x->left;
	}
	return x;
}

std::shared_ptr<Node> Tree::maximum(std::shared_ptr<Node> x){
	while (x->right){
		x = x->right;
	}
	return x;
}

std::shared_ptr<Node> Tree::successor(std::shared_ptr<Node> x){
	if (x->right){
		return minimum(x->right);
	}
	else{
		auto y = x->parent;
		while (y&&x == y->right){
			x = y;
			y = y->parent;
		}
		return y;
	}
}

std::shared_ptr<Node> Tree::presuccessor(std::shared_ptr<Node> x){
	if (x->left){
		return maximum(x->left);
	}
	else{
		auto y = x->parent;
		while (y&&x == y->left){
			x = y;
			y = y->parent;
		}
		return y;
	}
}

void Tree::transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v){
	if (!u->parent){
		this->root = v;
	}
	else if (u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	if (v){
		v->parent = u->parent;
	}
}

void Tree::tree_delete(std::shared_ptr<Node> z){
	if (!z->left){
		transplant(z, z->right);
	}
	else if (!z->right){
		transplant(z, z->left);
	}
	else{
		auto y = minimum(z->right);
		if (y->parent != z){
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->parent = z->parent;
	}
}



