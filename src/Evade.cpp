#include "Evade.h"
#include "Vector2D.h"


Evade::Evade()
{
}


Evade::~Evade()
{
}

void Evade::applySteeringForce(Agent *agent, float dtime)
{
	/*targetPos = agent->getTargetAgent()->getPosition();

	timeLookAhead = (agent->getTargetAgent()->getTarget() - agent->getTargetAgent()->getPosition()).Length();

	if (timeLookAhead > maxTime)
	{
		timeLookAhead = maxTime;
	}

	targetVel = timeLookAhead;*/

	if (agent->getVelocity().Length() != 0)
	{
		dist = agent->getTargetAgent()->getPosition() - agent->getPosition();
		t = dist.Length() / agent->getVelocity().Length();
	}
	else
	{
		dist = agent->getTargetAgent()->getPosition() - agent->getPosition();
		t = dist.Length() / agent->getMaxVelocity();
	}

	//if (t > maxTime) t = maxTime;

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

	std::cout << agent->getPosition().x << " " << agent->getPosition().y << std::endl;

}
