#pragma once

#include <unordered_map>
#include "Point2D.h"
#include "Connection.h"
#include <string>


class Connection;

class Node
{
	friend class Connection;

	Point2D point;

	std::unordered_map<Node*, Connection*> connectionList;

	void addConnection(Node* other, Connection* con);
	void removeConnection(Node* other);

	public:
	Node(Point2D _point) : point(_point) {}
	~Node();

	const std::unordered_map<Node*, Connection*>& getConnectionList() { return connectionList; }
	Point2D getPoint() { return point; }
	Connection* getConnection(Node& other);

	//std::string toStringConnections();
};