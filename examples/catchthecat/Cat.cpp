#include "Cat.h"
#include "World.h"
#include <stdexcept>
bool tog = false;
Point2D Cat::Move(World* world) {
	auto rand = Random::Range(0, 5);
	auto pos = world->getCat();

	/*switch (rand) {
		case 0:
			return World::NE(pos);
		case 1:
			return World::NW(pos);
		case 2:
			return World::E(pos);
		case 3:
			return World::W(pos);
		case 4:
			return World::SW(pos);
		case 5:
			return World::SE(pos);
		default:
			throw "random out of range";
	}*/

	calculateOptimalPath(world);

	if (tog == false)
	{
		return World::NE(pos);
		tog = true;
	}
	else
	{
		return World::E(pos);
		tog = false;
	}
}

std::vector<Point2D> Cat::calculateOptimalPath(World* world)
{
	int wSize = world->getWorldSideSize();
	
	NodeBoard board(wSize, std::vector<Node*>(wSize, nullptr));

	for (int r = 0; r < wSize; r++)
	{
		for (int c = 0; c < wSize; c++)
		{
			Point2D point = Point2D(c, r);
			if (world->getContent(point) == false) // Point unblocked
			{
				board[c][r] = new Node(point);
			}
		}
	}

	for (int r = 0; r < wSize; r++)
	{
		for (int c = 0; c < wSize; c++)
		{
			if (board[c][r] != nullptr)
			{
				linkNode(*board[c][r], board, world);
				std::cout << "COMPLETE" << std::endl;
			}
		}
	}
	
	Node* temp = board[0][0];
	//std::cout <<  temp->toStringConnections() << std::endl;

	return std::vector<Point2D>();
}


void Cat::linkNode(Node& node, NodeBoard& board, World* world)
{
	std::cout << "STANDARD: " + node.getPoint().toString() << std::endl;
	for (int xMod = -1; xMod <= 1; xMod++)
	{
		for (int yMod = -1; yMod <= 1; yMod++)
		{
			// LINK USING NOTEBOOK DIAGRAM
			if (xMod == 0 && yMod == 0) continue;

			Point2D point = Point2D(node.getPoint().x + xMod, node.getPoint().y + yMod);

			if (point.x < 0 || point.y < 0 || point.x >= world->getWorldSideSize() || point.y >= world->getWorldSideSize()) continue;
			if (board[point.x][point.y] == nullptr) continue;

			Point2D worldAdjustedPoint = world->convertToMiddleOrigin(point);

			std::cout << "WORLD: " + worldAdjustedPoint.toString() << std::endl;

			std::cout << world->isValidPosition(worldAdjustedPoint) << std::endl;

			if (world->isValidPosition(worldAdjustedPoint))
			{
				std::cout << (world->getContent(worldAdjustedPoint) == false) << std::endl;

				if ((world->getContent(worldAdjustedPoint) == false))
				{
					std::cout << world->isNeighbor(world->convertToMiddleOrigin(node.getPoint()), worldAdjustedPoint) << std::endl;
				}
			}

			if (world->isValidPosition(worldAdjustedPoint) && world->getContent(worldAdjustedPoint) == false && 
				world->isNeighbor(world->convertToMiddleOrigin(node.getPoint()), worldAdjustedPoint))
			{
				Connection* con = new Connection(node, *board[point.x][point.y], 1);
			}
		}
	}
}
