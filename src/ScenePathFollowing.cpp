#include "ScenePathFollowing.h"
#include "PathFollowing.h"

using namespace std;

ScenePathFollowing::ScenePathFollowing()
{
	Agent *agent = new Agent;
	agent->setBehavior(new PathFollowing(agent));
	agent->setPosition(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	agent = new Agent();
	agents.push_back(agent);

	pathPoints.push_back(Vector2D(200, 250));
	pathPoints.push_back(Vector2D(200, 550));
	pathPoints.push_back(Vector2D(1000, 550));
	pathPoints.push_back(Vector2D(1000, 250));


}

ScenePathFollowing::~ScenePathFollowing()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFollowing::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[1]->setTarget(target);
			agents[0]->setNewPath(true);
			pathPoints.push_back(target);
		}
		break;
	default:
		break;
	}
	agents[0]->update(dtime, event);
	agents[0]->setTargetAgent(agents[1]);

	nextTrail++;
	if (nextTrail == 15)
	{
		trail[trailCounter] = agents[0]->getPosition() - agents[0]->getVelocity().Normalize() * 20;
		trailCounter++;
		nextTrail = 0;
	}
	if (trailCounter == 150) trailCounter = 0;
	if(trailMax<150) trailMax++;
}

void ScenePathFollowing::draw()
{
	for (int i = 0; i < trailMax; i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), trail[i].x, trail[i].y, 10, 0, 0, 255, 255);
	}

	for (int i = 0; i < pathPoints.size(); i++)
		draw_circle(TheApp::Instance()->getRenderer(), pathPoints[i].x, pathPoints[i].y, 15, 0, 255, 255, 255);

	draw_circle(TheApp::Instance()->getRenderer(), 600, 300, 25, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* ScenePathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: PathFollowing Demo";
}