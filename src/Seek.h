#pragma once
#include "Agent.h"

class Seek :
	public Agent::SteeringBehavior
{
public:
	Seek();
	~Seek();
	void applySteeringForce(Agent *agent, float dtime);
private:
	Vector2D desiredVelocity, vDelta, steeringForce, acceleration, velocity;
	float dist;
};
