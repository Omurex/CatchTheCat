#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include <vector>
#include "Node.h"
#include <unordered_map>
#include <queue>


typedef std::vector<std::vector<Node*>> NodeBoard;

class Cat: public Agent {
	private:

	struct DijkstraNodeInfo
	{
		Node* node;
		Node* parent;
		float pathWeight;

		DijkstraNodeInfo(Node* _node, Node* _parent, float path_weight) { node = _node; parent = _parent; pathWeight = path_weight; }
	};

	Point2D calculateOptimalNextMove(World*);
	void linkNode(Node& node, NodeBoard& board, World* world);
	std::vector<Node*> getEdgeNodes(NodeBoard& board);

	std::unordered_map<Node*, DijkstraNodeInfo> dijkstraSearchNoTarget(Node& startNode, NodeBoard& board, World* world);

	public:

    explicit Cat():Agent(){};
    Point2D Move(World *) override;
};

#endif  // CAT_H
