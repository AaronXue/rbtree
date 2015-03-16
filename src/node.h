//node.h
#ifndef _NODE_H_
#define _NODE_H_

#include <memory>

class Node{
public:
	//constructor
	Node();
	//deconstructor
	virtual ~Node() = default;
	//member
	int key;
	std::shared_ptr<Node> left, right, parent;
};

#endif // ~node.h