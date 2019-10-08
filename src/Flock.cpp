#include "Flock.h"

Flock::Flock()
{
	neighbors = std::vector<Agent*>();
}

Flock::~Flock()
{
}

void Flock::applySteeringForce(Agent *agent, float dtime) {
	
	agent->getDesiredVelocity(desiredVelocity);
	//agent->calculateSteeringForce(steeringForce, desiredVelocity);
	flockingForce = 
		applyAlignment(agent) * K_ALIGNMENT_FORCE 
		
		//+ applyFlee(agent) * K_FLEE_FORCE +
		//applyCohesion(agent) * K_COHESION_FORCE
		;
	if(agent->getNeighbors().size() > 0)
		agent->UpdateForces(flockingForce, dtime);
}

Vector2D Flock::applyAlignment(Agent* agent) {
	Vector2D averageVelocity;
	std::vector<Agent*> agents = agent->getNeighbors();
	for (int i = 0; i < agents.size(); i++) {
		averageVelocity += agents[i]->getVelocity();
	}
	averageVelocity /= agents.size();
	return averageVelocity.Normalize();
}

Vector2D Flock::applyCohesion(Agent* agent) {
	Vector2D averagePosition;
	std::vector<Agent*> agents = agent->getNeighbors();
	for (int i = 0; i < agents.size(); i++) {
		averagePosition += agents[i]->getPosition();
	}
	averagePosition /= agents.size();
	averagePosition -= agent->getPosition();
	return averagePosition.Normalize();
}

Vector2D Flock::applyFlee(Agent* agent) {
	Vector2D separationVector;
	std::vector<Agent*> agents = agent->getNeighbors();
	for (int i = 0; i < agents.size(); i++) {
		separationVector += (agent->getPosition() - agents[i]->getPosition());
	}
	separationVector /= agents.size();
	return separationVector.Normalize();

}
