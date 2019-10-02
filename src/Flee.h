#pragma once
#include "Agent.h"

class Flee :
	public Agent::SteeringBehavior
{
public:
	Flee();
	~Flee();
	void applySteeringForce(Agent *agent, float dtime);
private:
	Vector2D desiredVelocity, vDelta, steeringForce, acceleration, velocity;
	float dist;
};
