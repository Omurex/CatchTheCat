#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include <vector>
#include "Node.h"

typedef std::vector<std::vector<Node*>> NodeBoard;

class Cat: public Agent {
	private:
	std::vector<Point2D> calculateOptimalPath(World*);
	void linkNode(Node& node, NodeBoard& board, World* world);


	public:
    explicit Cat():Agent(){};
    Point2D Move(World *) override;
};

#endif  // CAT_H
