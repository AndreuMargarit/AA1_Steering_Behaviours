#pragma once
#include "Agent.h"

class Wander :
	public Agent::SteeringBehavior
{
public:
	const float _wanderMaxAngleChange = 1;
	const float _wanderOffset = 150;
	const float _wanderRadius = 75;

	Wander();
	~Wander();
	void applySteeringForce(Agent *agent, float dtime);

private:
	Vector2D desiredVelocity, steeringForce;
	float lastAngle, angleDelta;
	float _wanderAngle;
	float _targetAngle;

	void UpdateWanderAngle(Agent* agent);
	float RandomBinomial();
	void CalculateNewWanderPosition(Agent* agent);
};

