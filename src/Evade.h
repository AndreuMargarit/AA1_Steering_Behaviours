#pragma once
#include "Agent.h"

class Evade :
	public Agent::SteeringBehavior
{
public:
	Evade();
	~Evade();
	void applySteeringForce(Agent *agent, float dtime);
private:
	Vector2D desiredVelocity, vDelta, steeringForce, acceleration, velocity;
	Vector2D prediction, targetVel, dist;
	float t;
	float maxTime = 0.2;
};

