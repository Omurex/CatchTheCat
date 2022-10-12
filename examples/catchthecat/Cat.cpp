#include "Cat.h"
#include "World.h"
#include <stdexcept>


Point2D Cat::Move(World* world) 
{
	return calculateOptimalNextMove(world);
}


Point2D Cat::calculateOptimalNextMove(World* world)
{
	std::vector<Point2D> path = GraphFunctions::getClosestPathToEdge(world->getCat(), world);

	if (path.size() < 2) 
	{
		return world->getCat();
	}
	else
	{
		return path.at(1);
	}
}
