#include "Flee.h"
Flee::Flee()
{
}

Flee::~Flee()
{
}

void Flee::applySteeringForce(Agent *agent, float dtime)
{
	agent->getDesiredVelocity(desiredVelocity, false);
	agent->calculateSteeringForce(steeringForce, desiredVelocity);
	agent->UpdateForces(steeringForce, dtime);
}
