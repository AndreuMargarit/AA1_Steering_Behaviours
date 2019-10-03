#pragma once
#include "Agent.h"

class Arrive : public Agent::SteeringBehavior
{

public:
	Arrive();
	~Arrive();
	void applySteeringForce(Agent *agent, float dtime);
private:
	Vector2D desiredVelocity, steeringForce;
	float dist, speedFactor, radius;
};

