#pragma once
#include "Agent.h"

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
	Vector2D pathPoints[4];
	int pathPoint = 0;
	int numPathPoints = 4;
	float dist;
};


