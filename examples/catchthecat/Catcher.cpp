#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  for(;;) 
  {
    Point2D cat = world->getCat();

	auto catPredictedPath = GraphFunctions::getClosestPathToEdge(cat, world, 1);

	if (catPredictedPath.size() < 2)
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
		return catPredictedPath.at(catPredictedPath.size() - 1);
	}
  }
}
