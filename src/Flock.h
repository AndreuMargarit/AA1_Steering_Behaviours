#pragma once
#include "Agent.h"

class Flock :
	public Agent::SteeringBehavior
{
public:
	Flock();
	~Flock();

private:
	std::vector<Agent*> neighbors;
	Vector2D desiredVelocity, steeringForce, flockingForce;
	float K_ALIGNMENT_FORCE = 1;
	float K_COHESION_FORCE = 2;
	float K_FLEE_FORCE = 5;
public:
	void applySteeringForce(Agent *agent, float dtime);
	Vector2D applyAlignment(Agent* agent);
	Vector2D applyCohesion(Agent* agent);
	Vector2D applyFlee(Agent* agent);
};

