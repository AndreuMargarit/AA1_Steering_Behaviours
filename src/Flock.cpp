#include "Flock.h"
//#include <stdio.h>

Flock::Flock()
{
	neighbors = std::vector<Agent*>();
}

Flock::~Flock()
{
}

void Flock::applySteeringForce(Agent *agent, float dtime) {
	
	agent->getDesiredVelocity(desiredVelocity);
	agent->calculateSteeringForce(steeringForce, desiredVelocity);
	calculateFlockingForce(agent, alignment, cohesion, flock);
	std::cout << alignment.x << ' ' << alignment.y << std::endl;
	flockingForce = 
		alignment.Normalize() * K_ALIGNMENT_FORCE +
		flock.Normalize() * K_FLEE_FORCE +
		cohesion.Normalize() * K_COHESION_FORCE;

	agent->UpdateForces(flockingForce, dtime);
	agent->UpdateForces(steeringForce, dtime);
}

void Flock::calculateFlockingForce(Agent* agent, Vector2D& align, Vector2D& cohesion, Vector2D& flock) {
	std::vector<Agent*> agents = agent->getNeighbors();
	int neighbourCounter = 0;
	for (int i = 0; i < agents.size(); i++) {
		if (NEIGHBOR_RADIUS > (agent->getPosition() - agents[i]->getPosition()).Length() && agent != agents[i]){
			align += agents[i]->getVelocity();
			cohesion += agents[i]->getPosition();
			flock += (agent->getPosition() - agents[i]->getPosition());
			neighbourCounter++;
		}
	}

	if (neighbourCounter > 0) {

		align /= neighbourCounter;
		cohesion /= agents.size();
		cohesion -= agent->getPosition();
		flock /= agents.size();
	}
	else {
		align = cohesion = flock = Vector2D(0, 0);
	}
}
