#include "Pursue.h"
#include "Vector2D.h"


Pursue::Pursue()
{
}


Pursue::~Pursue()
{
}

void Pursue::applySteeringForce(Agent *agent, float dtime)
{
	if (agent->getVelocity().Length() !=0)
	{
		dist = agent->getTargetAgent()->getPosition() - agent->getPosition();
		float length = agent->getVelocity().Length();
		t = dist.Length() / length;
	}
	else
	{
		dist = agent->getTargetAgent()->getPosition() - agent->getPosition();
		t = dist.Length() / agent->getMaxVelocity();
	}
	std::cout << t << std::endl;
	if (t > maxTime) t = maxTime;
	
	agent->setTarget((agent->getTargetAgent()->getPosition() + agent->getTargetAgent()->getVelocity() * t));
	//agent->setTarget(agent->getTargetAgent()->getTarget() * (agent->getTargetAgent()->getPosition()-agent->getPosition()));


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