#include "Arrive.h"



Arrive::Arrive()
{
}


Arrive::~Arrive()
{
}

void Arrive::applySteeringForce(Agent *agent, float dtime)
{

	agent->getDesiredVelocity(desiredVelocity);
	agent->getDistanceToTarget(dist);

	speedFactor = 1;
	if (dist < 300)
	{
		speedFactor = dist / 300;
	}

	desiredVelocity *= agent->getMaxVelocity() * speedFactor;
	vDelta = desiredVelocity - agent->getVelocity();
	vDelta /= agent->getMaxVelocity();

	steeringForce = vDelta * agent->getMaxForce();
	
	acceleration = steeringForce / agent->getMass();
	velocity = agent->getVelocity() + acceleration * dtime;

	velocity.Truncate(agent->getMaxVelocity());

	
	agent->setVelocity(velocity);
	std::cout << agent->getVelocity().Length() <<" speed: " << speedFactor << std::endl;
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}
