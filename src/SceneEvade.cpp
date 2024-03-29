#include "SceneEvade.h"
#include "Evade.h"
#include "Seek.h"



SceneEvade::SceneEvade()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Evade);
	agent->setPosition(Vector2D(300, 300));
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
	agent = new Agent();
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(100, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setMaxVel(400);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

SceneEvade::~SceneEvade()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneEvade::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[1]->setTarget(target);
			

		}
		break;
	default:
		break;
	}
	agents[0]->setTargetAgent(agents[1]);
	agents[0]->update(dtime, event);
	agents[1]->update(dtime, event);
	predict = agents[0]->getTarget();
}

void SceneEvade::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)predict.x, (int)predict.y, 15, 0, 255, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneEvade::getTitle()
{
	return "SDL Steering Behaviors :: Evade mo";
}
