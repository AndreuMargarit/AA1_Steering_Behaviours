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
			/*target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);*/
		}
		break;
	default:
		break;
	}
	agents[0]->update(dtime, event);

	nextTrail++;
	if (nextTrail == 20)
	{
		trail[trailCounter] = agents[0]->getPosition() - agents[0]->getVelocity().Normalize() * 20;
		trailCounter++;
		nextTrail = 0;
	}
	if (trailCounter == 110) trailCounter = 0;
	if(trailMax<110) trailMax++;
}

void ScenePathFollowing::draw()
{
	//draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	draw_circle(TheApp::Instance()->getRenderer(), 200, 250, 15, 0, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), 200, 550, 15, 0, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), 1000, 550, 15, 0, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), 1000, 250, 15, 0, 255, 255, 255);

	for (int i = 0; i < trailMax; i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), trail[i].x, trail[i].y, 15, 255, 0, 0, 255);
	}
	agents[0]->draw();
}

const char* ScenePathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: PathFollowing Demo";
}