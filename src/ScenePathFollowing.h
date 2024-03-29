#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class ScenePathFollowing :
	public Scene
{
public:
	ScenePathFollowing();
	~ScenePathFollowing();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D trail[150];
	std::vector<Vector2D> pathPoints;
	int trailCounter, trailMax, nextTrail = 0;
};

