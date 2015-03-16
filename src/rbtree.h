//rbtree.h
#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <memory>
#include "tree.h"

class RBTree :public Tree{
public:
	//constructor
	RBTree();
	//deconstructor
	virtual ~RBTree() = default;
	//red-black tree methods
	void inorder_walk(std::shared_ptr<RBNode> x, std::ostream_iterator<int> &out_iter);
	std::shared_ptr<RBNode> search(std::shared_ptr<RBNode> x, int k);
	void left_rotate(std::shared_ptr<RBNode> x);
	void right_rotate(std::shared_ptr<RBNode> x);
	void insert_fixup(std::shared_ptr<RBNode> z);
	void tree_insert(std::shared_ptr<RBNode> z);
	void transplant(std::shared_ptr<RBNode> u, std::shared_ptr<RBNode> v);
	void tree_delete(std::shared_ptr<RBNode> z);
	void delete_fixup(std::shared_ptr<RBNode> x);
	//member
	std::shared_ptr<RBNode> root;
	std::shared_ptr<RBNode> nil;
};


#endif // ~rbtree.h