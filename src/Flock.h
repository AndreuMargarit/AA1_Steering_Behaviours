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
	float K_COHESION_FORCE = 16;
	float K_FLEE_FORCE = 20;
	const int NEIGHBOR_RADIUS = 200;

	Vector2D alignment;
	Vector2D cohesion;
	Vector2D flock;

public:
	void applySteeringForce(Agent *agent, float dtime);

	void calculateFlockingForce(Agent* agent, Vector2D& align, Vector2D& cohesion, Vector2D& flock);
	Vector2D applyAlignment(Agent* agent);
	Vector2D applyCohesion(Agent* agent);
	Vector2D applyFlee(Agent* agent);
};

