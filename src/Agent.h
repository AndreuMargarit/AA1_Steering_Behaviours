#pragma once
#include <vector>
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"


class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	Vector2D vDelta;
	Vector2D circleCenter;

	Agent *targetAgent;

	float speed;
	float orientation;
	float max_force;
	float max_velocity;
	float mass;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;
	std::vector<Agent*> neighbors;
	const int NEIGHBOR_RADIUS = 10;
	bool newPath = false;

public:
	Agent();
	Agent(Vector2D veloc);
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Vector2D getCircleCenter();
	void setAgents(std::vector<Agent*> agents);
	void setCircleCenter(Vector2D circleCenter);
	float getMaxVelocity();
	void setBehavior(SteeringBehavior *behavior);
	SteeringBehavior* getBehavior();
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	float getMass();
	void setMass(float _mass);
	float getMaxForce();
	void setMaxForce(float _force);
	float getOrientation();
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void getDesiredVelocity(Vector2D& desiredVelocityOut, bool seek = true, float speedFactor = 1);
	void getDistanceToTarget(float& distanceOut);
	void calculateSpeedFactor(float& speedFactor, float dist, float radius);
	void calculateSteeringForce(Vector2D& steeringForce, Vector2D desiredVelocity);
	void UpdateForces(Vector2D steeringForce, float dtime);
	void setNeighbors(std::vector<Agent*> agents);
	bool getNewPath();
	void setNewPath(bool state);
	void setMaxVel(float vel);

	
	std::vector<Agent*> getNeighbors();
	void setTargetAgent(Agent* target);
	Agent* getTargetAgent();
};
