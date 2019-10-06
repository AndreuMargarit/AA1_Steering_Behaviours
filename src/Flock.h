#pragma once
#include "Agent.h"

class Flock :
	public Agent::SteeringBehavior
{
public:
	Flock();
	~Flock();
	void applySteeringForce(Agent *agent, float dtime);
};

