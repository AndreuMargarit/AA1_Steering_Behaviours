#include "Arrive.h"



Arrive::Arrive()
	: radius(300)
{
}


Arrive::~Arrive()
{
}

void Arrive::applySteeringForce(Agent *agent, float dtime)
{
	agent->getDistanceToTarget(dist);
	agent->calculateSpeedFactor(speedFactor, dist, radius);
	agent->getDesiredVelocity(desiredVelocity, true, speedFactor);
	agent->calculateSteeringForce(steeringForce, desiredVelocity);
	agent->UpdateForces(steeringForce, dtime);
}
