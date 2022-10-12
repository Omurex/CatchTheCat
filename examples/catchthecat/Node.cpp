#include "Node.h"


Node::~Node()
{
	std::vector<Connection*> loggedConnections(connectionList.size());

	for (auto it = connectionList.begin(); it != connectionList.end(); it++)
	{
		loggedConnections.emplace_back(it->second);
	}

	for (Connection* con : loggedConnections)
	{
		delete con;
		con = nullptr;
	}
}


Connection* Node::getConnection(Node& other)
{
	auto iter = connectionList.find(&other);

	if (iter != connectionList.end()) return iter->second;

	return nullptr;
}


void Node::addConnection(Node* other, Connection* con)
{
	connectionList.emplace(other, con);
}


void Node::removeConnection(Node* other)
{
	connectionList.erase(other);
}


std::string Node::toStringConnections()
{
	std::string returnStr = point.toString() + " : ";

	for (auto it = connectionList.begin(); it != connectionList.end();)
	{
		returnStr += it->second->getOtherNode(*this)->point.toString();

		it++;

		if (it != connectionList.end())
		{
			returnStr += ", ";
		}
	}

	return returnStr;
}
