//rbtree.cpp

#include <memory>
#include <iostream>

#include "rbnode.h"
#include "rbtree.h"
//constructor
RBTree::RBTree(){
	this->nil = std::make_shared<RBNode>();
	this->nil->color = 1;
	this->root = this->nil;
};
//methods
void RBTree::inorder_walk(std::shared_ptr<RBNode> x, std::ostream_iterator<int> &out_iter){
	if (x != this->nil){
		inorder_walk(x->left, out_iter);
		*out_iter++ = x->key;
		inorder_walk(x->right, out_iter);
	}
}

std::shared_ptr<RBNode> RBTree::search(std::shared_ptr<RBNode> x, int k){
	if (x==this->nil){
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

void RBTree::left_rotate(std::shared_ptr<RBNode> x){
	auto y = x->right;
	x->right = y->left;
	if (y->left != this->nil){
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == this->nil){
		this->root = y;
	}
	else if (x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RBTree::right_rotate(std::shared_ptr<RBNode> x){
	auto y = x->left;
	x->left = y->right;
	if (y->right != this->nil){
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == this->nil){
		this->root = y;
	}
	else if (x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}

void RBTree::tree_insert(std::shared_ptr<RBNode> z){
	auto y = this->nil;
	auto x = this->root;
	while (x != this->nil){
		y = x;
		if (z->key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	z->parent = y;
	if (y == this->nil){
		this->root = z;
	}
	else if (z->key < y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}
	z->left = this->nil;
	z->right = this->nil;
	z->color = 0;
	insert_fixup(z);
}

void RBTree::insert_fixup(std::shared_ptr<RBNode> z){
	while (z->parent->color == 0){
		if (z->parent == z->parent->parent->left){
			auto y = z->parent->parent->right;
			if (y->color == 0){
				z->parent->color = 1;
				y->color = 1;
				z->parent->parent->color = 0;
				z = z->parent->parent;
			}
			else{
				if (z == z->parent->right){
					z = z->parent;
					left_rotate(z);
					
				}
				z->parent->color = 1;
				z->parent->parent->color = 0;
				right_rotate(z->parent->parent);
			}
		}
		else{
			auto y = z->parent->parent->left;
			if (y->color == 0){
				z->parent->color = 1;
				y->color = 1;
				z->parent->parent->color = 0;
				z = z->parent->parent;
			}
			else{
				if (z == z->parent->left){
					z = z->parent;
					right_rotate(z);
				}
				z->parent->color = 1;
				z->parent->parent->color = 0;
				left_rotate(z->parent->parent);
			}
		}
	}
	this->root->color = 1;
}

void RBTree::transplant(std::shared_ptr<RBNode> u, std::shared_ptr<RBNode> v){
	if (u->parent == this->nil){
		this->root = v;
	}
	else if (u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RBTree::tree_delete(std::shared_ptr<RBNode> z){
	auto y = z;
	std::shared_ptr<RBNode> x;
	int y_original_color = y->color;
	if (z->left == this->nil){
		x = z->right;
		transplant(z, z->right);
	}
	else if (z->right == this->nil){
		x = z->left;
		transplant(z, z->left);
	}
	else{
		y = std::dynamic_pointer_cast<RBNode>(minimum(z->right));
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z){
			x->parent = y;
		}
		else{
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_original_color == 1){
		delete_fixup(x);
	}
}

void RBTree::delete_fixup(std::shared_ptr<RBNode> x){
	while (x != this->root&&x->color == 1){
		if (x == x->parent->left){
			auto w = x->parent->right;
			if (w->color == 0){
				w->color = 1;
				x->parent->color = 0;
				left_rotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 1 && w->right->color == 1){
				w->color = 0;
				x = x->parent;
			}
			else{
				if (w->right->color == 1){
					w->left->color = 1;
					w->color = 0;
					right_rotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->right->color = 1;
				left_rotate(x->parent);
				x = this->root;
			}
		}
		else{
			auto w = x->parent->left;
			if (w->color == 0){
				w->color = 1;
				x->parent->color = 0;
				right_rotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 1 && w->left->color == 1){
				w->color = 0;
				x = x->parent;
			}
			else{
				if (w->left->color == 1){
					w->right->color = 1;
					w->color = 0;
					left_rotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->left->color = 1;
				right_rotate(x->parent);
				x = this->root;
			}
		}
	}
	x->color = 1;
}

