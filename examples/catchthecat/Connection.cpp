#include "Connection.h"


Connection::Connection(Node& _node1, Node& _node2, float _weight) : nodePair(_node1, _node2)
{
	_node1.addConnection(&_node2, this);
	_node2.addConnection(&_node1, this);

	setWeight(_weight);
}


Connection::~Connection()
{
	nodePair.first.removeConnection(&nodePair.second);
	nodePair.second.removeConnection(&nodePair.first);
}


bool Connection::setFirstNode(Node& node, float newWeight)
{
	if (&node == &nodePair.second) return false;

	nodePair.first = node;
	weight = newWeight;

	return true;
}


bool Connection::setSecondNode(Node& node, float newWeight)
{
	if (&node == &nodePair.first) return false;

	nodePair.second = node;
	weight = newWeight;

	return true;
}


int Connection::findNodeInConnection(Node& node)
{
	if (&nodePair.first == &node) return 0;
	else if (&nodePair.second == &node) return 1;
	else return -1;
}


Node* Connection::getOtherNode(Node& node)
{
	int index = findNodeInConnection(node);

	if (index == -1) return nullptr;

	return &std::get<0>(nodePair);
}


float Connection::setWeight(float _weight)
{
	if (_weight < 0) weight = 0;
	else if (weight >= INT_MAX) weight = INT_MAX - 1;
	else weight = _weight;

	return getWeight();
}
