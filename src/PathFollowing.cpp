#include "PathFollowing.h"



PathFollowing::PathFollowing(Agent *agent)
{
	pathPoints[0] = Vector2D(200, 250);
	pathPoints[1] = Vector2D(200, 550);
	pathPoints[3] = Vector2D(1000, 550);
	pathPoints[2] = Vector2D(1000, 250);
	agent->setTarget(pathPoints[pathPoint]);
}


PathFollowing::~PathFollowing()
{
}

void PathFollowing::UpdatePath(Agent *agent)
{
	pathPoint++;
	if (pathPoint == 4) pathPoint = 0;
	agent->setTarget(pathPoints[pathPoint]);
}

Vector2D PathFollowing::getPathPoint(int num)
{
	return pathPoints[num];
}

int PathFollowing::getNumPathPoints()
{
	return numPathPoints;
}

void PathFollowing::applySteeringForce(Agent *agent, float dtime)
{
	dist = agent->getPosition().Distance(agent->getPosition(), pathPoints[pathPoint]);

	if(dist <= 10)
	UpdatePath(agent);

	agent->getDesiredVelocity(desiredVelocity);
	agent->calculateSteeringForce(steeringForce, desiredVelocity);
	agent->UpdateForces(steeringForce, dtime);
}
