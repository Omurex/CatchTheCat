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
	static NodeBoard createBoardFromWorld(World* world);
	static void linkNode(Node& node, NodeBoard& board, World* world, float blockedNeighborWeightModifier = 1);

	static std::vector<Node*> getEdgeNodes(NodeBoard& board);
	static std::vector<Point2D> getClosestPathToEdge(Point2D startPosMiddleOrigin, World* world);
    
	static std::unordered_map<Node*, DijkstraNodeInfo> dijkstraSearchNoTarget(Node& startNode, NodeBoard& board, World* world);

	static void printBoard(NodeBoard& board);
};