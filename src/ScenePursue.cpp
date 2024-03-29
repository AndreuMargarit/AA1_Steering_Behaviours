#include "ScenePursue.h"
#include "Pursue.h"
#include "Seek.h"



using namespace std;

ScenePursue::ScenePursue()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Pursue);
	agent->setTarget(Vector2D(100, 100));
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
	agent = new Agent();
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

ScenePursue::~ScenePursue()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePursue::update(float dtime, SDL_Event *event)
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

void ScenePursue::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)predict.x, (int)predict.y, 15, 0, 255, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* ScenePursue::getTitle()
{
	return "SDL Steering Behaviors :: Pursue Demo";
}
