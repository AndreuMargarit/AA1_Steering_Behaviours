#include "Seek.h"
Seek::Seek()
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	agent->getDesiredVelocity(desiredVelocity);
	agent->calculateSteeringForce(steeringForce, desiredVelocity);
	agent->UpdateForces(steeringForce, dtime);
}
