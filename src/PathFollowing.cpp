#include "PathFollowing.h"



PathFollowing::PathFollowing(Agent *agent)
{
	pathPoints.push_back(Vector2D(200, 250));
	pathPoints.push_back(Vector2D(200, 550));
	pathPoints.push_back(Vector2D(1000, 250));
	pathPoints.push_back(Vector2D(1000, 550));
	agent->setTarget(pathPoints[pathPoint]);
	obstaclePos = Vector2D(600, 300);
	
}


PathFollowing::~PathFollowing()
{
}

void PathFollowing::UpdatePath(Agent *agent)
{
	pathPoint++;
	if (pathPoint == pathPoints.size()) pathPoint = 0;
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

void PathFollowing::obstacleAvoiding(Agent *agent, float dtime)
{
	obstacleVec = Vector2D(0, 0);

	if (obstaclePos.Distance(obstaclePos, agent->getPosition()) <= 50)
	{
		float aux = obstaclePos.Distance(obstaclePos, agent->getPosition());
		 obstacleVec = (agent->getPosition() - obstaclePos);
		agent->getDesiredVelocityPath(obstacleVec, 1.f);
	}
	
}


void PathFollowing::applySteeringForce(Agent *agent, float dtime)
{
	dist = agent->getPosition().Distance(agent->getPosition(), pathPoints[pathPoint]);

	if(dist <= 10)
	UpdatePath(agent);
	if (agent->getNewPath())
	{
		pathPoints.insert(pathPoints.begin()+pathPoint, agent->getTargetAgent()->getTarget());
		pathPoint--;
		UpdatePath(agent);
		agent->setNewPath(false);
	}
	

	agent->getDesiredVelocity(desiredVelocity);
	agent->calculateSteeringForce(steeringForce, desiredVelocity);
	obstacleAvoiding(agent, dtime);
	
	agent->UpdateForces((steeringForce + obstacleVec*0.4f), dtime);
}
