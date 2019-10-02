#include "Seek.h"
Seek::Seek()
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	desiredVelocity = agent->getTarget() - agent->getPosition();
	dist = desiredVelocity.Length();
	desiredVelocity.Normalize();
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
