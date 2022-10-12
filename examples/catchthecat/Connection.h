#pragma once
#include <utility>
#include "Node.h"

class Node;

class Connection
{
	friend class Node;

	std::pair<Node&, Node&> nodePair;

	float weight;

	public:
	Connection(Node& _node1, Node& _node2, float _weight = 0);
	~Connection();

	std::pair<Node&, Node&> getNodes() { return nodePair; }

	Node& getFirstNode() { return nodePair.first; }
	Node& getSecondNode() { return nodePair.second; }

	// Returns true if succeeded, false if failed
	bool setFirstNode(Node& node, float newWeight);
	bool setSecondNode(Node& node, float newWeight);

	// Returns 0 if first, 1 if second, -1 if not found
	int findNodeInConnection(Node& node);
	Node* getOtherNode(Node& node); // Get node opposite of what was passed in

	float getWeight() { return weight; }
	float setWeight(float _weight); // Returns final set weight since we may change if below 0
};