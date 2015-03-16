//rbnode.h
#ifndef _RBNODE_H_
#define _RBNODE_H_

#include <memory>
#include "node.h"

class RBNode:public Node{
public:
	//constructor
	RBNode();
	//deconstructor
	virtual ~RBNode() = default;
	//member
	std::shared_ptr<RBNode> left, right, parent;
	int color;
};

#endif // ~rbnode.h