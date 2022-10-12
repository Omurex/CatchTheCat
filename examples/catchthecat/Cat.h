#ifndef CAT_H
#define CAT_H

#include <vector>
#include <unordered_map>
#include <queue>
#include "Agent.h"
#include "Node.h"
#include "GraphFunctions.h"


class Cat: public Agent {
	private:

	const float BLOCKED_NEIGHBORS_WEIGHT_MULTIPLIER = 1;

	Point2D calculateOptimalNextMove(World*);


	public:

    explicit Cat():Agent(){};
    Point2D Move(World *) override;

};

#endif  // CAT_H
