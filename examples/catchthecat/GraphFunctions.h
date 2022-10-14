#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include "Node.h"

class World;

typedef std::vector<std::vector<Node*>> NodeBoard;


struct DijkstraNodeInfo 
{
	Node* node;
	Node* parent;
	float pathWeight;

	DijkstraNodeInfo(Node* _node, Node* _parent, float path_weight) 
	{
		node = _node;
		parent = _parent;
		pathWeight = path_weight;
	}
};


class GraphFunctions 
{
	public:
	static NodeBoard createBoardFromWorld(World* world, float blockedNeighborWeightModifier = 1); // Generate board from current state of world
	static void linkNode(Node& node, NodeBoard& board, World* world, float blockedNeighborWeightModifier = 1); // Adds weighted connections to node depending on neighbors

	static std::vector<Node*> getEdgeNodes(NodeBoard& board); // Returns a list of all spots where cat can escape
	static std::vector<Point2D> getClosestPathToEdge(Point2D startPosMiddleOrigin, World* world, float blockedNeighborWeightModifier = 1);
    
	static std::unordered_map<Node*, DijkstraNodeInfo> dijkstraSearchNoTarget(Node& startNode, NodeBoard& board, World* world); // Returns result of full dijkstra map coverage

	static void cleanupBoard(NodeBoard& board);

	//static void printBoard(NodeBoard& board);
};