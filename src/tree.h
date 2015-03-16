//tree.h
#ifndef _TREE_H_
#define _TREE_H_

#include <memory>
#include <iterator>

class Tree{
public:
	//constructor
	Tree();
	//deconstructor
	virtual ~Tree() = default;
	//methods
	void tree_insert(std::shared_ptr<Node> z);
	void inorder_walk(std::shared_ptr<Node> x, std::ostream_iterator<int> &out_iter);
	std::shared_ptr<Node> search(std::shared_ptr<Node> x, int k);
	std::shared_ptr<Node> minimum(std::shared_ptr<Node> x);
	std::shared_ptr<Node> maximum(std::shared_ptr<Node> x);
	std::shared_ptr<Node> successor(std::shared_ptr<Node> x);
	std::shared_ptr<Node> presuccessor(std::shared_ptr<Node> x);
	void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);
	void tree_delete(std::shared_ptr<Node> z);
	//member
	std::shared_ptr<Node> root;
};

#endif //~tree.h