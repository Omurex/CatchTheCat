#include "GraphFunctions.h"
#include "World.h"


NodeBoard GraphFunctions::createBoardFromWorld(World* world, float blockedNeighborWeightModifier)
{
	int wSize = world->getWorldSideSize();

	NodeBoard board(wSize, std::vector<Node*>(wSize, nullptr));

	// Fill board, non-blocked spaces get a node, blocked spaces get nullptr
	for (int r = 0; r < wSize; r++)
	{
		for (int c = 0; c < wSize; c++)
		{
			Point2D point = Point2D(c, r);
			if (world->getContent(world->convertToMiddleOrigin(point)) == false) // Point unblocked
			{
				board[c][r] = new Node(point);
			}
			else
			{
				board[c][r] = nullptr;
			}
		}
	}

	// Link each node to neighbor nodes
	for (int r = 0; r < wSize; r++)
	{
		for (int c = 0; c < wSize; c++)
		{
			if (board[c][r] != nullptr)
			{
				linkNode(*board[c][r], board, world, blockedNeighborWeightModifier);
			}
		}
	}

	return board;
}


void GraphFunctions::linkNode(Node& node, NodeBoard& board, World* world, float blockedNeighborWeightModifier)
{
	int finalWeight = 0;

	for (int xMod = -1; xMod <= 1; xMod++) 
	{
		for (int yMod = -1; yMod <= 1; yMod++) 
		{
			if (xMod == 0 && yMod == 0) continue;

			Point2D point = Point2D(node.getPoint().x + xMod, node.getPoint().y + yMod);

			// If fthis point is out of bounds, continue
			if (point.x < 0 || point.y < 0 || point.x >= world->getWorldSideSize() ||
				point.y >= world->getWorldSideSize()) continue;

			if (board[point.x][point.y] == nullptr) // If there is a neighbor that is blocked, increase weight of all connections
			{
				finalWeight++;
				continue;
			}

			Point2D worldAdjustedPoint = world->convertToMiddleOrigin(point);

			if (world->isValidPosition(worldAdjustedPoint) && world->getContent(worldAdjustedPoint) == false &&
				world->isNeighbor(world->convertToMiddleOrigin(node.getPoint()), worldAdjustedPoint)) 
			{
				Connection* con = new Connection(node, *board[point.x][point.y], 1);
			}
		}
	}

	auto conList = node.getConnectionList();

	for (auto it = conList.begin(); it != conList.end(); it++) 
	{
		it->second->setWeight(1 + (finalWeight * blockedNeighborWeightModifier));
	}
}


std::vector<Node*> GraphFunctions::getEdgeNodes(NodeBoard& board)
{
	int sideLength = board.size();

	std::vector<Node*> edgeList;

	for (int x = 0; x < sideLength; x++)
	{
		edgeList.push_back(board[x][0]);
		edgeList.push_back(board[x][sideLength - 1]);
	}

	for (int y = 0; y < sideLength; y++)
	{
		edgeList.push_back(board[0][y]);
		edgeList.push_back(board[sideLength - 1][y]);
	}

	return edgeList;
}


std::vector<Point2D> GraphFunctions::getClosestPathToEdge(Point2D startPosMiddleOrigin, World* world, float blockedNeighborWeightModifier)
{
	NodeBoard board = GraphFunctions::createBoardFromWorld(world, blockedNeighborWeightModifier);

	Point2D catPosStandard = world->convertToStandard(startPosMiddleOrigin);
	Node* catNode = board[catPosStandard.x][catPosStandard.y];

	std::unordered_map<Node*, DijkstraNodeInfo> dijkstraResult = GraphFunctions::dijkstraSearchNoTarget(*catNode, board, world);
	std::vector<Node*> edgeList = GraphFunctions::getEdgeNodes(board);

	Node* winningEdgeNode = nullptr;

	for (Node* n : edgeList)
	{
		if (n == nullptr || dijkstraResult.find(n) == dijkstraResult.end())
		{
			continue;
		}

		if (winningEdgeNode == nullptr)
		{
			winningEdgeNode = n;
		}
		else
		{
			if (dijkstraResult.at(n).pathWeight < dijkstraResult.at(winningEdgeNode).pathWeight)
			{
				winningEdgeNode = n;
			}
		}
	}

	if (winningEdgeNode == nullptr) return {};

	// Loop through dijkstra result to get backwards path
	std::vector<Node*> nodePath;
	Node* trackedNode = winningEdgeNode;

	while (trackedNode != nullptr)
	{
		nodePath.push_back(trackedNode);
		trackedNode = dijkstraResult.at(trackedNode).parent;
	}

	if (nodePath.size() == 0 || nodePath.size() == 1) return {}; // No path found

	// Reverse path to get actual path we will travel down
	std::reverse(nodePath.begin(), nodePath.end());

	std::vector<Point2D> path(nodePath.size());

	// Convert back to middle origin coordinate system
	for (int i = 0; i < nodePath.size(); i++)
	{
		path[i] = world->convertToMiddleOrigin(nodePath.at(i)->getPoint());
	}

	cleanupBoard(board);

	return path;
}


std::unordered_map<Node*, DijkstraNodeInfo> GraphFunctions::dijkstraSearchNoTarget(Node& startNode, NodeBoard& board, World* world)
{
	// Compare lambda for priority queue sorting
	auto pQueueCompare = [](const DijkstraNodeInfo& left, const DijkstraNodeInfo& right) { return left.pathWeight > right.pathWeight; };
	std::priority_queue<DijkstraNodeInfo, std::vector<DijkstraNodeInfo>, decltype(pQueueCompare)> pQueue(pQueueCompare);

	std::unordered_map<Node*, DijkstraNodeInfo> processedNodes;

	int wSize = world->getWorldSideSize();

	pQueue.push(DijkstraNodeInfo(&startNode, nullptr, 0));

	while (pQueue.empty() == false)
	{
		DijkstraNodeInfo nextNodeInfo = pQueue.top();
		pQueue.pop();

		if (processedNodes.find(nextNodeInfo.node) != processedNodes.end()) continue; // Already processed node, skip

		std::unordered_map<Node*, Connection*> connectionList = nextNodeInfo.node->getConnectionList();

		for (auto it = connectionList.begin(); it != connectionList.end(); it++) // Load queue with neighbors
		{
			pQueue.push(DijkstraNodeInfo(it->first, nextNodeInfo.node, it->second->getWeight() + nextNodeInfo.pathWeight));
		}

		processedNodes.insert(std::make_pair(nextNodeInfo.node, nextNodeInfo));
	}

	return processedNodes;
}


void GraphFunctions::cleanupBoard(NodeBoard& board)
{
	for (int x = 0; x < board.size(); x++)
	{
		for (int y = 0; y < board.size(); y++)
		{
			if(board[x][y] != nullptr)
				delete board[x][y];
		}
	}
}


//void GraphFunctions::printBoard(NodeBoard& board)
//{
//	for (int y = 0; y < board.size(); y++)
//	{
//		for (int x = 0; x < board.size(); x++)
//		{
//			if (board[x][y] == nullptr) std::cout << " XX,XX ";
//			else
//			{
//				std::string pStr = "";
//
//				if (y % 2 == 1) pStr += "  ";
//
//				if (x < 10) pStr += "0" + std::to_string(x);
//				else pStr += std::to_string(x);
//				pStr += ",";
//				if (y < 10) pStr += "0" + std::to_string(y);
//				else pStr += std::to_string(y);
//
//				std::cout << " " + pStr + " ";
//			}
//		}
//		std::cout << std::endl;
//	}
//}