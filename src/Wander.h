#pragma once
#include "Agent.h"

class Wander :
	public Agent::SteeringBehavior
{
public:
	const float _wanderMaxAngleChange = 0.01f * DEG2RAD;
	const float _wanderOffset = 300;
	const float _wanderRadius = 150;

	Wander();
	Wander(Agent* agent);
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

