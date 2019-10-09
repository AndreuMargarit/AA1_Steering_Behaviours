#include "SceneFlock.h"
#include "Flock.h"
#include "Seek.h"

using namespace std;

SceneFlock::SceneFlock()
{
	for (int i = 0; i < 10; i++) {
		Agent *agent = new Agent(Vector2D(rand() % 5, rand() % 5));
		agent->setMass(0.2f);
		agent->setBehavior(new Flock);
		int randomX = rand() % 1280;
		int randomY = rand() % 768;
		agent->setPosition(Vector2D(randomX, randomY));
		agent->setTarget(Vector2D(640, 360));

		if((rand() % 2) == 1)
			agent->loadSpriteTexture("../res/zombie1.png", 8);
		else
			agent->loadSpriteTexture("../res/zombie2.png", 8);

		agents.push_back(agent);
	}
	for (int i = 0; i < 10; i++) {
		agents[i]->setFlock(agents);
	}

	target = Vector2D(640, 360);
}

SceneFlock::~SceneFlock()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlock::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			for (int i = 0; i < (int)agents.size(); i++)
				agents[i]->setTarget(target);
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < (int)agents.size(); i++) {
		agents[i]->update(dtime, event);
	}
}

void SceneFlock::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++)
		agents[i]->draw();
}

const char* SceneFlock::getTitle()
{
	return "SDL Steering Behaviors :: Flock Demo";
} 