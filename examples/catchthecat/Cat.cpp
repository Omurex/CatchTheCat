#include "Cat.h"
#include "World.h"
#include <stdexcept>


Point2D Cat::Move(World* world) 
{
	Point2D calculatedNextMove = calculateOptimalNextMove(world);

	if (calculatedNextMove == world->getCat())
	{
		auto pos = world->getCat();

		std::vector<Point2D> possibleMoves
		{
			World::NE(pos), World::NW(pos), World::E(pos), 
			World::W(pos), World::SW(pos), World::SE(pos)
		};

		while (possibleMoves.empty() == false)
		{
			auto rand = Random::Range(0, possibleMoves.size() - 1);

			Point2D point = possibleMoves[rand];

			if (world->getContent(point) == false)
			{
				return point;
			}

			possibleMoves.erase(possibleMoves.begin() + rand);
		}

		return pos;
	}
	else
	{
		return calculatedNextMove;
	}
}


Point2D Cat::calculateOptimalNextMove(World* world)
{
	std::vector<Point2D> path = GraphFunctions::getClosestPathToEdge(world->getCat(), world, 1);

	if (path.size() < 2) 
	{
		return world->getCat();
	}
	else
	{
		return path.at(1);
	}
}
