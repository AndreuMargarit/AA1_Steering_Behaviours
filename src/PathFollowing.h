#pragma once
#include "Agent.h"
#include <vector>

class PathFollowing :
	public Agent::SteeringBehavior
{
public:
	PathFollowing(Agent *agent);
	~PathFollowing();
	void UpdatePath(Agent *agent);
	Vector2D getPathPoint(int num);
	int getNumPathPoints();
	void applySteeringForce(Agent *agent, float dtime);
private:
	Vector2D desiredVelocity, steeringForce;
	std::vector<Vector2D> pathPoints;
	int pathPoint = 0;
	int numPathPoints = 4;
	float dist;
};


