#include "Flee.h"
Flee::Flee()
{
}

Flee::~Flee()
{
}

void Flee::applySteeringForce(Agent *agent, float dtime)
{
	agent->getDesiredVelocity(desiredVelocity);

	desiredVelocity *= agent->getMaxVelocity();
	vDelta = desiredVelocity - agent->getVelocity();
	vDelta /= agent->getMaxVelocity();

	steeringForce = vDelta * agent->getMaxForce();
	
	acceleration = steeringForce / agent->getMass();
	velocity = agent->getVelocity() + acceleration * dtime;

	velocity.Truncate(agent->getMaxVelocity());
	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}
