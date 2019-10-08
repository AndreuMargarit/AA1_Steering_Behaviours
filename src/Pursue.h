#pragma once
#include "Agent.h"

class Pursue :
	public Agent::SteeringBehavior
{
public:
	Pursue();
	~Pursue();
	void applySteeringForce(Agent *agent, float dtime);
private:
	Vector2D desiredVelocity, vDelta, steeringForce, acceleration, velocity;
	Vector2D prediction, targetVel, dist;
	float t;
	float maxTime = 100;
};

