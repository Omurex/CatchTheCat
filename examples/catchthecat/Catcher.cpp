#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize()/2;
  for(;;) {

    //Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    Point2D cat = world->getCat();

	auto catPredictedPath = GraphFunctions::getClosestPathToEdge(cat, world, 1);

	if (catPredictedPath.size() < 2)
	{
		throw new _exception();
	}
	else
	{
		return catPredictedPath.at(catPredictedPath.size() - 1);
	}

    /*if(cat.x!=p.x && cat.y!=p.y && !world->getContent(p))
      return p;*/
  }
}
